########################### yaml-cpp

# Once done this will define
#
#  YAML_CPP_INCLUDE_DIR - include directory
#  YAML_CPP_LIBRARIES    - libraries to link against

OPTION(YAML-CPP_EXTERNAL "load yaml-cpp from the internet, if turned off, FindYAML-CPP.cmake or YAML-CPP_DIR has to be provided" ON)

if(YAML-CPP_EXTERNAL)
    ExternalProject_Add(
        yaml-cpp-ext
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.5.3
        # TIMEOUT 10
        CMAKE_ARGS -DBUILD_SHARED_LIBS=ON
                   -DCMAKE_BUILD_TYPE=Release
                   -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_INSTALL_DIR}
        INSTALL_DIR ${THIRD_PARTY_INSTALL_DIR})

    # Specify include dir
    ExternalProject_Get_Property(yaml-cpp-ext INSTALL_DIR)
    set(YAML_CPP_INCLUDE_DIR ${INSTALL_DIR}/include)

    # Library
    set(YAML_CPP_LIBRARY yaml-cpp)
    add_library(${YAML_CPP_LIBRARY} SHARED IMPORTED)
    set_property(TARGET ${YAML_CPP_LIBRARY} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
    set_target_properties(${YAML_CPP_LIBRARY} PROPERTIES IMPORTED_LOCATION_RELEASE "${INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}yaml-cpp.so")
    add_dependencies(${YAML_CPP_LIBRARY} yaml-cpp-ext)

    set(YAML_CPP_LIBRARIES ${YAML_CPP_LIBRARY})
else()
    find_package(yaml-cpp REQUIRED)
endif()
