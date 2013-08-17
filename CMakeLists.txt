PROJECT(Hemsleya)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

find_package(Boost)
if (Boost_FOUND)
	link_directories(${Boost_INCLUDE_DIR}//stage//lib)
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
endif (Boost_FOUND)

MESSAGE(STATUS "This is BOOST lib dir " ${Boost_LIBRARIES})  
MESSAGE(STATUS "This is BOOST include dir " ${Boost_INCLUDE_DIR})  

MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})  
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})  

set(Hemsleya_include_path "${PROJECT_SOURCE_DIR}\\../build/bin/Debug" CACHE PATH "Hemsleya include path")
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}\\..)

set(Hemsleya_lib_path "${PROJECT_BINARY_DIR}\\../build/bin/Debug" CACHE PATH "Hemsleya lib path")
link_directories(${Hemsleya_lib_path})

MESSAGE(STATUS "This is BINARY dir " ${Hemsleya_lib_path}) 

set(Hemsleya_bin_path ${PROJECT_BINARY_DIR}/../build/bin CACHE PATH "Hemsleya bin path")
ADD_SUBDIRECTORY(base ${Hemsleya_bin_path})
ADD_SUBDIRECTORY(test ${Hemsleya_bin_path}//test)