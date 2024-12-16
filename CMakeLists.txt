cmake_minimum_required(VERSION 3.29)
project(Minesweeper)
set(CMAKE_CXX_STANDARD 26)

# Find SFML library components and set them up if you want
#find_package(SFML COMPONENTS graphics window system audio REQUIRED)
#target_link_libraries(Minesweeper sfml-graphics sfml-system)


set(SFML_DIR lib/SFML)

include_directories(include)

set (SRC
        src/game.cpp
        src/main.cpp
)
add_executable(Minesweeper
        ${SRC}
)

target_link_libraries(Minesweeper sfml-graphics sfml-window sfml-system)
