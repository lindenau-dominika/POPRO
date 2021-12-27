#include "enemy.h"

Enemy::Enemy(int hp, sf::Texture* texture, int animations, int frames, sf::Vector2f position, float speed, float switchTime) :
animation(texture->getSize(), animations, frames, switchTime), Entity(hp, texture, speed, switchTime) {
	this->speed = speed;
	row = 0;

	body.setSize(sf::Vector2f(20.0f, 20.f));
    body.setPosition(position);
	body.setOrigin(30.0f, 48.0f);
	body.setTexture(texture);
	velocity.x = speed;
}


Enemy::~Enemy() {
}

void Enemy::update(float deltaTime) {

	if (body.getPosition().x >= 600.0f)
	{
		velocity.x = -speed;
	}
	if (body.getPosition().x <= 450.0f)
	{
		velocity.x = speed;
	}


    animation.Update(deltaTime);
    body.setTextureRect(animation.GetUVRect());
    body.move(velocity.x * deltaTime, velocity.y * deltaTime);
}