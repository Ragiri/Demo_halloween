#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <map>
#include <vector>
#include <filesystem>
#include <utility>
#include <string.h>
#include "Ennemy.hpp"
#include "Object.hpp"

class Game {
    public:
    Game(std::string layerDir) {
	for (auto &layer: std::filesystem::recursive_directory_iterator(layerDir)) {
		std::ifstream ifs(layer);
		if (ifs.is_open()) {
			std::string line;
    		while (std::getline(file, line)) {
				char *line_point = strtok(line.c_str(), )
			}
    			file.close();
			}
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
