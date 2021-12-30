#include "enemy.h"

Enemy::Enemy(int hp, sf::Texture* texture, Animation animation, sf::Vector2f position, float speed) :
animation(animation), Entity(texture, speed) {
	GetBody()->setSize(sf::Vector2f(20.0f, 20.f));
    GetBody()->setPosition(position);
	GetBody()->setOrigin(30.0f, 48.0f);
	GetBody()->setTexture(texture);
	SetVelocity(sf::Vector2f(GetSpeed(), 0));
}


Enemy::~Enemy() {
}

void Enemy::update(float deltaTime) {
	if (GetBody()->getPosition().x >= 600.0f)
	{
		SetVelocity(sf::Vector2f(-GetSpeed(), 0)); 
	}
	if (GetBody()->getPosition().x <= 450.0f)
	{
		SetVelocity(sf::Vector2f(GetSpeed(), 0));
	}
	

    animation.Update(deltaTime);
    GetBody()->setTextureRect(animation.GetUVRect());
    GetBody()->move(GetVelocity().x * deltaTime, GetVelocity().y * deltaTime);
}