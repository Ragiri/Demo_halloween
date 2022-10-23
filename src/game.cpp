#include "../includes/game.hpp"
#include <unistd.h>

static obj_t create_obj(int id, sf::Vector2f cord) {
    return (obj_t){.idSprite=id, .pos=cord};
}

void Game::draw(void) {
    _window.get()->getWindow()->clear(sf::Color::Black);
	_window.get()->getWindow()->setView(_window.get()->getWindow()->getDefaultView());
	if (_scene == MENU)
		_menu.displayMenu(_window.get()->getWindow());
	if (_scene == MAP) {
		_window.get()->getWindow()->setView(_view);
    	for (auto &obj : o_container) {
    	    s_container.at(obj.idSprite).setPosition(obj.pos);
    	    _window.get()->getWindow()->draw(s_container.at(obj.idSprite).getSprite());
    	}
		_players.at(1)->displayPlayer(_window.get()->getWindow());
	}
	if (_scene == FIGHT) {
		_fight.displayFight(_window.get()->getWindow());	
	}
    _window.get()->display();
}

void Game::add_texture(std::string const &path) {
    t_container[_totalId] = Texture{path};
    _totalId++;
}

bool Game::checkCollider(sf::Vector2f vect) {
	sf::FloatRect fr = {vect.x, vect.y, 16, 16};
	bool ret = false;

	for (auto &obj : o_container) {
    	bool tmp = fr.contains(obj.pos);
		if (tmp) {
			if (std::find(std::begin(id_collide), std::end(id_collide), obj.idSprite) != std::end(id_collide)) {
				ret = true;
			} else return ret = false;
		}
	}
	return ret;
}

void Game::createFight() {
	int sp = rand() % 4;
	int ss = rand() % 4;
	int lvl = rand() % _players.at(0)->getLvl();
	int tp = rand() % 3;
	int ts = rand() % 3;
	std::vector<std::pair<std::string, std::string>> slime {
		{"Pink Donut", "assets/neko_donut_rose.png"},
		{"Green Donut", "assets/neko_donut_vert.png"},
		{"Purple Slime", "assets/slimePurple.png"},
		{"Yellow Slime", "assets/slimeYellow.png"},
		{"Blue Slime", "assets/slimeBlue.png"},
		{"Green Slime", "assets/slimeGreen.png"},
	};
	static std::vector<Ennemy*> ennemy = {
		new Ennemy(lvl, slime.at(sp).first, ENTITY_TYPE(tp), slime.at(sp).second, {30, 30}),
		new Ennemy(lvl + 1, slime.at(ss).first, ENTITY_TYPE(ts), slime.at(ss).second, {30, 30}),
	};
	_fight.setEnnemys(ennemy);
	_scene = FIGHT;
}

void Game::gameCollider() {
	sf::FloatRect fr = {_players.at(1)->getPosition().x, _players.at(1)->getPosition().y, 16, 16};
	int i = rand() % 155;

	for (auto &obj : o_container) {
    	bool tmp =  fr.contains(obj.pos);
		if (tmp) {
			if (std::find(std::begin(id_collide_fight), std::end(id_collide_fight), obj.idSprite) != std::end(id_collide_fight)) {
				std::cout << "collide, i: " << i << std::endl;
				if (i % 2 != 0 && i % 3 != 0 && i % 5 != 0 && i % 7 != 0 ) {
					this->createFight();
				}
			}
		}
	}
}

void Game::move(int top, float x, float y) {
	_players.at(1)->setPosition({_players.at(1)->getPosition().x + x, _players.at(1)->getPosition().y + y});
	_players.at(1)->getSprite()->getTextureRect().left < 32 ? 
	_players.at(1)->getSprite()->setTextureRect({_players.at(1)->getSprite()->getTextureRect().left + 16, top, 16, 16})
	: _players.at(1)->getSprite()->setTextureRect({0, top, 16, 16});
	_view.setCenter(_players.at(1)->getPosition());
	gameCollider();	
}

void Game::moveEvent(sf::Event event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && checkCollider({_players.at(1)->getPosition().x - (float)0.5, _players.at(1)->getPosition().y}))
		move(16, -0.5, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && checkCollider({_players.at(1)->getPosition().x + (float)0.5, _players.at(1)->getPosition().y}))
		move(32, 0.5, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && checkCollider({_players.at(1)->getPosition().x, _players.at(1)->getPosition().y - (float)0.5}))
		move(48, 0, -0.5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && checkCollider({_players.at(1)->getPosition().x, _players.at(1)->getPosition().y + (float)0.5}))
		move(0, 0, 0.5);
};

void Game::add_layer(File &tmp, int width, int height) {
    sf::Vector2f pos = {0, 0};
    int count = 0;
    int line = 0;
    int tile = 0;

    for(auto &y: tmp.getData()) {
        pos.y = height * line;
        for(auto &x: y) {
            pos.x = width * tile;
            //std::cout << "pos.x " << pos.x << " pos.y " << pos.y << std::endl;
            add_obj(create_obj(x, pos));
            if (s_container.find(x) == s_container.end()) {
                s_container[x] = Sprite{};
                if ( x != -1) {
                    s_container[x].setTexture(t_container[0].getTexture());
                    s_container[x].setRect({(x % 57) * 16 + (x % 57), (x / 57) * 16 + (x / 57) , 16, 16});
                }
            }
            count++;
            tile++;
        }
        tile = 0;
        line++;
    }
}

void Game::insert_o(int width, int height) {
    File layer1("Map/Layers/map_Doors_windows_roof.csv");
    File layer2("Map/Layers/map_Ground overlay.csv");
    File layer3("Map/Layers/map_Ground_terrain.csv");
    File layer4("Map/Layers/map_Objects.csv");
    File layer5("Map/Layers/map_Roof object.csv");

    add_layer(layer3, width, height);
    add_layer(layer2, width, height);
    add_layer(layer4, width, height);
    add_layer(layer1, width, height);
    add_layer(layer5, width, height);
}

void Game::run(void) {
    while(_status != 0 || _scene != EXIT) {
        if (event() == EVENT::QUIT)
            _status = 0;
        draw();
    }
}

void Game::add_obj(obj_t obj) {
    o_container.push_back(obj);
}

void Game::add_sprite(int id, Sprite &sprite) {
    s_container.insert({id, sprite});
}

EVENT Game::event(void) {
    while(_window.get()->getWindow()->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            return EVENT::QUIT;
        if (_event.type == sf::Event::KeyPressed)
            if (_event.key.code == sf::Keyboard::Escape && _scene == MENU)
                return EVENT::QUIT;
		if (_scene == EXIT)
			return EVENT::QUIT;
		if (_scene == MENU)
			_scene = _menu.menuEvents(_event, &_sound);

		if (_scene == FIGHT) {
			FIGHT_STATUS f = _fight.fight(_event,  _window.get()->getWindow(), &_sound);
			if (f == WIN) {
				_fight.reward();
				_scene = MAP;
			} if (f == LOST) {
				_scene = MAP;
				return EVENT::QUIT;
			}
		}
    }
	if (_scene == MAP)
		this->moveEvent(_event);
    return EVENT::NONE;
}