#include "enemy.h"

Enemy::Enemy(int hp, sf::Texture *texture, Animation animation, sf::Vector2f position, float speed) : Entity(texture, animation, speed, hp)
{
	GetBody()->setSize(sf::Vector2f(20.0f, 20.f));
	GetBody()->setPosition(position);
	GetBody()->setOrigin(GetBody()->getSize() / 2.0f);
	GetBody()->setTexture(texture);
	SetVelocity(sf::Vector2f(GetSpeed(), 0));

	SetDamageCooldown(0.25f);
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime)
{
	UpdateCooldown(deltaTime);
	SetVelocity(sf::Vector2f(GetDirection().x * GetSpeed(), GetDirection().y * GetSpeed()));

	GetAnimation().Update(deltaTime);
	GetBody()->setTextureRect(GetAnimation().GetUVRect());
	GetBody()->move(GetVelocity().x * deltaTime, GetVelocity().y * deltaTime);
}