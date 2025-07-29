# meson.build
project(
  'tidwall-hashmap-test',
  'c',
  version: '1.0',
  default_options: [
    'warning_level=3',
    'c_std=c11',
    'buildtype=debugoptimized',
  ],
)

# Build the hashmap library as a static library
hashmap_inc = include_directories('deps/hashmap.c')
hashmap_lib = static_library(
  'hashmap',
  ['deps/hashmap.c/hashmap.c'],
  include_directories: hashmap_inc,
)

app = executable(
  'tidwall-hashmap-test',
  'src/main.c',
  include_directories: hashmap_inc,
  link_with: hashmap_lib,
)
