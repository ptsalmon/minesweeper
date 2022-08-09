cmake_minimum_required(VERSION 3.20)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_library(Button Button.cpp)
target_link_libraries(Button sfml-graphics sfml-audio)

add_library(GameState GameState.cpp)
target_link_libraries(GameState sfml-graphics sfml-audio)

add_library(Tile Tile.cpp)
target_link_libraries(Tile sfml-graphics sfml-audio)

add_library(Toolbox Toolbox.cpp)
target_link_libraries(Toolbox sfml-graphics sfml-audio)

set(SOURCE_FILES minesweeper.cpp minesweeper.h Button.cpp Button.h GameState.cpp GameState.h Tile.cpp Tile.h Toolbox.cpp Toolbox.h)

add_executable(minesweeper ${SOURCE_FILES})
target_link_libraries(minesweeper Toolbox sfml-graphics sfml-audio)