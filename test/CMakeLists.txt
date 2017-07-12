cmake_minimum_required(VERSION 3.5)

add_subdirectory(./lib/googletest)

set(gtest_SOURCE_DIR, ./lib/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp Tester.cpp )

#
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    add_executable(runTests ${TEST_SOURCE_FILES})
    target_link_libraries(runTests gtest gtest_main ${SFML_LIBRARIES} core )
    #target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} core)
endif()
#



#target_link_libraries(runTests gtest gtest_main core)