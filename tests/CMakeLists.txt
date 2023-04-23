INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/include
    ../include/
    ../extern/googletest/include
)
enable_testing()
add_subdirectory(../extern/googletest ../build/gtesting)



set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_library(JoVecsHeader INTERFACE)
target_include_directories(JoVecsHeader INTERFACE ../include/)

MACRO(CREATE_TEST test_name)
    set(binary_name "${test_name}TestBIN")
    #add_executable(${binary_name} EXCLUDE_FROM_ALL "${test_name}Test.cpp")
    add_executable(${binary_name} "${test_name}Test.cpp" )
    target_link_libraries(${binary_name} JoVecsHeader gtest gtest_main)

    add_test("${test_name}TestBIN" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${binary_name})
    #ADD_DEPENDENCIES(tests ${binary_name})
ENDMACRO()

CREATE_TEST(JoVecs)