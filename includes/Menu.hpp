#ifndef MENU_HPP
#define MENU_HPP

#include "Text.hpp"
#include "Object.hpp"

enum SCENE {
	MENU,
	MAP,
	FIGHT,
	EXIT,
};

class Menu {
public:
	Menu(std::string filename): _bg("assets/battle_bg.png", {0, 0}, {2000, 800}) {
		_arrow.createText(">", {850, 350}, 50, sf::Color::Cyan);
		_selected_scene = 0;
	};
	~Menu() = default;
	void displayShapes(sf::RenderWindow *window) {
		sf::RectangleShape start_rect(sf::Vector2f(500, 250));
		sf::RectangleShape quit_rect(sf::Vector2f(500, 250));
		Text start, quit;

		start_rect.setPosition({800, 250});
		start_rect.setFillColor(sf::Color::White);
		start_rect.setOutlineThickness(5);
		start_rect.setOutlineColor(sf::Color::Black);
		quit_rect.setPosition({800, 650});
		quit_rect.setFillColor(sf::Color::White);
		quit_rect.setOutlineThickness(5);
		quit_rect.setOutlineColor(sf::Color::Black);


		start.createText("START", {start_rect.getPosition().x + 200, start_rect.getPosition().y + 100}, 50, sf::Color::Black);
		quit.createText("QUIT", {quit_rect.getPosition().x + 200, quit_rect.getPosition().y + 100}, 50, sf::Color::Black);
		_arrow.displayText(window);
		window->draw(start_rect);
		window->draw(quit_rect);
		start.displayText(window);
		quit.displayText(window);
	};
	void displayMenu(sf::RenderWindow *window) {
		_bg.display(window);
		this->displayShapes(window);
		_arrow.displayText(window);
	};
	SCENE menuEvents(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
		    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
			    _selected_scene = _selected_scene == 0 ? 1 : 0;
				_selected_scene == 0 ? 
				_arrow.setPosition({850, 350})
				: _arrow.setPosition({850, 750});
			}
			if (event.key.code == sf::Keyboard::Enter) {
				if (_selected_scene == 0)
					return MAP;
				else
					return EXIT;
			}
		}
		return MENU;
	};
private:
	Object _bg;
	Text _arrow;
	int _selected_scene;
};


#endif