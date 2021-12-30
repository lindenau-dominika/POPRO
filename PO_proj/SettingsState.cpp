#include "SettingsState.h"
#include "StateMachine.h"

SettingsState::SettingsState(StateMachine& machine, const std::string& contents, std::shared_ptr<ResourceManager> resourceManager) : State(machine), resourceManager(resourceManager) {
    text.setFont(*resourceManager->GetFont(ResourceIDs::Fonts::General));
    text.setString("U dont need this but ok. its W S A D. glhf");
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(200.0, 400.0));
}

void SettingsState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text);
}

void SettingsState::update(sf::RenderWindow& window, float deltaTime)
{
    sf::Event event;

    // Poll events
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
}