#include <SFML/Graphics.hpp>

#pragma once


// Tile class
class Tile {
public:
    //Public methods and attributes from spec
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*,8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*,8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();

    // setMine and getMine added from Teams
    void setMine();
    bool getMine();
protected:
    void revealNeighbors();
private:

    // Private attribrutes
    int adjacentMines = 0;
    bool isMine = false;
    State currentState = HIDDEN;

    // Neighbors array
    std::array<Tile*,8> neighbors;

    // Location of tile
    sf::Vector2f location;

    // Relevant tile sprites
    sf::Sprite sprite, number, flag, mine;
};