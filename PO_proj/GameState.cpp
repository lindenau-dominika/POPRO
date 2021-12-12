#include "GameState.h"
#include "StateMachine.h"

GameState::GameState(StateMachine& machine) : State(machine), view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f)) {
    // Load player texture
    playerTexture = std::make_shared<sf::Texture>();
    if (!playerTexture->loadFromFile("assets/player.png")) {
        throw("Couldn't load the player texture");
    }

    // Set up player
    player = std::make_unique<Player>(playerTexture.get(), sf::Vector2u(8, 6), 0.07f, 200.0f, 200.0f);

    // Set up field
    meme = sf::RectangleShape(sf::Vector2f(200.f, 300.f));
    meme.setPosition(450.0, 450.0);

    //Interface - Healthbar, avatar
    int z = 8;
    int hpp = 10;
    float x = hpp*z;
    avatar = sf::RectangleShape(sf::Vector2f(80.f, 95.f));
    f_bar = sf::RectangleShape(sf::Vector2f(110.f, 16.f));
    bar = sf::RectangleShape(sf::Vector2f(x, 10.f));
  

    
   
    //load interface texture 
    avatarTexture = std::make_shared<sf::Texture>();
    if (!avatarTexture->loadFromFile("assets/avatar.png")) {
        throw("Couldn't load the avatar texture");
    }

    fbarTexture = std::make_shared<sf::Texture>();
    if (!fbarTexture->loadFromFile("assets/frame_Healthbar.png")) {
        throw("Couldn't load the healthbar frame texture");
    }

    barTexture = std::make_shared<sf::Texture>();
    if (!barTexture->loadFromFile("assets/Healthbar.png")) {
        throw("Couldn't load the healthbar texture");
    }
    
    avatar.setTexture(avatarTexture.get());
    f_bar.setTexture(fbarTexture.get());
    bar.setTexture(barTexture.get());
    
    // Load music
    music = std::make_unique<sf::Music>();
    if (!music->openFromFile("assets/soundtrack.wav")) {
        throw("Couldn't load the soundtrack");
    }
    music->setVolume(20.f);
    music->setLoop(true);
    music->play();
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.setView(view);
    target.draw(meme);
    target.draw(*player);
    target.draw(avatar);
    target.draw(bar);
    target.draw(f_bar);
}

void GameState::update(sf::RenderWindow& window, float deltaTime) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == event.KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) {
                parent_machine.pop_state();
                return;
            }
        }
    }

    player->update(deltaTime);
    avatar.setPosition(player->GetPosition().x - 340.f, player->GetPosition().y +90.f);
    bar.setPosition(player->GetPosition().x -257.f, player->GetPosition().y + 160.f);
    f_bar.setPosition(player->GetPosition().x -262.f, player->GetPosition().y + 156.5f);

    view.setCenter(player->GetPosition());
}
