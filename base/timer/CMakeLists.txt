PROJECT(timer)
SET(timer_src
    timer.cpp
)
SET(timer_h
    timer.h
)
ADD_LIBRARY(timer ${timer_src} ${timer_h})
