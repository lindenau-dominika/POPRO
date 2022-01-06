#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "entity.h"

class Enemy : public Entity
{
public:
	Enemy(int hp, sf::Texture *texture, Animation animation, sf::Vector2f position, float speed);
	~Enemy();
	virtual void update(float deltaTime) override;

private:
	bool alive;
};
