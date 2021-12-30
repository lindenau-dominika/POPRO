#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include "player.h"
#include "animation.h"
#include "MenuState.h"
#include "StateMachine.h"
#include "ResourceManager.h"

int main()
{
    //window rendering: measurements, title, resolution, etc.
    sf::RenderWindow window(sf::VideoMode(1820, 1024), "Redemption", sf::Style::Close);
    //setting the centre of view
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f));

    // Create resource manager
    std::shared_ptr<ResourceManager> resourceManager = std::make_shared<ResourceManager>();
    resourceManager->LoadAll();

    // Set up state machine
    StateMachine stateMachine;

    // Set up menu
    MenuState menu(stateMachine, "Yggdrasil", resourceManager);
    menu.add_option("Uno gaem my friend?", sf::Vector2f(300.0f, 250.0f));
    menu.add_option("Settingos, but u dont need this", sf::Vector2f(400.0f, 450.0f));
    menu.add_option("Exito see you laterito", sf::Vector2f(600.0f, 650.0f));
    stateMachine.push_state(std::move(std::make_unique<MenuState>(std::move(menu))));


    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        //deltaTime will make the game logic independent of FPS
        deltaTime = clock.restart().asSeconds();

        stateMachine.update(window, deltaTime);
        window.clear();
        stateMachine.draw(window);
        window.display();
    }
}