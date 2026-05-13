cmake_minimum_required(VERSION 3.20)

project(matrix LANGUAGES CXX)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(
    Sources
    src/main.cpp
    src/quaternion.cpp
 "src/vec3.cpp")

set(
    Headers 
    include/quaternion.h
 "include/vec3.h")

add_library(matrix_lib STATIC ${Sources} ${Headers})

if (MSVC)
    target_compile_options(matrix_lib PRIVATE
        /external:W0
        /external:anglebrackets
        /analyze:external-
    )
endif()

target_include_directories(matrix_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(matrix_lib PUBLIC cxx_std_20)

add_executable(matrix 
    src/main.cpp 
)

target_link_libraries(matrix 
    matrix_lib
)


add_subdirectory(testing)