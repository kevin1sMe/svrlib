cmake_minimum_required(VERSION 3.1)

project(timer)

#---------- boost asio timer ------------

SET(BOOST_DIR /usr/local/boost/include)
INCLUDE_DIRECTORIES(${BOOST_DIR})

SET(SRC_ASIO_LIST boost_asio_timer.cpp) 

ADD_EXECUTABLE(boost_asio_timer ${SRC_ASIO_LIST})

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so")
FIND_LIBRARY(BOOST_SYSTEM 
    NAMES libboost_system
    PATHS /usr/local/boost/lib
    NO_DEFAULT_PATH)
IF(BOOST_SYSTEM)
    MESSAGE(STATUS "-------find boost_system path is ${BOOST_SYSTEM}")
    TARGET_LINK_LIBRARIES(boost_asio_timer ${BOOST_SYSTEM})
ELSE(BOOST_SYSTEM)
    MESSAGE(FATAL "*******cannot find boost_system")
ENDIF(BOOST_SYSTEM)

#---------------------------------------------

#--------------time wheel ---------------------
SET(SRC_LIST time_wheel_test.cpp time_wheel.hpp)
ADD_EXECUTABLE(time_wheel_test ${SRC_LIST})

