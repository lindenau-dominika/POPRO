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
    target.draw(meme);
    target.setView(view);
    target.draw(*player);
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
    view.setCenter(player->GetPosition());
}
