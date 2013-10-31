cmake_minimum_required(VERSION 2.8)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set( CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "Configurations" FORCE )
project( ${SOLUTION_NAME} )
include( environment.cmake required )

modules( binary_reader )
binaries( 3_4_bad_data_chanell 3_5_parallel_queues 3_6_divided_datafeed )

compile()
