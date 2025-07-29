// src/main.c
#include "hashmap.h"
#include <stdio.h>
#include <string.h>

struct account {
    unsigned long id;
    char *name;
    char *email;
    char *nickname;
    int point;
};

/**
 * Compare function for sorting accounts by ID.
 * It is used for hashmap operations.
 *
 * @param a Pointer to the first account.
 * @param b Pointer to the second account.
 * @param udata Unused user data pointer.
 * @return -1 if a < b, 1 if a > b, 0 if a == b.
 */
int account_compare(const void *a, const void *b,
                    void *udata __attribute__((unused))) {
    const struct account *aa = a;
    const struct account *bb = b;

    if (aa->id < bb->id) {
        return -1;
    } else if (aa->id > bb->id) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * An iterator function to print account details.
 *
 * @param item Pointer to the account item.
 * @param udata Unused user data pointer.
 * @return true to continue iteration, false to stop.
 */
bool account_iter(const void *item, void *udata __attribute__((unused))) {
    const struct account *ac = item;
    printf("ID:%2lu | %-5s | %-20s | %-8s | pts=%3d\n", ac->id, ac->name,
           ac->email, ac->nickname, ac->point);
    return true;
}

/**
 * Hash function for accounts.
 * It should only use the field(s) that constitute the key.
 *
 * @param item Pointer to the account item.
 * @param seed0 First seed for hashing.
 * @param seed1 Second seed for hashing.
 * @return Hash value based on the account ID.
 */
uint64_t account_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const struct account *ac = item;
    // The hash MUST be calculated on the same fields used in the compare
    // function. In this case, the unique key is the `id`.
    return hashmap_sip(&ac->id, sizeof(ac->id), seed0, seed1);
}

int main(void) {
    struct hashmap *map = hashmap_new(sizeof(struct account), // item size
                                      0, 0, 0,
                                      account_hash,    // hash function
                                      account_compare, // compare function
                                      NULL, NULL);

    struct account users[] = {
        {1, "Alice", "alice@cybernet.io", "ally", 120},
        {2, "Bob", "bob@cybernet.io", "bobby", 95},
        {3, "Carol", "carol@cybernet.io", "caz", 150},
    };

    for (int i = 0; i < 3; i++) {
        hashmap_set(map, &users[i]);
    }

    printf("--------- Accounts existence check (ID 1)---------\n");
    // Create a key with only the identifying field(s) populated.
    struct account key = {.id = 1};
    struct account *found = (struct account *)hashmap_get(map, &key);
    if (found) {
        // Corrected printf to reflect the lookup ID.
        printf("Lookup ID=1 -> Found: %s (%s)\n", found->name, found->email);
    } else {
        printf("Lookup ID=1 -> Not found.\n");
    }

    printf("\n--------- Accounts in Hashmap (in hashmap_scan())---------\n");
    hashmap_scan(map, account_iter, NULL);

    printf("\n--------- Accounts in Hashmap (in hashmap_iter())---------\n");
    size_t iter = 0;
    void *item;
    while (hashmap_iter(map, &iter, &item)) {
        const struct account *ac = item;
        printf("ID: %lu, Name: %s, Email: %s, Nickname: %s, Points: %d\n",
               ac->id, ac->name, ac->email, ac->nickname, ac->point);
    }

    hashmap_free(map);
    return 0;
}
