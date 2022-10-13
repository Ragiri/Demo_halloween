#define ENNEMY_HPP
#ifndef ENNEMY_HPP

#define EXPTOLVLUP 50 
#include "Entity.hpp"

class Player: public Entity {
public:
Player(int pv, int atk, int def): Entity(pv, atk, def) {
	_exp = 0;
	_lvl = 1;
};
~Healer() = default;
int addExp(int64_t exp) {
	if ((_exp += exp) >= _lvl * EXPTOLVLUP) {
		_exp -= _lvl * EXPTOLVLUP;
		_lvl +=1;
		return 1;
	} else
		return -1;
};
void Attack() {};
void setPosition(std::pair<int, int> pos) {
	_pos = pos;
};
std::pair<int, int> getPosition() { return _pos; };
private:
	int64_t _exp;
	int _lvl;
	std::pair<int, int> _pos;
};

#endif
