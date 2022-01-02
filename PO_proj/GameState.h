#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "Teleport.h"
#include "player.h"
#include "enemy.h"
#include "ResourceManager.h"
#include "Arrow.h"

class GameState : public State {
private:
	// Assets
	std::shared_ptr<ResourceManager> resourceManager;

	// Game objects
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	sf::RectangleShape meme;
	std::vector<Teleport> teleports;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> lines;
	std::vector<Arrow> arrows;
	float timeSinceShot;
	sf::RectangleShape tavern;

	//Interface - Healthbar, avatar
	sf::RectangleShape healthBar;
	sf::Sprite avatar;
	sf::RectangleShape avatarFrame;
	sf::Text fpsText;
	sf::Text enemyCountText;

	// Camera
	sf::View gameView;
	sf::View interfaceView;

	bool debugMode;
	bool GetDebugMode() const;
	void SetDebugMode(bool debugMode);

public:
	GameState(StateMachine& machine, std::shared_ptr<ResourceManager> resourceManager);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow& window, float deltaTime);
};