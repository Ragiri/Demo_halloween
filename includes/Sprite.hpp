#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Texture {
public:
    Texture() {};
    Texture(std::string path, sf::Vector2i size) {
        fromFile(path, sf::Rect<int>(0,0, size.x, size.y));
    };
    Texture(std::string path) {
        fromFile(path);
    };
    ~Texture() = default;
public:
    bool fromFile(std::string &, sf::Rect<int>);
    bool fromFile(std::string &);
    void setSmooth(bool);
public:
    sf::Texture &getTexture(void) {return this->_texture;};
    bool isSmooth(void) const {return _texture.isSmooth();};
private:
    sf::Texture _texture;
};

class Sprite {
public:
    Sprite() {};
    ~Sprite() = default;
public:
    void setPosition(sf::Vector2f);
    void setRotation(float);
    void setScale(sf::Vector2f);
    void setOrigin(sf::Vector2f);
    void setTexture(sf::Texture &/*sf::Vector2i*/);
    void setRect(sf::Rect<int>);
    void setVisible(bool);
    void setMoving(bool);
public:
    sf::Sprite &getSprite(void) {return this->_sprite;};
    bool isMove(void) const noexcept {return this->_move;};
    bool isVisible(void) const noexcept {return this->_visible;};
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _visible;
    bool _move;
};