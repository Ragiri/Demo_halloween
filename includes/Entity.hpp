#define _ENTITY_HPP
#ifndef _ENTITY_HPP

enum ENTITY_TYPE {
	HEALER,
	SWORDMAN,
	MAGE,
	TANK,
};

class Entity {
public:
Entity(int pv, int atk, int def, ENTITY_TYPE type): _pv(pv), _atk(atk), _def(def), _type(type) {};
~Entity() = default;
int getPV() { return _pv; };
int getATK() { return _atk; };
int getDEF() { return _def; };
void setPV(int pv) { _pv = pv; };
void setATK(int atk) { _atk = atk; };
void setDEF(int def) { _def = def; };
bool isAlive() { return _pv > 0; };
protected:
int _pv;
int _atk;
int _def;
ENTITY_TYPE _type;
};

#endif
