#include "GameState.h"
#include "StateMachine.h"

GameState::GameState(StateMachine& machine) : State(machine), gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f)), interfaceView(sf::Vector2f(480.0f, 270.0f), sf::Vector2f(960.0f, 540.0f)) {
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
    float x = 100 * (static_cast<float>(player->GetHp()) / player->GetMaxHp());
    //avatar = sf::RectangleShape(sf::Vector2f(80.f, 95.f));
    healthBar = sf::RectangleShape(sf::Vector2f(x * 2, 17.f));
 
    // Load interface textures
    avatarTexture = std::make_shared<sf::Texture>();
    if (!avatarTexture->loadFromFile("assets/interface.png")) {
        throw("Couldn't load the avatar texture");
    }
    avatar = sf::Sprite(*avatarTexture.get());
    avatar.setScale(0.125, 0.125);
    avatar.setPosition(2.0f, 2.0f);


    healthBarTexture = std::make_shared<sf::Texture>();
    if (!healthBarTexture->loadFromFile("assets/Healthbar.png")) {
        throw("Couldn't load the healthbar texture");
    }
    healthBar.setScale(0.68f, 1.f);
    healthBar.setTexture(healthBarTexture.get());
    healthBar.setPosition(112.0f, 15.f);
    
    // Load music
    music = std::make_unique<sf::Music>();
    if (!music->openFromFile("assets/soundtrack.wav")) {
        throw("Couldn't load the soundtrack");
    }
    music->setVolume(0.f);
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
   
    
    target.draw(healthBar);
    target.draw(avatar);
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
