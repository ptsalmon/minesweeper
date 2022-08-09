#include "Button.h"

// Button constructor
// Set func to _onClick with constructor intializer list
Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) : func(_onClick) {
    position = _position;

    // Dynamically allocate sprite information;
    // will be deleted when Toolbox destructor is called
    sprite = new sf::Sprite();

    sprite->setPosition(position);
}

// Position getter
sf::Vector2f Button::getPosition() {
    return position;
}

// Sprite getters and setters
sf::Sprite *Button::getSprite() {
    return sprite;
}
void Button::setSprite(sf::Sprite *_sprite) {
    _sprite->setPosition(sprite->getPosition());
    sf::Sprite* deleteMe = sprite;
    sprite = _sprite;
    delete deleteMe;
}

// onClick functionality determined by private method func
void Button::onClick() {
    func();
}
