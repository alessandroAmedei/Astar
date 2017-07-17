cmake_minimum_required(VERSION 3.4)

add_subdirectory(test)
add_executable(astar main.cpp)
add_library(astar2 Node.h Map.cpp Map.h)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(astar ${SFML_LIBRARIES})
    target_link_libraries(astar2 ${SFML_LIBRARIES})
endif ()

target_link_libraries(astar astar2)
