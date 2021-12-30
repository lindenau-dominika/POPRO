#include "GameState.h"
#include "StateMachine.h"
#include "player.h"
#include "entity.h"
#include <iostream>

GameState::GameState(StateMachine& machine) : State(machine), gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f)), interfaceView(sf::Vector2f(480.0f, 270.0f), sf::Vector2f(960.0f, 540.0f)) {
    // Load player texture
    playerTexture = std::make_shared<sf::Texture>();
    if (!playerTexture->loadFromFile("assets/player.png")) {
        throw("Couldn't load the player texture");
    }
    enemyTexture = std::make_shared<sf::Texture>();
    if (!enemyTexture->loadFromFile("assets/enemo.png")) {
        throw("Couldn't load the enemy texture");
    }

    // Set up enemies
    Animation enemyAnimation(enemyTexture->getSize(), 8, 8, 0.07f);
    enemies.emplace_back(std::make_unique<Enemy>(1377, enemyTexture.get(), enemyAnimation, sf::Vector2f(500.f, 500.f), 20.0f));
    enemies.emplace_back(std::make_unique<Enemy>(1377, enemyTexture.get(), enemyAnimation, sf::Vector2f(800.f, 500.f), 20.0f));

    // Set up player
    Animation playerAnimation(playerTexture->getSize(), 6, 8, 0.07f);
    player = std::make_unique<Player>(1337, 1, playerTexture.get(), playerAnimation, 200.0f);

    // Set up field
    meme = sf::RectangleShape(sf::Vector2f(614.4f, 614.4f));
    
    groundTexture = std::make_shared<sf::Texture>();
    if (!groundTexture->loadFromFile("assets/basicc.png"))
    {
        throw("couldn't load the ground Texture");
    }
    meme.setPosition(450.0, 450.0);
    meme.setTexture(groundTexture.get());

    //Interface - Healthbar, 
    // player->GetHp()) / player->GetMaxHp()
    float x = 100 * (static_cast<float>(0.5/1.0));
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

    // Teleports
    teleports.emplace_back(sf::FloatRect(100.f, 100.f, 300.f, 300.f), sf::Vector2f(420.f, 666.f));
}

//void GameState::isDead() const
//{
//   unsigned index = 0;
//for(auto *enemy : this ->activeEnemies)
//{
//    enemy->update(dt, this->mousePosView);
//
//    this->updateCombat(enemy, index, deltaTime);
//    
//}
//
//   if (enemy->get()->hp <= 0) {}
//}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw world
    target.setView(gameView);
    target.draw(meme);
    target.draw(*player);
    for (auto& enemy : enemies) {
        target.draw(*enemy);
    }

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

    // Player movement
    sf::Vector2i playerDirection;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerDirection.x += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerDirection.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        playerDirection.y += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        playerDirection.y += 1;
    }

    player->Move(playerDirection);
    player->update(deltaTime);
    for(auto& enemy : enemies) {
        enemy->update(deltaTime);
        enemy->HandleCollision(*player);
    }

    for(auto teleport : teleports) {
        if (player->GetBounds().intersects(teleport.GetBounds()))
        {
            player->SetPosition(teleport.GetExitPosition());
        } 
    }

    gameView.setCenter(player->GetPosition());
}
