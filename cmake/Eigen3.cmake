# Once done this will define
#
#  EIGEN3_FOUND - system has eigen lib with correct version
#  EIGEN3_INCLUDE_DIR - the eigen include directory
#  EIGEN3_VERSION - eigen version

OPTION(EIGEN_EXTERNAL "load Eigen from the internet, if turned off, FindEigen.cmake or Eigen3_DIR has to be provided" ON)

if(EIGEN_EXTERNAL)
    ExternalProject_Add(
        Eigen3
        URL http://bitbucket.org/eigen/eigen/get/3.2.8.tar.bz2
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND "")

    # Specify include dir
    ExternalProject_Get_Property(Eigen3 source_dir)
    set(EIGEN3_INCLUDE_DIR ${source_dir})
else()
    find_package(Eigen3 REQUIRED)
endif()
