#include "gane.hpp"

int main(void) {
    Game game;

    game.add_texture("likerogue.png");
    game.insert_o(16, 16);
    //Texture text("Space Background.png");
    //Sprite cc;

    //cc.setTexture(text.getTexture());

    //game.add_sprite(0, cc);
    //game.add_obj(create_obj(0, {0,0}));
    game.run();
    //file.print();
    return 0;
}