#include "GameState.h"
#include "StateMachine.h"

GameState::GameState(StateMachine& machine) : State(machine), gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f)), interfaceView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(400.0f, 400.0f)) {
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
    maxHp = hp = 1337;

    int z = 8;
    int hpp = 10;
    float x = hpp*z;
    avatar = sf::RectangleShape(sf::Vector2f(80.f, 95.f));
    frameBar = sf::RectangleShape(sf::Vector2f(110.f, 16.f));
    healthBar = sf::RectangleShape(sf::Vector2f(x, 10.f));
 
    // Load interface textures
    avatarTexture = std::make_shared<sf::Texture>();
    if (!avatarTexture->loadFromFile("assets/avatar.png")) {
        throw("Couldn't load the avatar texture");
    }
    avatar.setTexture(avatarTexture.get());
    avatar.setPosition(0.0f, 50.0f);

    frameBarTexture = std::make_shared<sf::Texture>();
    if (!frameBarTexture->loadFromFile("assets/frame_Healthbar.png")) {
        throw("Couldn't load the healthbar frame texture");
    }
    frameBar.setTexture(frameBarTexture.get());
    healthBar.setPosition(0.0f, 100.0f);

    healthBarTexture = std::make_shared<sf::Texture>();
    if (!healthBarTexture->loadFromFile("assets/Healthbar.png")) {
        throw("Couldn't load the healthbar texture");
    }
    healthBar.setTexture(healthBarTexture.get());
    frameBar.setPosition(0.0f, 100.0f);
    
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
    // Draw world
    target.setView(gameView);
    target.draw(meme);
    target.draw(*player);

    // Draw UI
    target.setView(interfaceView);
    target.draw(avatar);
    target.draw(healthBar);
    target.draw(frameBar);
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

    gameView.setCenter(player->GetPosition());
}