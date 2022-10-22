#ifndef ACTION_HPP
#define ACTION_HPP

#include "Entity.hpp"
#include <cstdlib>
#include <ctime>

class Action {
	public:
	Action() {
		srand(time(NULL));
	};
	~Action() = default;
	static int heal(Entity *p, Entity *e) {
		int i = rand() % 155;
		std::cout << i << std::endl;
		if (e->getPV() > 0 && e->getPV() != e->getInitialPV()) {
			e->setPV(e->getPV() + (3 * p->getLvl()));
			return 0;
		};
		if ((e->getPV() + (3 * p->getLvl())) > e->getInitialPV()) {
			e->setPV(e->getInitialPV());
		}
		return -1;
	};
	static int light(Entity *p, Entity *e) {
		int i = rand() % 155;
		std::cout << i << std::endl;
		if (i % 2 == 0 || i % 3 == 0  || i % 5 == 0) {
			e->takeDamage((p->getATK() * p->getLvl()) + (p->getBoostATK() * p->getLvl()) - 2);
			return 0;
		};
		return -1;
	};
	static int fireBall(Entity *p, Entity *e) {
		int i = rand() % 155;
		std::cout << i << std::endl;
		if (i % 2 == 0 || i % 3 == 0  || i % 5 == 0) {
			e->takeDamage((p->getATK() * p->getLvl()) + (p->getBoostATK() * p->getLvl()) + 2);
			if ((i / 2) % 5 == 0 && e->getStatus() == NONE)
				e->setStatus(BURN);
			return 0;
		};
		return -1;
	};
	static int poison(Entity *p, Entity *e) {
		int i = rand() % 155;
		std::cout << i << std::endl;
		if (i % 2 == 0 || i % 3 == 0  || i % 5 == 0) {
			e->setStatus(POISON);
			return 0;
		};
		return -1;
	};
	static int boostAtk(Entity *p, Entity *e) {
		e->setATK(e->getATK() + (1 * e->getLvl()));
		return 0;
	};
	static int boostDef(Entity *p, Entity *e) { 
		if (e->getDEF() < e->getPV())
			e->setDEF(e->getDEF() + (2 * e->getLvl()));
		else e->setDEF(e->getPV());
		return 0;
	};
	static int slash(Entity *p, Entity *e) {
		int i = rand() % 155;
		std::cout << i << std::endl;
		if (i % 2 == 0 || i % 3 == 0  || i % 5 == 0) {
			e->takeDamage((p->getATK() * p->getLvl()) + (p->getBoostATK() * p->getLvl()));
			return 0;
		};
		return -1;
	};
};

#endif