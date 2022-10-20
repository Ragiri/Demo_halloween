//#define _SPRITE_HPP
//#ifndef _SPRITE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Object
{
public:
	Object(std::string filename, std::pair<int, int> rect_pos, std::pair<int, int> rect_size) {
		if (!_Texture.loadFromFile(filename))
			std::cerr << "Could not load texture" << std::endl;
		_Sprite.setTexture(_Texture);
		_Sprite.setTextureRect(sf::IntRect(rect_pos.first, rect_pos.second, rect_size.first, rect_size.second));
		_display = true;
	};
	~Object() = default;
	void display(sf::RenderWindow *Window) {
		if (_display) {
			_Sprite.setTexture(_Texture);
			Window->draw(_Sprite);
		}
	};
	void setPos(sf::Vector2f pos) { _Sprite.setPosition(pos); };
	sf::Vector2f getPos() { return _Sprite.getPosition(); };
	void setDisplay(bool disp) { _display = disp; };
	sf::FloatRect getRect() { return _Sprite.getGlobalBounds(); };
private:
	sf::Sprite _Sprite;
	sf::Texture _Texture;
	bool _display;
};

//#endif