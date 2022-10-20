// #define TEXT_HPP
// #ifndef TEXT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Text {
public:
	Text(std::string filename) {
		if (!_font.loadFromFile(filename))
			std::cerr << "Could not load texture" << std::endl;
	};
	~Text() = default;
	void createText(std::string str, sf::Vector2f vect, int size, sf::Color color) {
		sf::Text text(str, _font, size);
		text.setPosition(vect);
		text.setColor(color);
		_text = text;
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
}

// #endif