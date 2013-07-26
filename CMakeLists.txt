PROJECT(Hemsleya)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

find_package(Boost)
if (Boost_FOUND)
	link_directories(${Boost_LIBRARIES})
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
endif (Boost_FOUND)

INCLUDE_DIRECTORIES(..)

MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})  

set(Hemsleya_lib_path "${PROJECT_BINARY_DIR}\\../build/bin/Debug" CACHE PATH "Hemsleya lib path")
link_directories(${Hemsleya_lib_path})

MESSAGE(STATUS "This is BINARY dir " ${Hemsleya_lib_path}) 

set(Hemsleya_bin_path ${PROJECT_BINARY_DIR}/../build/bin CACHE PATH "Hemsleya bin path")
ADD_SUBDIRECTORY(base ${Hemsleya_bin_path})