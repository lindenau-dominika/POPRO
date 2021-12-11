#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"


class Player
{
private:
	float speed;
	Animation animation;
	sf::FloatRect bound;
	sf::Vector2f velocity;
	sf::RectangleShape body;
	bool faceRight;
	unsigned int row;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float deltaTime, float speed);
	~Player();
	//creating the functions responsible for updating the display, so the player wont be leaving any pixels behind 
	void update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	//collecting information about the position of player
	sf::Vector2f GetPosition()
	{
		return body.getPosition();
	}
};

