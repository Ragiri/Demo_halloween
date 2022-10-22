#include "gane.hpp"

static obj_t create_obj(int id, sf::Vector2f cord) {
    return (obj_t){.idSprite=id, .pos=cord};
}

void Game::draw(void) {
    for (auto &obj : o_container) {
        s_container.at(obj.idSprite).setPosition(obj.pos);
        _window.get()->getWindow()->draw(s_container.at(obj.idSprite).getSprite());
    }
    _window.get()->display();
}

void Game::add_texture(std::string const &path) {
    t_container[_totalId] = Texture{path};
    _totalId++;
}

#include <unistd.h>

void Game::add_layer(File &tmp, int width, int height) {
    sf::Vector2f pos = {0, 0};
    int count = 0;
    int line = 0;
    int tile = 0;

    for(auto &y: tmp.getData()) {
        pos.y = height * line;
        for(auto &x: y) {
            pos.x = width * tile;
            std::cout << "pos.x " << pos.x << " pos.y " << pos.y << std::endl;
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
    File layer1("grrrr_Tile Layer 1.csv");
    File layer2("grrrr_path.csv");
    File layer3("grrrr_object.csv");

    add_layer(layer1, width, height);
    add_layer(layer2, width, height);
    add_layer(layer3, width, height);
}

void Game::run(void) {
    while(_status != 0) {
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
            if (_event.key.code == sf::Keyboard::Escape)
                return EVENT::QUIT;
    }
    return EVENT::NONE;
}