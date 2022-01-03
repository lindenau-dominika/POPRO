#pragma once
#include <vector>
#include <deque>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "Teleport.h"
#include "player.h"
#include "enemy.h"
#include "ResourceManager.h"
#include "Arrow.h"
#include "Building.h"

class GameState : public State
{
private:
	// Assets
	std::shared_ptr<ResourceManager> resourceManager;

	// Game objects
	// Entities
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<Arrow> arrows;

	// Backgrounds
	sf::RectangleShape background;
	sf::RectangleShape tavernFloor;
	std::vector<Teleport> teleports;

	// Buildings
	std::vector<Building> buildings;

	// Game state variables
	bool isPlayerInTeleport = false;
	float timeSinceShot;

	// Game interface
	sf::RectangleShape healthBar;
	sf::Sprite avatar;
	sf::RectangleShape avatarFrame;
	sf::Text useText;

	// Debug interface
	sf::Text fpsText;
	sf::Text enemyCountText;
	sf::Text playerPositionText;

	// Cameras
	sf::View gameView;
	sf::View interfaceView;

	// Debug mode state
	bool debugMode;
	bool GetDebugMode() const;
	void SetDebugMode(bool debugMode);

	// Debug objects
	std::deque<std::pair<sf::Vector2f, sf::Vector2f>> lines;

public:
	GameState(StateMachine &machine, std::shared_ptr<ResourceManager> resourceManager);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow &window, float deltaTime);
};