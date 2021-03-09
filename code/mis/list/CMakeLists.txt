cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0011 NEW)
cmake_policy(SET CMP0053 OLD)

set(_PROJECT_ LIST C CXX ASM)

AUX_SOURCE_DIRECTORY(. SRC_LIST)
project(LIST C CXX ASM)

add_executable(list
${SRC_LIST}
		)
