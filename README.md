# tidwall-hashmap-test

> An example(sample) project using tidwall/hashmap.c


### build and run
1. First of all, clone the repository with `--recursive` option because it contains a Git submodule.
```shell
git clone --recursive git@github.com:KnightChaser/tidwall-hashmap-test.git
```

2. Using Meson (The C/C++ build system), setup the build directory and build the source, then execute the compiled binary.
```shell
meson setup builddir --native-file=clang.ini
cd builddir
meson compile
./tidwall-hashmap-test
```
