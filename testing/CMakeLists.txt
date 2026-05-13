cmake_minimum_required(VERSION 3.20)

set(
	this
	matrix_tests 
)

set(
	Sources
	src/tests.cpp
)

set(
	Headers
	../include/quaternion.h
)

add_executable(${this}
	${Sources}
	${Headers}
)

if (MSVC)
    target_compile_options(${this} PRIVATE
        /external:W0
        /external:anglebrackets
        /analyze:external-
    )
endif()

target_link_libraries(${this}
	gtest_main 
	matrix_lib
)

add_test(
	NAME ${this}
	COMMAND ${this}
)
