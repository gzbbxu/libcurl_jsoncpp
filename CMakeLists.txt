cmake_minimum_required (VERSION 2.6)
add_definitions(-std=c++11)
project (face_recong)

LINK_LIBRARIES(curl)
LINK_LIBRARIES(jsoncpp)

add_executable(face_recong face_recong.cpp)
