#define GAME_HPP
#ifndef GAME_HPP

#include <iostream>
#include <map>
#include <vector>
#include <filesystem>
#include <uttility>
#include "Ennemy.hpp"

class Game {
    public:
    Game(std::string layerDir) {
	for (auto &layer: std::filesystem::recursive_directory_iterator(layerDir)) {
		std::ifstream ifs;
  		ifs.open (layer, std::ifstream::in);
  		//char c = ifs.get();
  		//while (ifs.good()) {
    		//	std::cout << c;
    		//	c = ifs.get();
  		//}
  		ifs.close();
	}
    };
    ~Game() = default;
    void createMap() {

    };
    private:
    std::vector<std::vector<std::pair<int, int>>> _map_layers;
    std::map<int, Ennemy> _ennemy;
};

#endif
