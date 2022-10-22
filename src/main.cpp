#include <SFML/Graphics.hpp>
#include "../includes/Fight.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(), "My window", sf::Style::Fullscreen);
	std::vector<Player*> p = {
		new Player(35, 5, 3, "Witch", MAGE, "assets/witch.png"),
		new Player(35, 3, 3, "EGirl", HEALER, "assets/witch.png"),
	};
	std::vector<Ennemy*> e = {
		new Ennemy(35, 3, 5, "Blue", TANK, "assets/slimeBlue.png", {30, 30}),
		new Ennemy(35, 5, 3, "Green", SWORDMAN, "assets/slimeGreen.png", {30, 30}),
	};
	Fight f(p, e);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
			f.fight(event, &window);
        }
        window.clear(sf::Color::Black);
		f.displayFight(&window);
        window.display();
    }

    return 0;
}