project(gesture_recognition_tests)

include(${CMAKE_SOURCE_DIR}/cmake/gtest.cmake)

add_executable(gesture_recognition_tests
    test_neural_network.cpp
    test_eigen_yaml.cpp
    test_sampling.cpp
    ${UTIL_SRC_LIST})
target_compile_options(gesture_recognition_tests PRIVATE -std=c++11)
target_include_directories(gesture_recognition_tests PRIVATE ${GTEST_INCLUDE_DIR} ${YAML_CPP_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ../util)
target_link_libraries(gesture_recognition_tests PRIVATE neural_network gtest_main gtest ${YAML_CPP_LIBRARIES} ${SDL2_LIBRARY})
