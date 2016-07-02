project(gesture_recognition)
cmake_minimum_required(VERSION 2.8)

include(${CMAKE_SOURCE_DIR}/cmake/CompilerConfig.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)

find_package(SDL2 REQUIRED)
SET(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
SET(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
SET(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
ADD_SUBDIRECTORY(3rdparty/libSDL2pp)

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
    ${SDL2_INCLUDE_DIR}
    ${SDL2PP_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${YAML_CPP_INCLUDE_DIR}
    ./util)
target_link_libraries(gesture_recorder ${SDL2_LIBRARY} ${SDL2PP_LIBRARIES} ${YAML_CPP_LIBRARIES})

#tests
add_subdirectory(test)

