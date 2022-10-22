#ifndef _GAME_HPP_
#define _GAME_HPP_

#pragma once

#include <unordered_map>
#include <memory>

#include "window.hpp"
#include "Sprite.hpp"
#include "ofile.hpp"
#include "Menu.hpp"
#include "Fight.hpp"

enum EVENT {
    QUIT = -1,
    NONE,
};

static std::vector<int> id_collide = {
	-1, 862, 863, 864, 865, 866, 919, 920, 976, 977, 978, 
	921, 632, 408, 405, 416, 807, 1031, 404, 689, 1254, 406,
	462, 465, 1356, 465, 577, 578, 579, 520, 521, 522,
	519, 634, 635, 636, 518, 575, 576, 636, 807, 1032, 404,
	526, 458,459, 460, 1257
};

typedef struct obj_s {
    int idSprite;
    sf::Vector2f pos; 
} obj_t;


static std::vector<Ennemy*> init_fight_ennemy = {
	new Ennemy(35, 3, 5, "Blue", TANK, "assets/slimeBlue.png", {30, 30}),
	new Ennemy(35, 5, 3, "Green", SWORDMAN, "assets/slimeGreen.png", {30, 30}),
};


static std::vector<Player*> init_fight_player = {
	new Player(35, 5, 3, "Witch", MAGE, "assets/witch.png"),
	new Player(35, 3, 3, "Healer", HEALER, "assets/witch.png"),
};

class Game {
public:
    Game(): _menu("assets/battle_bg.png"), _fight(init_fight_player, init_fight_ennemy) {
        _window = std::make_unique<Window>();
        _status = 1;
        _totalId = 0;
		_scene = MENU;
		_players = init_fight_player;
    };
    ~Game() = default;
public:
    EVENT event(void);
    void draw(void);
    void setScene(SCENE s) { _scene = s; };
    void run(void);
    void insert_o(int, int);
    void add_texture(std::string const &);
    void add_obj(obj_t);
    void add_sprite(int, Sprite &);
    void add_layer(File &, int, int);
	void createFight();
	void gameCollider();
	bool checkCollider(sf::Vector2f vect);
	void moveEvent(sf::Event event);
public:
    std::unordered_map<int, Sprite> &get_Cs(void) { return this->s_container;};
private:
    std::unordered_map<int, Sprite> s_container;
    std::unordered_map<int, Texture> t_container;
    std::vector<obj_t> o_container;
	Menu _menu;
	Fight _fight;
    sf::Event _event{};
    std::unique_ptr<Window> _window;
	std::vector<Player*> _players;
	SCENE _scene;
    int _status;
    int _totalId;
};

#endif