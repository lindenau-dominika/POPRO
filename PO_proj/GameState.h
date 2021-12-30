#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "Teleport.h"
#include "player.h"
#include "enemy.h"

class GameState : public State {
private:
	// Assets
	std::shared_ptr<sf::Texture> playerTexture;
	std::shared_ptr<sf::Texture> enemyTexture;
	std::shared_ptr<sf::Texture> avatarTexture;
	std::shared_ptr<sf::Texture> groundTexture;
	std::shared_ptr<sf::Texture> healthBarTexture;
	std::unique_ptr<sf::Music> music;
	std::unique_ptr<sf::Font> font;

	// Game objects
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	sf::RectangleShape meme;
	std::vector<Teleport> teleports;
	
	//Interface - Healthbar, avatar
	sf::RectangleShape healthBar;
	sf::Sprite avatar;
	sf::RectangleShape avatarFrame;
	sf::Text fpsText;

	// Camera
	sf::View gameView;
	sf::View interfaceView;

	bool debugMode;
	bool GetDebugMode() const;
	void SetDebugMode(bool debugMode);

public:
	GameState(StateMachine& machine);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow& window, float deltaTime);
};