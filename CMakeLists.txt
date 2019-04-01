################################################################################
#                                                                              #
# Copyright (C) 2019 Fondazione Istitito Italiano di Tecnologia (IIT)          #
# All Rights Reserved.                                                         #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 3.13)
project(test_thrift_py)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(YARP 3.1 REQUIRED)
foreach(_component conf OS sig dev)
  get_property(YARP_${_component}_INCLUDE_DIRS TARGET YARP::YARP_${_component} PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
  include_directories(${YARP_${_component}_INCLUDE_DIRS})
endforeach()
include_directories(${YARP_BINDINGS})

yarp_add_idl(IDL_GEN_FILES task-planning.thrift)
add_library(protocol STATIC ${IDL_GEN_FILES})
target_link_libraries(protocol YARP::YARP_OS)


add_executable(textTaskPlanningServer TextTaskPlanningServer.cpp)
target_link_libraries(textTaskPlanningServer protocol YARP::YARP_OS YARP::YARP_init)

add_executable(taskPlanningClient TaskPlanningClient.cpp)
target_link_libraries(taskPlanningClient protocol YARP::YARP_OS YARP::YARP_init)

find_package(Python3 COMPONENTS Development REQUIRED)

find_package(SWIG 3.0 REQUIRED)
include(${SWIG_USE_FILE})

set(SWIG_BINDINGS_SOURCE_FILE task-planning.i)
set_source_files_properties(${SWIG_BINDINGS_SOURCE_FILE} PROPERTIES CPLUSPLUS ON)
set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/lib/python")

set(CMAKE_SWIG_FLAGS "-py3;-O;-threads")

swig_add_library(TaskPlanning_python
                 LANGUAGE python
                 SOURCES ${SWIG_BINDINGS_SOURCE_FILE})
swig_link_libraries(TaskPlanning_python protocol Python3::Python YARP::YARP_OS YARP::YARP_sig YARP::YARP_dev)
target_include_directories(${SWIG_MODULE_TaskPlanning_python_REAL_NAME} SYSTEM PRIVATE ${PYTHON_INCLUDE_PATH})

set_target_properties(${SWIG_MODULE_TaskPlanning_python_REAL_NAME} PROPERTIES OUTPUT_NAME "TaskPlanning"
                                                                              LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/python")
