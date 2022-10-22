#include "../includes/Sprite.hpp"

void Sprite::setPosition(sf::Vector2f pos) {
    _sprite.setPosition(pos);
}

void Sprite::setRotation(float rotate) {
    _sprite.setRotation(rotate);
}

void Sprite::setScale(sf::Vector2f scale) {
    _sprite.setScale(scale);
}

void Sprite::setOrigin(sf::Vector2f pos) {
    _sprite.setOrigin(pos);
}

void Sprite::setTexture(sf::Texture &cpy/*sf::Vector2i set le rect direct a voir*/) {
    _texture = cpy;
    _sprite.setTexture(_texture);
}

void Sprite::setRect(sf::Rect<int> rect) {
    _sprite.setTextureRect(rect);
}

void Sprite::setVisible(bool visible) {
    _visible = visible;
}

void Sprite::setMoving(bool move) {
    _move = move;
}

bool Texture::fromFile(std::string &path, sf::Rect<int> rect) {
    if (_texture.loadFromFile(path, rect)) {
        std::cout << "load" << std::endl;
        return true;
    }
    std::cerr << "error opening File : " << path << std::endl;
    return false;
}

bool Texture::fromFile(std::string &path) {
    if (_texture.loadFromFile(path)) {
        std::cout << "load" << std::endl;
        return true;
    }
    std::cerr << "error opening File : " << path << std::endl;
    return false;
}


void Texture::setSmooth(bool smooth) {
    _texture.setSmooth(smooth);
}