#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <map>

enum ACTION_TYPE {
	ONPLAYERS,
	ONENNEMYS,
};

enum ENTITY_TYPE {
	HEALER,
	SWORDMAN,
	MAGE,
	TANK,
};

enum ENTITY_STATUS {
	PARALYSE,
	BURN,
	POISON,
	NAN,
};

class Entity {
public:
Entity(int pv, int atk, int def, ENTITY_TYPE type, std::string name): _pv(pv), _atk(atk), _def(def), _type(type), _name(name) {
	_status = NAN;
	_lvl = 1;
	_boostAtk = 0;
	_boostDef = 0;
	_initialPV = pv;
	std::vector<std::string> sl{"PARALISE", "BURN", "POISON", "NONE"};
	_status_letter = sl;
};
~Entity() = default;
int getPV() { return _pv; };
int getInitialPV() { return _initialPV; };
int getATK() { return _atk; };
int getDEF() { return _def; };
ENTITY_STATUS getStatus() { return _status; };
int getBoostATK() { return _boostAtk; };
int getBoostDEF() { return _boostDef; };
void setPV(int pv) { _pv = pv; };
void takeDamage(int damage) {
	std::cout << damage << std::endl;
	if (_boostDef + _def < damage)
		_pv -= (damage - (_boostDef + _def));
	else _pv -= 1;
};
void takeDamageStatus() {
	if (_status != NAN)
		_pv -= 3 * _lvl;
};
void setStatus(ENTITY_STATUS stat) {_status = stat;};
void setATK(int atk) { _atk = atk; };
void setDEF(int def) { _def = def; };
void setBoostATK(int atk) { _boostAtk += atk; };
void setBoostDEF(int def) { _boostDef += def; };
void resetBoost() {
	_boostAtk = 0;
	_boostDef = 0;
};
int getLvl() { return _lvl; };
bool isAlive() { return _pv > 0; };
std::string getName() { return _name; };

protected:
int _pv;
int _initialPV;
int _atk;
int _boostAtk;
int _boostDef;
int _def;
int _lvl;
std::string _name;
ENTITY_STATUS _status;
ENTITY_TYPE _type;
std::vector<std::string> _status_letter;
};

#endif
