#include "minesweeper.h"
#include "Toolbox.h"
#include <iostream>

using namespace std;

// Initialize toolbox singleton
Toolbox Toolbox::tb;

int launch() {
    Toolbox* toolbox = Toolbox::getInstance();

    // Set gameState to a new random game state
    toolbox->gameState = new GameState();

    // Start main program loop
    gameLoop();

    return 0;
};

// Render method draws every button and tile
void render() {
    Toolbox* toolbox = Toolbox::getInstance();

    // Draw tiles based on current state and mine
    for (int j=0; j < toolbox->boardDimensions.y; j++) {
        for (int i=0; i < toolbox->boardDimensions.x; i++) {
            Tile* currentTile = toolbox->gameState->getTile(i,j);
            currentTile->draw();
            if (toolbox->debugMode && currentTile->getMine()) {
                sf::Sprite mine(toolbox->textureMap["mine"]);
                mine.setPosition(currentTile->getLocation()*32.0f);
                toolbox->window.draw(mine);
            }
        }
    }

    // Draw debug button
    toolbox->debugButton->getSprite()->setTexture(toolbox->textureMap["debug"]);
    toolbox->window.draw(*toolbox->debugButton->getSprite());

    // Draw new game button
    switch(toolbox->gameState->getPlayStatus()) {
        case (GameState::PLAYING):
            toolbox->newGameButton->setSprite(new sf::Sprite(toolbox->textureMap["happy"]));
            break;
        case (GameState::WIN):
            toolbox->newGameButton->setSprite(new sf::Sprite(toolbox->textureMap["win"]));
            break;
        case (GameState::LOSS):
            toolbox->newGameButton->setSprite(new sf::Sprite(toolbox->textureMap["lose"]));
            break;
    }
    toolbox->window.draw(*toolbox->newGameButton->getSprite());

    // Draw test buttons
    toolbox->testButton1->getSprite()->setTexture(toolbox->textureMap["test_1"]);
    toolbox->window.draw(*toolbox->testButton1->getSprite());
    toolbox->testButton2->getSprite()->setTexture(toolbox->textureMap["test_2"]);
    toolbox->window.draw(*toolbox->testButton2->getSprite());
    toolbox->testButton3->getSprite()->setTexture(toolbox->textureMap["Test_3"]);
    toolbox->window.draw(*toolbox->testButton3->getSprite());

    // Draw counter in bottom left
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Count to be displayed = difference between total mines and flags placed
    int count = toolbox->gameState->getMineCount() - toolbox->gameState->getFlagCount();

    // Count is converted to a string to access each digit
    sf::Sprite digit1(toolbox->textureMap["digits"]), digit2(toolbox->textureMap["digits"]), digit3(toolbox->textureMap["digits"]);
    if (count >= 0) {
        string countString = to_string(count);
        switch (countString.size()) {
            case 1:
                countString = "00" + countString;
                break;
            case 2:
                countString = "0" + countString;
                break;
        }
        digit1.setTextureRect(sf::IntRect((countString[0]-48)*21,0,21,32));
        digit2.setTextureRect(sf::IntRect((countString[1]-48)*21,0,21,32));
        digit3.setTextureRect(sf::IntRect((countString[2]-48)*21,0,21,32));
    } else {
        count *= -1;
        string countString = to_string(count);
        switch (countString.size()) {
            case 1:
                countString = "-0" + countString;
                break;
            case 2:
                countString = "-" + countString;
                break;
        }
        digit1.setTextureRect(sf::IntRect(210,0,21,32));
        digit2.setTextureRect(sf::IntRect((countString[1]-48)*21,0,21,32));
        digit3.setTextureRect(sf::IntRect((countString[2]-48)*21,0,21,32));
    }
    // Set position of digits and draw them
    digit1.setPosition(0,512); digit2.setPosition(21,512); digit3.setPosition(42,512);
    toolbox->window.draw(digit1); toolbox->window.draw(digit2); toolbox->window.draw(digit3);
}

// Toggle debug mode switches debug mode on/off
void toggleDebugMode() {
    Toolbox* toolbox = Toolbox::getInstance();
    getDebugMode() ? toolbox->debugMode = false : toolbox->debugMode = true;
}

// Main program loop
int gameLoop() {
    Toolbox* toolbox = Toolbox::getInstance();

    // While loop is responsible for polling and event handling
    while (toolbox->window.isOpen()) {
        sf::Event event;
        while (toolbox->window.pollEvent(event)) {
            // If window closed, end program
            if (event.type == sf::Event::Closed) {
                toolbox->window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {

                // If mouse clicked, check which button was clicked
                auto mousePosInt = sf::Mouse::getPosition(toolbox->window);
                sf::Vector2f mousePos(mousePosInt.x,mousePosInt.y);

                if (toolbox->newGameButton->getSprite()->getGlobalBounds().contains(mousePos)) {
                    toolbox->newGameButton->onClick();
                } else if (toolbox->debugButton->getSprite()->getGlobalBounds().contains(mousePos)) {
                    toolbox->debugButton->onClick();
                } else if (toolbox->testButton1->getSprite()->getGlobalBounds().contains(mousePos)) {
                    toolbox->testButton1->onClick();
                } else if (toolbox->testButton2->getSprite()->getGlobalBounds().contains(mousePos)) {
                    toolbox->testButton2->onClick();
                } else if (toolbox->testButton3->getSprite()->getGlobalBounds().contains(mousePos)) {
                    toolbox->testButton3->onClick();
                }

                // If no buttons were clicked, check if a tile was clicked
                // call onClickRight or onClickLeft function
                for (int j=0; j<toolbox->boardDimensions.y; j++) {
                    for (int i=0; i<toolbox->boardDimensions.x; i++) {
                        Tile* currentTile = toolbox->gameState->getTile(i,j);
                        auto spritePos = currentTile->getLocation()*32.0f;
                        sf::FloatRect bounds(spritePos,sf::Vector2f(32,32));
                        if (bounds.contains(mousePos) && toolbox->gameState->getPlayStatus() == toolbox->gameState->PLAYING) {
                            event.mouseButton.button ? currentTile->onClickRight() : currentTile->onClickLeft();
                        }
                    }
                }
            }
        }
        // Clear window and call render function
        toolbox->window.clear(sf::Color(255,255,255,255));
        render();
        toolbox->window.display();
    }

    return 0;
}

// Restart game method
// Set playStatus to playing, and hide every tile
void restart() {
    Toolbox* toolbox = Toolbox::getInstance();

    toolbox->gameState->setPlayStatus(GameState::PLAYING);

    if (getDebugMode()) toggleDebugMode();

    for (int i=0; i<toolbox->boardDimensions.x; i++) {
        for (int j=0; j<toolbox->boardDimensions.y; j++) {
            toolbox->gameState->getTile(i,j)->setState(Tile::HIDDEN);
        }
    }
}

// Returns true if debug mode is active, false otherwise
bool getDebugMode() {
    Toolbox* toolbox = Toolbox::getInstance();

    return toolbox->debugMode;
}

// main calls launch() function, beginning program
int main() { return launch(); }
