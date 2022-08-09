#include <iostream>
#include "Tile.h"
#include <array>
#include "Toolbox.h"

using namespace std;

Toolbox* toolbox = Toolbox::getInstance();

// Tile constructor
Tile::Tile(sf::Vector2f position) {
    location = position;
    sf::Vector2f windowPos = location*32.0f;

    // Set tile sprites based on position parameter
    sprite.setPosition(windowPos);
    number.setPosition(windowPos);
    flag.setPosition(windowPos);
    mine.setPosition(windowPos);
}

// Tile state getter
Tile::State Tile::getState() {
    return currentState;
}

// Tile state setter
void Tile::setState(Tile::State _state) {
    currentState = _state;
}

// Returns array containing tile's neighbors
array<Tile*,8> &Tile::getNeighbors() {
    //Replace existing neighbors array with nullptrs
    neighbors.fill(nullptr);

    // Messy for-loop gets every neighbor with some math
    for (int j=0; j<3; j++) {
        for (int i=0; i<3; i++) {
            Tile* neighborTile = toolbox->gameState->getTile(location.x-1+i,location.y-1+j);
            if (j*3+i < 4) {
                neighbors[j*3+i] = neighborTile;
            } else if (j*3+i > 4) {
                neighbors[j*3+i-1] = neighborTile;
            }
        }
    }

    // Count adjacent mines to update adjacentMines attribute
    // and update number sprite accordingly
    adjacentMines = 0;
    for (int i=0; i<8; i++) {
        if (neighbors[i] != nullptr) {
            if (neighbors[i]->getMine()) adjacentMines++;
        }
    }
    if (adjacentMines > 0) {
        number.setTexture(toolbox->textureMap[to_string(adjacentMines)]);
    }

    // return update neighbor array
    return neighbors;
}

// neighbors setter
void Tile::setNeighbors(array<Tile*,8> _neighbors) {
    neighbors = _neighbors;
}

// Define behavior for when a tile is clicked on
void Tile::onClickLeft() {
    // Flagged tiles cannot be left clicked
    if (currentState != FLAGGED) {

        // Check if tile contains a mine
        // If so, tile is revealed and game is lost
        if (isMine) {
            currentState = State::EXPLODED;
            sprite.setTexture(toolbox->textureMap["revealed"]);
            toolbox->gameState->setPlayStatus(toolbox->gameState->LOSS);
        } else {

            // Reveal tile and neighbors, if tile has no adjacent mines
            currentState = State::REVEALED;
            sprite.setTexture(toolbox->textureMap["revealed"]);
            getNeighbors();
            if (adjacentMines == 0) {
                revealNeighbors();
            }

            // Check if game has been won
            GameState::PlayStatus testStatus = GameState::WIN;
            for (int i=0; i < toolbox->boardDimensions.x; i++) {
                for (int j=0; j<toolbox->boardDimensions.y; j++) {
                    Tile* currentTile = toolbox->gameState->getTile(i,j);
                    if (!currentTile->isMine && (currentTile->currentState == HIDDEN || currentTile->currentState == FLAGGED)) {
                        testStatus = GameState::PLAYING;
                    }
                }
            }

            // If every non-mine tile has been revealed, game has been won
            if (testStatus == GameState::WIN) {
                toolbox->gameState->setPlayStatus(GameState::WIN);
            }
        }
    }
}


// Define right click behavior
void Tile::onClickRight() {
    // Toggle flag, if tile is not revealed or exploded
    if (currentState != REVEALED && currentState != EXPLODED) {
        (currentState == FLAGGED) ? currentState = HIDDEN : currentState = FLAGGED;
    }
}

// Draw tile based on currentState
void Tile::draw() {
    if (currentState == HIDDEN) {

        sprite.setTexture(toolbox->textureMap["hidden"]);
        toolbox->window.draw(sprite);

    } else if (currentState == REVEALED) {

        sprite.setTexture(toolbox->textureMap["revealed"]);
        toolbox->window.draw(sprite);

        number.setTexture(toolbox->textureMap[to_string(adjacentMines)]);
        toolbox->window.draw(number);

    } else if (currentState == FLAGGED) {

        sprite.setTexture(toolbox->textureMap["hidden"]);
        toolbox->window.draw(sprite);

        flag.setTexture(toolbox->textureMap["flag"]);
        toolbox->window.draw(flag);

    } else if (currentState == EXPLODED) {

        sprite.setTexture(toolbox->textureMap["revealed"]);
        toolbox->window.draw(sprite);

        mine.setTexture(toolbox->textureMap["mine"]);
        toolbox->window.draw(mine);

    }
}

// Location getter
sf::Vector2f Tile::getLocation() {
    return location;
}

// isMine getters and setters
void Tile::setMine() {
    isMine ? isMine = false : isMine = true;
}
bool Tile::getMine() {
    return isMine;
}

// Reveal neighbors method
void Tile::revealNeighbors() {
    for (int i=0; i<8; i++) {
        if (neighbors[i] != nullptr && !neighbors[i]->getMine() && neighbors[i]->getState() != REVEALED) {
            neighbors[i]->setState(REVEALED);
            neighbors[i]->onClickLeft();
        }
    }
}