#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "entity.h"

class Player : public Entity
{
public:
	Player(int hp, int level, sf::Texture *texture, Animation animation, float speed);
	void Move(sf::Vector2f direction);
	virtual void update(float deltaTime) override;

private:
	int level;
	int lvl();
	int exp();
	int lvlUp();
};
