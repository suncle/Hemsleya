project(test_ringque)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

AUX_SOURCE_DIRECTORY(. DIR_SRC)

ADD_executable(test_ringque ${DIR_SRC})
target_link_libraries(test_ringque container)