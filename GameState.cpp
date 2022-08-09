#include "GameState.h"
#include "Toolbox.h"
#include <fstream>
#include <iostream>

using namespace std;

// Default gamestate constructor constructs a random board
// based on dimensions and numberOfMines by calling resetBoard
GameState::GameState(sf::Vector2f _dimensions, int _numberOfMines) {
    resetBoard(_numberOfMines,_dimensions);
}

// Second gamestate constructor makes a new gamestate
// by loading from specified filepath
GameState::GameState(const char *filepath) {
    Toolbox* toolbox = Toolbox::getInstance();

    // Read board data to a string
    std::vector<std::string> boardData;
    ifstream file(filepath, std::ios_base::binary);
    string nextln;
    while (file.good()) {
        file >> nextln;
        boardData.push_back(nextln);
    }

    toolbox->boardDimensions.x = boardData[0].size();
    toolbox->boardDimensions.y = boardData.size();

    // Convert boardData from string to 2d tile vector
    for (int j=0; j<toolbox->boardDimensions.y; j++) {
        vector<Tile> nextRow;
        for (int i=0; i<toolbox->boardDimensions.x; i++) {
            Tile currentTile(sf::Vector2f(i,j));
            if (boardData[j][i] == '1') {
                currentTile.setMine();
                mineCount++;
            }
            nextRow.push_back(currentTile);
        }
        tiles.push_back(nextRow);
    }
}

// getFlagCount counts the number of flags
int GameState::getFlagCount() {
    flagCount = 0;
    for (int j=0; j<tiles.size(); j++) {
        for (int i=0; i<tiles[j].size(); i++) {
            if (tiles[j][i].getState() == Tile::FLAGGED) {
                flagCount++;
            }
        }
    }
    return flagCount;
}

// Returns number of mines on the board
int GameState::getMineCount() {
    return mineCount;
}

// Returns pointer to a tile at designated location
// If invalid location, return nullptr
Tile *GameState::getTile(int x, int y) {
    Toolbox* toolbox = Toolbox::getInstance();
    if (x > toolbox->boardDimensions.x-1 || y > toolbox->boardDimensions.y-1 || y < 0 || x < 0 ) return nullptr;
    return &(tiles[y][x]);
}

// playStatus getters and setters
GameState::PlayStatus GameState::getPlayStatus() {
    return playStatus;
}
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    playStatus = _status;
}

// resetBoard function makes a new random board with
// specificed number of mines and dimensions
void GameState::resetBoard(int mines, sf::Vector2f _dimensions) {
    Toolbox* toolbox = Toolbox::getInstance();

    mineCount = mines;
    int size = _dimensions.x * _dimensions.y;
    string boardData = (string(mines,'1') + string(size-mines,'0'));
    random_shuffle(boardData.begin(), boardData.end());
    tiles.clear();
    for (int j=0; j<_dimensions.y; j++) {
        vector<Tile> nextRow;
        for (int i=0; i<_dimensions.x; i++) {
            Tile currentTile(sf::Vector2f(i,j));
            if (boardData[j*_dimensions.x+i] == '1') {
                currentTile.setMine();
            }
            nextRow.push_back(currentTile);
        }
        tiles.push_back(nextRow);
    }
    toolbox->boardDimensions = _dimensions;
}

