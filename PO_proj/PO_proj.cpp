#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "player.h"
#include "animation.h"

int main()
{
    //window rendering: measurements, title, resolution, etc.
    sf::RenderWindow window(sf::VideoMode(1820, 1024), "Redemption", sf::Style::Close | sf::Style::Fullscreen);
    //setting the centre of view
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f));
    
    //giving the texture to the specific objects
    sf::Texture playerTexture;
    playerTexture.loadFromFile("p.png");


    //creating player
    Player player(&playerTexture, sf::Vector2u(1, 1), 0.0, 100.0);
    
    
    float deltaTime = 0.0f;
    sf::Clock clock;

    while(window.isOpen()) {
        //deltaTime will make the game logic independent of FPS
        deltaTime = clock.restart().asSeconds();
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        player.Draw(window);
        player.update(deltaTime);
        window.display();
        window.clear();
    }

}
