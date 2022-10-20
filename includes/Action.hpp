#include "Player"
#include <stdlib.h>

class Action {
	Action() {
		srand(time(NULL));
	};
	~Action() = default;
	int heal() {};
	int light() {};
	int fireBall() {};
	int poison() {};
	int boostATK() {};
	int boostDEF() {};
	int slash() {};
	int shield(Entity *entity) {
		int i = srand (time(NULL));

	};
};