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
    playerTexture.loadFromFile("assets/player.png");

    Player player(&playerTexture, sf::Vector2u(8, 6), 0.07f, 200.0f, 200.0f);
    sf::RectangleShape meme(sf::Vector2f(200.f, 300.f));
    meme.setPosition(450.0, 450.0);
    
    //Text, font, menu etc
    sf::Text mainmenu;
    sf::Text option0;
    sf::Text option1;
    sf::Text option2;
    sf::Font font;


    // Music
    sf::Music music;
    if (!music.openFromFile("assets/soundtrack.wav"))
        return -1;
    music.setVolume(60.f);
    music.setLoop(true);

    if (!font.loadFromFile("assets/arial.ttf"))
        throw("couldnt load the font");

    //gaem naem 
    mainmenu.setFont(font);
    mainmenu.setString("Yggdrasil");
    mainmenu.setCharacterSize(120);
    mainmenu.setFillColor(sf::Color::Cyan);
    mainmenu.setPosition(sf::Vector2f(220.0f, 50.0f));

    // option0
    option0.setFont(font);
    option0.setString("Uno gaem my friend?");
    option0.setCharacterSize(90);
    option0.setFillColor(sf::Color::Cyan);
    option0.setPosition(sf::Vector2f(300.0f, 250.0f));

    // option1
    option1.setFont(font);
    option1.setString("Settingos, but u dont need this");
    option1.setCharacterSize(90);
    option1.setFillColor(sf::Color::Cyan);
    option1.setPosition(sf::Vector2f(400.0f, 450.0f));
                 
    //option2
    option2.setFont(font);
    option2.setString("Exito see you laterito");
    option2.setCharacterSize(90);
    option2.setFillColor(sf::Color::Cyan);
    option2.setPosition(sf::Vector2f(600.0f, 650.0f));
   

    //menu declarations
    int option = 0;
    bool in_menu = true;
    bool good = true;

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        //deltaTime will make the game logic independent of FPS
        deltaTime = clock.restart().asSeconds();
        sf::Event event;

        //Main Menu
        if (in_menu) {
            if (option == 1)
            {
                option0.setFillColor(sf::Color::White);
                option0.setCharacterSize(100);
                option1.setFillColor(sf::Color::Cyan);
                option1.setCharacterSize(90);
                option2.setFillColor(sf::Color::Cyan);
                option2.setCharacterSize(90);
            }
            else if (option == 2)
            {
                option0.setFillColor(sf::Color::Cyan);
                option0.setCharacterSize(90);
                option1.setFillColor(sf::Color::White);
                option1.setCharacterSize(100);
                option2.setFillColor(sf::Color::Cyan);
                option2.setCharacterSize(90);
            }
            else if (option == 3)
            {
                option0.setFillColor(sf::Color::Cyan);
                option0.setCharacterSize(90);
                option1.setFillColor(sf::Color::Cyan);
                option1.setCharacterSize(90);
                option2.setFillColor(sf::Color::White);
                option2.setCharacterSize(100);
            }

            window.draw(mainmenu);
            window.draw(option0);
            window.draw(option1);
            window.draw(option2);
        }
        else
        {
            if (option == 1)
            {        
                window.clear();
                window.draw(meme);
                window.setView(view);
                player.Draw(window);
                player.update(deltaTime);

                view.setCenter(player.GetPosition());
            }
            else if (option == 2) {
                sf::Text inst;
                inst.setFont(font);
                inst.setString("U dont need this but ok. its W S A D. glhf");
                inst.setCharacterSize(60);
                inst.setFillColor(sf::Color::White);
                inst.setPosition(sf::Vector2f(200.0, 400.0));
                window.draw(inst);

            }
            else if (option == 3) {
                window.close();
            }
        }


        // Poll events
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == event.KeyPressed)
            {
                if (good)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        if (option < 3) { option += 1; }
                        else { option = 1; }
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        if (option > 1) { option -= 1; }
                        else { option = 3; };
                    }
                    if (event.key.code == sf::Keyboard::Enter or event.key.code == sf::Keyboard::Space) {
                        in_menu = false;
                        if(option == 1) {
                            music.play();
                        }
                    }
                    good = false;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    if (in_menu) {
                        option = 3;
                        in_menu = false;
                    }
                    else if (!in_menu) {
                        option = 1;
                        in_menu = true;
                    }
        

                }
            }
            else if (event.type == event.KeyReleased) {
                good = true;
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        window.display();
        window.clear();
    }
}
