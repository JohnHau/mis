CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(HELLO)
INCLUDE_DIRECTORIES(./src)
AUX_SOURCE_DIRECTORY(. SRC_LIST)



set(ASTR  one_two_three)

string(REPLACE "_" "-" BSTR  ${ASTR})

message("BSTR is ${BSTR}")

add_subdirectory(./src  srcm/here/)
#MESSAGE("It is ${SRC_LIST}")
ADD_EXECUTABLE(hello ${SRC_LIST})
TARGET_LINK_LIBRARIES(hello  libbubble)
