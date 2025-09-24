cmake_minimum_required(VERSION 3.30)

set(CMAKE_BUILD_TYPE DEBUG)

project(feta)

add_library(feta src/letter.c src/syllable.c src/tables.c)

# Syllable counter
add_executable(feta-count src/counter/counter.c)
target_include_directories(feta-count PUBLIC src)
target_link_libraries(feta-count PUBLIC feta)

# Typo checker
add_executable(feta-check src/checker/checker.c src/checker/mistake.c)
target_include_directories(feta-check PUBLIC src)
target_link_libraries(feta-check PUBLIC feta)

# Syllable counter tester
add_executable(feta-test src/tester/tester.c)
target_include_directories(feta-test PUBLIC src)
target_link_libraries(feta-test PUBLIC feta)
target_link_libraries(feta-test PRIVATE ncursesw)