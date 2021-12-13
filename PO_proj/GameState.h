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
	std::shared_ptr<sf::Texture> avatarTexture;
	std::shared_ptr<sf::Texture> healthBarTexture;
	std::shared_ptr<sf::Texture> frameBarTexture;
	std::unique_ptr<sf::Music> music;

	// Game objects
	std::unique_ptr<Player> player;
	sf::RectangleShape meme;
	
	// Temp variables for health
	int hp;
	int maxHp;

	//Interface - Healthbar, avatar
	sf::RectangleShape healthBar;
	sf::RectangleShape frameBar;
	sf::RectangleShape avatar;
	sf::RectangleShape avatarFrame;

	// Camera
	sf::View gameView;
	sf::View interfaceView;
public:
	GameState(StateMachine& machine);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow& window, float deltaTime);
};