PROJECT(active)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

AUX_SOURCE_DIRECTORY(. DIR_SRC)

SET(header_files
    task.h
    active.h
    active_service.h
    mirco_active_service.h
)

SET(SRC_LIST 
    ${DIR_SRC}
)

ADD_LIBRARY(active ${SRC_LIST} ${header_files})