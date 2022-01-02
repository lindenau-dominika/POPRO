#include "GameState.h"
#include "StateMachine.h"
#include "player.h"
#include "entity.h"
#include <iostream>

GameState::GameState(StateMachine& machine, std::shared_ptr<ResourceManager> resourceManager) : State(machine), resourceManager(resourceManager), 
gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f)), interfaceView(sf::Vector2f(480.0f, 270.0f), sf::Vector2f(960.0f, 540.0f)) {
    // Set up enemies
    auto enemyTexture = resourceManager->GetTexture(ResourceIDs::Textures::EnemySpriteSheet);
    Animation enemyAnimation(enemyTexture->getSize(), 8, 8, 0.07f);
    enemies.emplace_back(std::make_unique<Enemy>(1377, enemyTexture.get(), enemyAnimation, sf::Vector2f(500.f, 500.f), 20.0f));
    enemies.emplace_back(std::make_unique<Enemy>(1377, enemyTexture.get(), enemyAnimation, sf::Vector2f(800.f, 500.f), 20.0f));

    // Set up player
    auto playerTexture = resourceManager->GetTexture(ResourceIDs::Textures::PlayerSpriteSheet);
    Animation playerAnimation(playerTexture->getSize(), 6, 8, 0.07f);
    player = std::make_unique<Player>(1337, 1, playerTexture.get(), playerAnimation, 200.0f);

    // Set up field
    meme = sf::RectangleShape(sf::Vector2f(614.4f, 614.4f));
    meme.setPosition(450.0, 450.0);
    meme.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::Ground).get());

    //Interface - Healthbar, 
    // player->GetHp()) / player->GetMaxHp()
    float x = 100 * (static_cast<float>(0.5/1.0));
    //avatar = sf::RectangleShape(sf::Vector2f(80.f, 95.f));
    healthBar = sf::RectangleShape(sf::Vector2f(x * 2, 17.f));
 
    // Load interface textures
    avatar = sf::Sprite(*resourceManager->GetTexture(ResourceIDs::Textures::PlayerAvatar));
    avatar.setScale(0.125, 0.125);
    avatar.setPosition(2.0f, 2.0f);

    healthBar.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::HealthBar).get());
    healthBar.setScale(0.68f, 1.f);
    healthBar.setPosition(112.0f, 15.f);
    
    // Load music
    auto music = resourceManager->GetMusic(ResourceIDs::Music::Overworld);
    music->setVolume(0.f);
    music->setLoop(true);
    music->play();

    // Text
    auto font = resourceManager->GetFont(ResourceIDs::Fonts::General);

    // Set up FPS text
    fpsText.setFont(*font);
    sf::Vector2f uiCenter = interfaceView.getCenter();
    sf::Vector2f uiSize = interfaceView.getSize();
    
    fpsText.setString("X FPS");
    fpsText.setOrigin(0, fpsText.getLocalBounds().height);
    fpsText.setPosition(uiCenter.x - uiSize.x / 2, uiCenter.y + uiSize.y / 2);
    fpsText.setCharacterSize(10);


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

    for (auto& arrow : arrows) {
        target.draw(arrow);
    }

    // Draw teleports in debug mode
    if (GetDebugMode()) {
        for (auto& teleport : teleports) {
            auto r = teleport.GetBounds();
            sf::RectangleShape tpRect(sf::Vector2f(r.width, r.height));
            tpRect.setPosition(r.left, r.top);
            tpRect.setFillColor(sf::Color(128, 128, 128, 255));
            tpRect.setOutlineThickness(1);
            tpRect.setOutlineColor(sf::Color::White);
            target.draw(tpRect);

            sf::CircleShape exit(3.0);
            exit.setPosition(teleport.GetExitPosition());
            tpRect.setFillColor(sf::Color(128, 128, 128, 255));
            tpRect.setOutlineThickness(1);
            tpRect.setOutlineColor(sf::Color::White);
            target.draw(exit);
        }

        for (auto& [playerPos, endPos] : lines) {
            sf::Vertex line[] = {
                playerPos,
                endPos
            };

            target.draw(line, 2, sf::Lines);
        }
    }

    // Draw UI
    target.setView(interfaceView); 
    target.draw(healthBar);
    target.draw(avatar);

    // Draw FPS counter in debug mode
    if (GetDebugMode()) {
        target.draw(fpsText);
    }
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

            if (event.key.code == sf::Keyboard::B) {
                SetDebugMode(!GetDebugMode());
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

    // Player action
    timeSinceShot += deltaTime;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (timeSinceShot > 0.5) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, gameView);
            sf::Vector2f playerPos = player->GetPosition();
            lines.emplace_back(playerPos, worldPos);

            sf::Vector2f direction = worldPos - playerPos;
            float magnitude = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
            sf::Vector2f normalizedDirection(0, 0);
            if (magnitude != 0) {
                normalizedDirection = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
            }

            Arrow arrow(playerPos, normalizedDirection, 200.0f, 3.0f);
            arrows.push_back(arrow);

            timeSinceShot = 0;
        }
    }

    player->Move(playerDirection);
    player->update(deltaTime);
    for(auto& enemy : enemies) {
        enemy->update(deltaTime);
        enemy->HandleCollision(*player);
    }

    for(auto& teleport : teleports) {
        if (player->GetBounds().intersects(teleport.GetBounds()))
        {
            player->SetPosition(teleport.GetExitPosition());
        } 
    }

    auto it = arrows.begin();
    while (it != arrows.end()) {
        if (it->HasLifeTimeEnded()) {
            it = arrows.erase(it);
        }
        else {
            it->update(deltaTime);
            it++;
        }
    }

    gameView.setCenter(player->GetPosition());
    fpsText.setString(std::to_string(static_cast<int>(1 / deltaTime)) + " FPS");
}


bool GameState::GetDebugMode() const
{
    return debugMode;
}

void GameState::SetDebugMode(bool debugMode)
{
    this->debugMode = debugMode;
    if (debugMode) {
        player->GetBody()->setOutlineThickness(1);
        for (auto& enemy : enemies) {
            enemy->GetBody()->setOutlineThickness(1);
        }
        for (auto& tp : teleports) {
            
        }
    }
    else {
        player->GetBody()->setOutlineThickness(0);
        for (auto& enemy : enemies) {
            enemy->GetBody()->setOutlineThickness(0);
        }
        for (auto& tp : teleports) {

        }
    }
}