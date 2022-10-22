#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"

class Window {
public:
    Window(std::string name = "window") {
        _window.create(sf::VideoMode(1920, 1080), sf::String(name), sf::Style::Fullscreen);
    };
    ~Window() {
        _window.close();
    };
public:
    sf::RenderWindow *getWindow(void) {return &_window;};
public:
    void draw(sf::Sprite &sprite) {
        _window.draw(sprite);
    };
    void display(void) {
        _window.display();
    };
public:
    sf::RenderWindow _window;
};