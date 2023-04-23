cmake_minimum_required(VERSION 3.0.0)
project(PyJonsics VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DOTESTING FALSE)


include(CTest)
enable_testing()



add_library(JoVecs INTERFACE)
target_include_directories(JoVecs INTERFACE include/)


add_library(JoVectors src/JoVecs.cpp)
target_link_libraries(JoVectors JoVecs)


add_executable(PyJonsics src/PyJonsics.cpp)
target_link_libraries(PyJonsics JoVectors)




if(DOTESTING)
    add_subdirectory(tests)
endif(DOTESTING)







set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
