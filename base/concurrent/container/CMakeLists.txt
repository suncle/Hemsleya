PROJECT(container)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

AUX_SOURCE_DIRECTORY(. DIR_SRC)
AUX_SOURCE_DIRECTORY(detail DIR_SRC_detail)

SET(header_files
    detail//_hazard_ptr.h
    concurrent_interval_table.h
    msque.h
    no_blocking_pool.h
    optimistic_queue.h
    ringque.h
    swapque.h
)

SET(SRC_LIST 
    ${DIR_SRC}
    ${DIR_SRC_detail}
)

ADD_LIBRARY(container ${SRC_LIST} ${header_files})