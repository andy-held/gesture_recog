project(gesture_recognition)
cmake_minimum_required(VERSION 2.8)

include(${CMAKE_SOURCE_DIR}/cmake/CompilerConfig.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Enable ExternalProject CMake module
include(ExternalProject)
set(THIRD_PARTY_INSTALL_DIR "${CMAKE_BINARY_DIR}/3rdParty")
include(cmake/Eigen3.cmake)
include(cmake/yaml-cpp.cmake)
include(cmake/SDL2pp.cmake)

aux_source_directory(${CMAKE_SOURCE_DIR}/util UTIL_SRC_LIST)

add_library(neural_network
    neural_network/neural_network.cpp)
target_include_directories(neural_network PUBLIC
    ./neural_network
    ${EIGEN3_INCLUDE_DIR})
#target_link_libraries(neural_network)

# gesture recorder
add_executable(gesture_recorder apps/gesture_recorder.cpp ${UTIL_SRC_LIST})
target_include_directories(gesture_recorder PUBLIC
    ${SDL2PP_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${YAML_CPP_INCLUDE_DIR}
    ./util)
target_link_libraries(gesture_recorder ${SDL2PP_LIBRARIES} ${YAML_CPP_LIBRARIES})
message(STATUS " ${SDL2PP_LIBRARIES}")
add_dependencies(gesture_recorder Eigen3)

#tests
add_subdirectory(test)

