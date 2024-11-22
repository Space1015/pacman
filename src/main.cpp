#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
using namespace std;
int main()
{
    auto window = sf::RenderWindow({896u, 1152u}, "Pacman");
    window.setFramerateLimit(144);
    GameMap gameMap;
    Pacman pacman;
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        gameMap.displayMap(window, pacman);
        window.display();
    }
}
