cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)
project (face_recong)



#将要构建的目标平台
set(CMAKE_SYSTEM_NAME Linux)
#将要构建的目标架构
set(CMAKE_SYSTEM_PROCESSOR arm)

#设置所用编译器
set(tools /opt/hisi-linux/x86-arm/arm-himix200-linux)
set(CMAKE_C_COMPILER ${tools}/bin/arm-himix200-linux-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-himix200-linux-g++)

#定义编译器查找头文件和库文件目录
SET(CMAKE_FIND_ROOT_PATH "/opt/hisi-linux/x86-arm/arm-himix200-linux")

#表示不在主机目录里面搜索头文件和库文件
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

#只在CMAKE_FIND_ROOT_PATH定义的目录中搜索lib库和头文件
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINK_FLAGS "-Wl -hash-style=sysv")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive -Wwrite-strings")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wwrite-strings")

#参与编译的文件
file(GLOB_RECURSE srcs "src/*.cpp")
#添加头文件搜索目录
link_directories(${CMAKE_CURRENT_LIST_DIR}/include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/include/curl)
link_directories(${CMAKE_CURRENT_LIST_DIR}/include/json)

#添加库文件搜索目录
link_directories(${CMAKE_SOURCE_DIR}/libs)


message(${CMAKE_CURRENT_LIST_DIR}/include)
LINK_LIBRARIES(curl)
#LINK_LIBRARIES(jsoncpp)
LINK_LIBRARIES(pthread)



#message(${src})  
add_executable(face_recong 
 			  ${srcs})
