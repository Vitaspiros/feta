cmake_minimum_required(VERSION 3.30)

set(CMAKE_BUILD_TYPE DEBUG)

project(greek_typo_checker)

# Syllable counter
add_executable(counter src/letter.c src/syllable.c src/counter.c)