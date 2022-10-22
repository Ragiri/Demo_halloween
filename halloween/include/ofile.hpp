#pragma once

#include <fstream>
#include <vector>
#include <iostream>

class File {
public:
    File(std::string path) {
        open(path);
    }
    ~File() = default;
public:
    void open(std::string path) {
        std::vector<int> value;
        std::string tmp;

        _ifs.open(path, std::ifstream::in);
        tmp = _ifs.get();
        for (;_ifs.good(); tmp.push_back(_ifs.get())) {
            if (tmp.back() == ',') {
                value.push_back(std::stoi(tmp));
                tmp.clear();
            } else if (tmp.back() == '\n') {
                _data.push_back(value);
                value.clear();
            }
        }
    };
    void print(void) {
        for (auto &i : _data) {
            for (auto &y : i) {
                std::cout << y << " ";
            }
            std::cout << std::endl;
        }
    }
public:
    std::vector<std::vector<int>> &getData(void) {return this->_data;};
private:
    std::ifstream _ifs;
    std::vector<std::vector<int>> _data;
};