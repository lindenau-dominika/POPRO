#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"


class Player : public sf::Drawable
{
private:
	int hp;
	int maxHp;
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
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//collecting information about the position of player
	sf::Vector2f GetPosition()
	{
		return body.getPosition();
	}

	int GetHp();
	int GetMaxHp();
	void SubHp(int damage);
};

