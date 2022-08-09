#include "Toolbox.h"
#include "minesweeper.h"
#include <iostream>


//Toolbox constructor
Toolbox::Toolbox() {

    //Create 800x600 render window
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Peter Salmon");


    // Button definitions
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //Debug button toggles debug mode
    debugButton = new Button(sf::Vector2f(460, 512), [](){
        toggleDebugMode();
    });

    // New game button deletes previous game (unless it was a testboard)
    // and creates a new random game
    newGameButton = new Button(sf::Vector2f(332, 512), [this](){
        restart();
        if (gameState == testboard1 || gameState == testboard2 || gameState == testboard3) {
            this->gameState = new GameState();
        } else {
            GameState* deleteMe = this->gameState;
            this->gameState = new GameState();
            delete deleteMe;
        }
    });

    // test button 1 creates a new game from boards/testboard1.brd
    // if previous board was not a test board, delete it
    testButton1 = new Button(sf::Vector2f(524, 512), [this](){
        restart();
        if (gameState == testboard1 || gameState == testboard2 || gameState == testboard3) {
            this->gameState = testboard1;
        } else {
            GameState* deleteMe = this->gameState;
            this->gameState = testboard1;
            delete deleteMe;
        }
    });

    // test button 2 creates a new game from boards/testboard2.brd
    // if previous board was not a test board, delete it
    testButton2 = new Button(sf::Vector2f(588, 512), [this](){
        restart();
        if (gameState == testboard1 || gameState == testboard2 || gameState == testboard3) {
            this->gameState = testboard2;
        } else {
            GameState* deleteMe = this->gameState;
            this->gameState = testboard2;
            delete deleteMe;
        }
    });

    // test button 3 creates a new game from boards/testboard3.brd
    // if previous board was not a test board, delete it
    testButton3 = new Button(sf::Vector2f(652, 512), [this](){
        restart();
        if (gameState == testboard1 || gameState == testboard2 || gameState == testboard3) {
            this->gameState = testboard3;
        } else {
            GameState* deleteMe = this->gameState;
            this->gameState = testboard3;
            delete deleteMe;
        }
    });

    // Load all textures in alphabetical order
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    textureMap["debug"] = sf::Texture();
    textureMap["debug"].loadFromFile("images/debug.png");
    textureMap["digits"] = sf::Texture();
    textureMap["digits"].loadFromFile("images/digits.png");
    textureMap["happy"] = sf::Texture();
    textureMap["happy"].loadFromFile("images/face_happy.png");
    textureMap["lose"] = sf::Texture();
    textureMap["lose"].loadFromFile("images/face_lose.png");
    textureMap["win"] = sf::Texture();
    textureMap["win"].loadFromFile("images/face_win.png");
    textureMap["flag"] = sf::Texture();
    textureMap["flag"].loadFromFile("images/flag.png");
    textureMap["mine"] = sf::Texture();
    textureMap["mine"].loadFromFile("images/mine.png");

    // for loops load number textures
    for (int i=1; i<=8; i++) {
        std::string iString = std::to_string(i);
        textureMap[iString] = sf::Texture();
        textureMap[iString].loadFromFile("images/number_" + iString + ".png");
    }

    // load remaining textures
    textureMap["test_1"] = sf::Texture();
    textureMap["test_1"].loadFromFile("images/test_1.png");
    textureMap["test_2"] = sf::Texture();
    textureMap["test_2"].loadFromFile("images/test_2.png");
    textureMap["Test_3"] = sf::Texture();
    textureMap["Test_3"].loadFromFile("images/Test_3.png");
    textureMap["hidden"] = sf::Texture();
    textureMap["hidden"].loadFromFile("images/tile_hidden.png");
    textureMap["revealed"] = sf::Texture();
    textureMap["revealed"].loadFromFile("images/tile_revealed.png");
}

// Toolbox destructor
Toolbox::~Toolbox() {

    // Delete all toolbox pointer attributes and
    // associated sprites, if applicable
    delete testboard1;
    delete testboard2;
    delete testboard3;
    delete debugButton->getSprite();
    delete debugButton;
    delete newGameButton->getSprite();
    delete newGameButton;
    delete testButton1->getSprite();
    delete testButton1;
    delete testButton2->getSprite();
    delete testButton2;
    delete testButton3->getSprite();
    delete testButton3;


    //Delete all tiles stored in gameState
    for (int j=0; j<boardDimensions.y; j++) {
        for (int i=0; i<boardDimensions.x; i++) {
            delete gameState->getTile(i,j);
        }
    }
    delete gameState;
}
