#pragma once

#include <unordered_map>
#include <memory>

#include "window.hpp"
#include "Sprite.hpp"
#include "ofile.hpp"

enum EVENT {
    QUIT = -1,
    NONE,
};

typedef struct obj_s {
    int idSprite;
    sf::Vector2f pos; 
} obj_t;


class Game {
public:
    Game() {
        _window = std::make_unique<Window>();
        _status = 1;
        _totalId = 0;
    };
    ~Game() = default;
public:
    EVENT event(void);
    void draw(void);
    void run(void);
    void insert_o(int, int);
    void add_texture(std::string const &);
    void add_obj(obj_t);
    void add_sprite(int, Sprite &);
    void add_layer(File &, int, int);
public:
    std::unordered_map<int, Sprite> &get_Cs(void) { return this->s_container;};
private:
    std::unordered_map<int, Sprite> s_container;
    std::unordered_map<int, Texture> t_container;
    std::vector<obj_t> o_container;

    sf::Event _event{};
    std::unique_ptr<Window> _window;
    int _status;
    int _totalId;
};