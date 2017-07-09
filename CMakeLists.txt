#[[
cmake_minimum_required(VERSION 3.6)
project(sfml)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(sfml ${SOURCE_FILES})
]]
cmake_minimum_required(VERSION 3.4)

# Define sources and executable

set(EXECUTABLE_NAME "astar")
add_executable(${EXECUTABLE_NAME} main.cpp)

# Detect and add SFML

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()