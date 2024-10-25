cmake_minimum_required(VERSION 3.29)
project(Minesweeper)
set(CMAKE_CXX_STANDARD 26)

# Find SFML library components
find_package(SFML COMPONENTS graphics window system audio REQUIRED)


set(INCLUDE_DIR include)
include_directories(${INCLUDE_DIR})


set (SRC
        src/game.cpp
        main.cpp
)

set (INCLUDE
        include/game.h)

add_executable(Minesweeper
        ${SRC}
        ${INCLUDE}
)

target_link_libraries(Minesweeper sfml-graphics sfml-system)
