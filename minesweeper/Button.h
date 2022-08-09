#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

// Button class
class Button {
    // Private attributes and functions
    sf::Vector2f position;
    sf::Sprite* sprite;
    // func stores onClick from button constructor
    std::function<void(void)> func;
public:
    // Public methods and attributes based on spec
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
};