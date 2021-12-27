#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "Collider.h"
#include "entity.h"


class Enemy : public Entity
{
public:
	Enemy(int hp, sf::Texture* texture, int animations, int frames, sf::Vector2f position, float speed, float switchTime);
	~Enemy();
	/*virtual const bool isDead() const;*/
	void update(float deltaTime);

private:
	Animation animation;
};



//class Druid : public Enemy
//{
//    Druid(int hp);
//};