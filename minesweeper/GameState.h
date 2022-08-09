#include <SFML/Graphics.hpp>
#include "Tile.h"

#pragma once


// GameState class
class GameState {
public:
    // Public methods and attributes based on spec
    enum PlayStatus { WIN, LOSS, PLAYING };
    GameState(sf::Vector2f _dimensions = sf::Vector2f(25,16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
private:
    // Private attributes track the number of mines and flags,
    // playStatus, and stores tile data
    int mineCount = 0;
    int flagCount = 0;
    PlayStatus playStatus = PLAYING;
    std::vector<std::vector<Tile>> tiles;

    // private resetBoard method is a minor abstraction
    // that makes the code a little cleaner visually
    void resetBoard(int mines, sf::Vector2f _dimensions);
};