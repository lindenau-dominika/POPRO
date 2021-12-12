#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "state.h"

class SettingsState : public State {
private:
	sf::Font font;
	sf::Text text;
public:
	SettingsState(StateMachine& machine, const std::string& contents, sf::Font& font);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow& window, float deltaTime);
};