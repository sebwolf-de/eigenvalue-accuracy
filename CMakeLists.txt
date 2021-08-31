cmake_minimum_required(VERSION 3.10)

# set the project name
project(eigen-accuracy)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(eigen3 src/eigen3.cpp)
find_package (Eigen3 REQUIRED NO_MODULE)
target_link_libraries (eigen3 Eigen3::Eigen)

include(CheckLanguage)
check_language(Fortran)
if(CMAKE_Fortran_COMPILER)
    enable_language(Fortran)
    include(FortranCInterface)
    FortranCInterface_HEADER(FC.h MACRO_NAMESPACE "FC_")

    find_package(LAPACK REQUIRED)
endif()
add_executable(lapack src/lapack.cpp)
target_include_directories(lapack PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
message(${LAPACK_LIBRARIES})
target_link_libraries(lapack PUBLIC ${LAPACK_LIBRARIES})

add_executable(armadillo src/armadillo.cpp)
find_package(Armadillo REQUIRED)
target_include_directories(armadillo PUBLIC ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(armadillo PUBLIC ${ARMADILLO_LIBRARIES})
