#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Text {
public:
	Text() {
		if (!_font.loadFromFile("assets/font.ttf"))
			std::cerr << "Could not load texture" << std::endl;
	};
	~Text() = default;
	sf::Text createText(std::string str, sf::Vector2f vect, int size, sf::Color color) {
		sf::Text text(str, _font, size);
		text.setPosition(vect);
		text.setFillColor(color);
		//text.setColor(color);
		_text = text;
		return text;
	};
	void setPosition(sf::Vector2f vect) {
		_text.setPosition(vect);
	};
	sf::FloatRect getRect() {
		return _text.getGlobalBounds();
	};
	void displayText(sf::RenderWindow *window) {
		window->draw(_text);
	};

private:
	sf::Text _text;
	sf::Font _font;
};

#endif