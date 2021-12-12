#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "player.h"
#include "animation.h"
#include "menu.h"

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
    
    // Load default font
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw("couldn't load the font");
    }


    // Music
    sf::Music music;
    if (!music.openFromFile("assets/soundtrack.wav")) {
        return -1;
    }
    music.setVolume(60.f);
    music.setLoop(true);


    // Setup menu
    Menu menu("Yggdrasil", font);
    menu.add_option("Uno gaem my friend?", sf::Vector2f(300.0f, 250.0f));
    menu.add_option("Settingos, but u dont need this", sf::Vector2f(400.0f, 450.0f));
    menu.add_option("Exito see you laterito", sf::Vector2f(600.0f, 650.0f));
    bool in_menu = true;
    bool pressing_button = false;

    
    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        //deltaTime will make the game logic independent of FPS
        deltaTime = clock.restart().asSeconds();
        sf::Event event;

        //Main Menu
        if (in_menu) {
            window.draw(menu);
        }
        else
        {
            // Draw game
            window.clear();
            window.draw(meme);
            window.setView(view);
            player.Draw(window);
            player.update(deltaTime);

            view.setCenter(player.GetPosition());
        }


        // Poll events
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == event.KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (in_menu) {
                    if (event.key.code == sf::Keyboard::Down && !pressing_button)
                    {
                        menu.move_down();
                    }
                    if (event.key.code == sf::Keyboard::Up && !pressing_button) {
                        menu.move_up();
                    }
                    if (event.key.code == sf::Keyboard::Enter or event.key.code == sf::Keyboard::Space) {
                        int selected_option = menu.get_selected_option();
                        if (selected_option == 0) {
                            in_menu = false;

                            // Play the music when entering the game
                            music.play();
                        }
                        else if (selected_option == 1) {
                            // TODO: Remake this for the new system
                            /* 
                            sf::Text inst;
                            inst.setFont(font);
                            inst.setString("U dont need this but ok. its W S A D. glhf");
                            inst.setCharacterSize(60);
                            inst.setFillColor(sf::Color::White);
                            inst.setPosition(sf::Vector2f(200.0, 400.0));
                            window.draw(inst);
                            */
                        }
                        else if (selected_option == 2) {
                            window.close();
                        }

                    }
                        
                    pressing_button = true;
                    
                }
            }
            else if (event.type == event.KeyReleased) {
                pressing_button = false;
            }
        }
        

        window.display();
        window.clear();
    }
}
