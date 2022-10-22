#include "../includes/game.hpp"

int main() {
    Game game;

    game.add_texture("assets/likerogue.png");
    game.insert_o(16, 16);
    game.run();
    return 0;
}