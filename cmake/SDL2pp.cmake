########################### yaml-cpp

# Once done this will define
#
#  SDL2PP_FOUND
#  SDL2PP_INCLUDE_DIRS
#  SDL2PP_LIBRARIES

OPTION(SDL2PP_EXTERNAL "load Eigen from the internet, if turned off, FindEigen.cmake or Eigen3_DIR has to be provided" ON)

find_package(SDL2 REQUIRED)

if(SDL2PP_EXTERNAL)
    ExternalProject_Add(
        SDL2pp-ext
        GIT_REPOSITORY https://github.com/libSDL2pp/libSDL2pp.git
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
                   -DSDL2PP_WITH_IMAGE=ON
                   -DSDL2PP_WITH_MIXER=ON
                   -DSDL2PP_WITH_TTF=ON
                   -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_INSTALL_DIR}
        INSTALL_DIR ${THIRD_PARTY_INSTALL_DIR}
        )

    # Specify include dir
    ExternalProject_Get_Property(SDL2pp-ext INSTALL_DIR)
    set(SDL2PP_INCLUDE_DIRS ${INSTALL_DIR}/include ${SDL2_INCLUDE_DIR})

    # Library
    set(SDL2PP_LIBRARY SDL2pp)
    add_library(${SDL2PP_LIBRARY} SHARED IMPORTED)
    set_property(TARGET ${SDL2PP_LIBRARY} APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
    set_target_properties(${SDL2PP_LIBRARY} PROPERTIES IMPORTED_LOCATION_RELEASE "${INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}SDL2pp.so")
    add_dependencies(${SDL2PP_LIBRARY} SDL2pp-ext SDL2)

    set(SDL2PP_LIBRARIES ${SDL2_LIBRARY} ${SDL2PP_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
else()
    find_package(SDL2pp REQUIRED)
endif()
