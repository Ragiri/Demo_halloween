#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

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
	void rect_transform(int left, int width) {
		sf::IntRect r = _Sprite.getTextureRect();
		r.left = left;
		r.width = width;
		_Sprite.setTextureRect(r);
	};
	sf::IntRect getTextureRect() { return _Sprite.getTextureRect(); };
	sf::FloatRect getRect() { return _Sprite.getGlobalBounds(); };
	sf::Sprite *getSprite() { return &_Sprite;};
private:
	sf::Sprite _Sprite;
	sf::Texture _Texture;
	bool _display;
};

#endif