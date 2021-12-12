#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "player.h"

class GameState : public State {
private:
	// Assets
	std::shared_ptr<sf::Texture> playerTexture;
	std::unique_ptr<sf::Music> music;

	// Game objects
	std::unique_ptr<Player> player;
	sf::RectangleShape meme;

	// Camera
	sf::View view;
public:
	GameState(StateMachine& machine);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow& window, float deltaTime);

};