cmake_minimum_required(VERSION 3.10)
project(LaboSpring2025)
add_compile_options(-Wno-analyzer-use-of-uninitialized-value)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test)
