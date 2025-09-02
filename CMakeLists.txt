cmake_minimum_required(VERSION 3.30)

set(CMAKE_BUILD_TYPE DEBUG)

project(greek_typo_checker)

add_library(typo_checker src/letter.c src/syllable.c)

# Syllable counter
add_executable(counter src/counter/counter.c)
target_include_directories(counter PUBLIC src)
target_link_libraries(counter PUBLIC typo_checker)

# Syllable counter tester
add_executable(tester src/tester/tester.c)
target_include_directories(tester PUBLIC src)
target_link_libraries(tester PUBLIC typo_checker)
target_link_libraries(tester PRIVATE ncursesw)