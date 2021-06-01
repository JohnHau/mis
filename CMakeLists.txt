cmake_minimum_required(VERSION 3.10)

project(Tutorial)
#option(USE_A "test a" ON)
configure_file(
"${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
"${CMAKE_CURRENT_SOURCE_DIR}/config.h"
	      )


if (USE_A)
	message("hello A")
endif (USE_A)






add_executable(Tutorial tutorial.c)
