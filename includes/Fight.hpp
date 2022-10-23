
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.hpp"
#include "Ennemy.hpp"

enum FIGHT_STATUS {
	WIN,
	LOST,
	BATTLE,
};

class Fight {
	public:
		Fight(std::vector<Player*> player, std::vector<Ennemy*> ennemy): _bg("assets/battle_bg.png", {0, 0}, {2000, 800}) {
			_player = player;
			_turn = 1;
			_id_player_turn = 0;
			srand(time(NULL));
			_ennemy = ennemy;
			_selected_action = 0;
			_selected_entity = 0;
			_arrow.createText(">", {5, 555}, 50, sf::Color::Cyan);
			for(auto &e: _ennemy)
				e->resetBoost();
			for(auto &p: _player)
				p->resetBoost();
		};
		~Fight() = default;
		FIGHT_STATUS statusBattle() {
			FIGHT_STATUS status = LOST;
			for(auto &p: _player)
				if (p->getPV() > 0)
					status = WIN;
			for(auto &e: _ennemy)
				if (e->getPV() > 0)
					status = BATTLE;
			std::cout << status << std::endl;
			return status;
		}
		void ennemyTurn() {
			for (auto &e: _ennemy) {
				if (e->getPV() > 0) {
					int i = rand() % 50;
					int p = rand() % 50;
					int id = i % 2 == 0 ? 0 : 1;
					int pid = p % 2 == 0 ? 0 : 1;
					ACTION_TYPE t = e->checkACtionType(id);
					t == ONENNEMYS ?  e->Attack(id, _player.at(pid))
					:  e->Attack(id, _ennemy.at(pid));
				}
			}
		};
		void setEnnemys(std::vector<Ennemy*> ennemy) {
			_ennemy = ennemy;
		};
		void reward() {
			for(auto &p: _player) {
				p->addExp((10 * _ennemy.at(0)->getLvl()));
				p->resetBoost();
			} for(auto &e: _ennemy)
				e->resetBoost();
		};
		FIGHT_STATUS fight(sf::Event event, sf::RenderWindow *window, sf::Sound *sound) {
			if (_player.at(_id_player_turn)->getPV() < 0);
				_id_player_turn == _player.size() - 1 ? 0 : _id_player_turn + 1;
			if (event.type == sf::Event::KeyPressed) {
			    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
					sound->play();
					if (_turn == 1) {
			        	_selected_action = _selected_action == 0 ? 1 : 0;
						_selected_action == 0 ? 
						_arrow.setPosition({10 , 555})
						: _arrow.setPosition({210, 555});
					} if (_turn == 2) {
						_selected_entity = _selected_entity == 0 ? 1 : 0;
						if (_type == ONENNEMYS){
							_selected_entity == 0 ? _arrow.setPosition({580, 130}) :
							_arrow.setPosition({1080, 130}); 
						} else {
							_selected_entity == 0 ? _arrow.setPosition({10, 730}) :
							_arrow.setPosition({310, 730}); 
						}
					}
			    }
			    if (event.key.code == sf::Keyboard::Enter) {
					sound->play();
					_turn++;
					if (_turn == 2) {
						_type = _player.at(_id_player_turn)->checkACtionType(_selected_action);
						_type == ONENNEMYS ?  _arrow.setPosition({580, 130}) : _arrow.setPosition({10, 730});
					}
					if (_turn >= 3) {
						_type == ONENNEMYS ?
						_player.at(_id_player_turn)->Attack(_selected_action, _ennemy.at(_selected_entity))
						: _player.at(_id_player_turn)->Attack(_selected_action, _player.at(_selected_entity));
						this->ennemyTurn();
						for(auto &p: _player)
							p->takeDamageStatus();
						for(auto &e: _ennemy)
							e->takeDamageStatus();
						_turn = 1;
						_arrow.setPosition({10 , 555});
						_id_player_turn = _id_player_turn == _player.size() - 1 ? 0 : _id_player_turn + 1;
						_selected_action = 0;
						_selected_entity = 0;
						_arrow.setPosition({10 , 555});
					}
				}
			}
			return this->statusBattle();
		};
		void displayFight(sf::RenderWindow *Window) {
			_bg.display(Window);
			sf::RectangleShape box(sf::Vector2f(2000, 500));
			box.setPosition({0, 650});
			box.setFillColor(sf::Color::Black);
			box.setOutlineColor(sf::Color::White);
			box.setOutlineThickness(5);
			Window->draw(box);
			for (int i = 0; i != _player.size(); ++i) {
				_player.at(i)->displayPlayerBox(Window, {(float)(20 + ( 300 * i )), (float)750});
			}
			_player.at(_id_player_turn)->displayActionBox(Window);
			for(int i = 0; i != _ennemy.size(); ++i) {
				_ennemy.at(i)->setPosition({(float)(600 + (500 * i)), (float)300});
				_ennemy.at(i)->setScale({8.f, 6.f});
				_ennemy.at(i)->displayEnnemy(Window);
			}
			_arrow.displayText(Window);
		};
	private:
		std::vector<Player*> _player;
		std::vector<Ennemy*> _ennemy;
		ACTION_TYPE _type;
		int _turn;
		int _selected_action;
		int _selected_entity;
		Text _arrow;
		int _id_player_turn;
		Object _bg;

};