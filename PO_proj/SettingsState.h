#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "ResourceManager.h"

class SettingsState : public State {
private:
	std::shared_ptr<ResourceManager> resourceManager;
	sf::Text text;
public:
	SettingsState(StateMachine& machine, const std::string& contents, std::shared_ptr<ResourceManager> resourceManager);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow& window, float deltaTime);
};