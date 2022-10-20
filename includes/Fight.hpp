
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

enum FIGHT_STATUS {
	WIN,
	LOST,
	BATTLE,
};

class Fight {
	public:
		Fight(std::vector<Player*> player) {
			_player = player;
		};
		~Fight() = default;
		void displayFight() {

		};
	private:
		std::vector<Player*> _player;
		std::map<sf::FloatRect, int> _attack;

};