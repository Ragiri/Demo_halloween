#ifndef Ennemy_HPP
#define Ennemy_HPP

#define EXPTOLVLUP 50 
#include "Text.hpp"
#include "Object.hpp"
#include "Action.hpp"
#include "Player.hpp"

typedef int (*IntFunctionWithTwoParameter) (Entity *p, Entity *e);

class Ennemy: public Entity {
public:
Ennemy(int l, std::string name, ENTITY_TYPE type, std::string filename, std::pair<int, int> size): 
	Entity(35 + (3 * (l - 1)), 3 + (2 * (l - 1)), 3 + (2 * (l - 1)), type, name), _obj(filename, std::make_pair(0, 0), size) {
	_action = list_action[type];
	_action_name = list_action_names[type];
	_lvl = l;
};
~Ennemy() = default;
void setPosition(sf::Vector2f pos) {
	_obj.setPos(pos);
};
std::pair<int, int> getPosition() { return _pos; };
int Attack(int atkId, Entity *entity) {
	return _action.at(atkId).second(this, entity);
};
ACTION_TYPE checkACtionType(int id) {
	return _action.at(id).first;
};
void setScale(sf::Vector2f v) {
	_obj.getSprite()->setScale(v);
};
void displayEnnemy(sf::RenderWindow *Window) { 
	Text info;
	Text status;
	sf::RectangleShape rectangle(sf::Vector2f(200, 100));
	rectangle.setPosition({_obj.getPos().x, _obj.getPos().y - 200});
	rectangle.setFillColor(sf::Color::White);
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(sf::Color::Black);

	info.createText( _name + "\nLvl: " + std::to_string(_lvl) + "\nLife: " + std::to_string(_pv), {rectangle.getPosition().x + 20, rectangle.getPosition().y + 10}, 20, sf::Color::Black);
	status.createText( _status_letter.at(_status), {rectangle.getPosition().x + 120, rectangle.getPosition().y + 40}, 15, sf::Color::Black);
	_obj.display(Window);
	Window->draw(rectangle);
	info.displayText(Window);
	status.displayText(Window);
};
private:
	std::pair<int, int> _pos;
	std::vector<sf::Text> _text;
	Object _obj;
	std::vector<std::pair<ACTION_TYPE, IntFunctionWithTwoParameter>> _action;
	std::vector<std::string> _action_name;
};

#endif
