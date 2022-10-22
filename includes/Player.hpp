#ifndef PLAYER_HPP
#define PLAYER_HPP

#define EXPTOLVLUP 50 
#include "Text.hpp"
#include "Object.hpp"
#include "Action.hpp"

typedef int (*IntFunctionWithTwoParameter) (Entity *p, Entity *e);

std::map<ENTITY_TYPE, std::vector<std::pair<ACTION_TYPE, IntFunctionWithTwoParameter>>> list_action = {
	{HEALER, {std::make_pair(ONPLAYERS , Action::heal), std::make_pair(ONENNEMYS , Action::light)}},
	{MAGE, {std::make_pair(ONENNEMYS , Action::fireBall), std::make_pair(ONENNEMYS , Action::poison)}},
	{SWORDMAN, {std::make_pair(ONPLAYERS , Action::boostAtk), std::make_pair(ONENNEMYS , Action::slash)}},
	{TANK, {std::make_pair(ONPLAYERS , Action::boostDef), std::make_pair(ONPLAYERS , Action::boostDef)}},
};

std::map<ENTITY_TYPE, std::vector<std::string>> list_action_names = {
	{HEALER, {"Heal", "Light"}},
	{MAGE, {"FireBall", "Poison"}},
	{SWORDMAN, {"Boost Attack", "SLASH"}},
	{TANK, {"Defance boost", "Defance boost"}},
};

class Player: public Entity {
public:
Player(int pv, int atk, int def, std::string name, ENTITY_TYPE type, std::string filename): 
	Entity(pv, atk, def, type, name), _obj(filename, std::make_pair(0, 0), std::make_pair(41, 91)) {
	_exp = 0;
	_action = list_action[type];
	_action_name = list_action_names[type];
};
~Player() = default;
int addExp(int64_t exp) {
	if ((_exp += exp) >= _lvl * EXPTOLVLUP) {
		_exp -= _lvl * EXPTOLVLUP;
		_lvl +=1;
		return 1;
	} else
		return -1;
};
void setPosition(std::pair<int, int> pos) {
	_pos = pos;
};
std::pair<int, int> getPosition() { return _pos; };
int Attack(int atkId, Entity *entity) {
	return _action.at(atkId).second(this, entity);
};
ACTION_TYPE checkACtionType(int id) {
	return _action.at(id).first;
};
void displayPlayer(sf::RenderWindow *Window) { _obj.display(Window); };
void displayPlayerBox(sf::RenderWindow *Window, sf::Vector2f pos) {
	sf::RectangleShape rectangle(sf::Vector2f(250, 250));
	Text name, pv, lvl, status;

	rectangle.setPosition(pos);
	rectangle.setFillColor(sf::Color::White);
	name.createText(_name, {rectangle.getPosition().x + 30, rectangle.getPosition().y + 10}, 20, sf::Color::Black);
	status.createText(_status_letter.at(_status), {rectangle.getPosition().x + 30, rectangle.getPosition().y + 10}, 20, sf::Color::Black);
	lvl.createText("Lvl: " + std::to_string(_lvl), {rectangle.getPosition().x + 20, rectangle.getPosition().y + 90}, 20, sf::Color::Black);
	pv.createText("Life: " + std::to_string(_pv), {rectangle.getPosition().x + 20, rectangle.getPosition().y + 150}, 20, sf::Color::Black);

	Window->draw(rectangle);
	name.displayText(Window);
	lvl.displayText(Window);
	pv.displayText(Window);
	status.displayText(Window);
};
void displayActionBox(sf::RenderWindow *Window) {
	for (int i = 0; i != _action_name.size(); i++) {
		sf::RectangleShape rectangle(sf::Vector2f(200, 100));
		rectangle.setPosition({( 200 * i ), 550});
		rectangle.setFillColor(sf::Color::White);
		rectangle.setOutlineThickness(5);
		rectangle.setOutlineColor(sf::Color::Black);
		Window->draw(rectangle);
		Text tmp;
		tmp.createText(_action_name.at(i), {rectangle.getPosition().x + 30, rectangle.getPosition().y + 20}, 20, sf::Color::Black);
		tmp.displayText(Window);
	};
};
private:
	int64_t _exp;
	std::pair<int, int> _pos;
	std::vector<sf::Text> _text;
	Object _obj;
	std::vector<std::pair<ACTION_TYPE, IntFunctionWithTwoParameter>> _action;
	std::vector<std::string> _action_name;
};

#endif
