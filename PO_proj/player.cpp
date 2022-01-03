#include "player.h"
#include "entity.h"
#include "animation.h"

Player::Player(int hp, int level, sf::Texture *texture, Animation animation, float speed) : animation(animation), Entity(texture, speed, hp)
{
	this->level = level;
	SetDamageCooldown(1.0f);

	GetBody()->setSize(sf::Vector2f(40.0, 56.0));
	GetBody()->setPosition(1450.0f, 1450.0f);
	GetBody()->setTexture(texture);
	GetBody()->setOrigin(GetBody()->getSize().x / 2, GetBody()->getSize().y / 2);
}

void Player::Move(sf::Vector2f direction)
{
	SetDirection(direction);
}

//declaring the movement
void Player::update(float deltaTime)
{
	UpdateCooldown(deltaTime);

	auto lastDirection = GetLastDirection();
	auto direction = GetDirection();

	if (lastDirection != direction)
	{
		if (direction.x == 0)
		{
			// Moving down vertically
			if (direction.y > 0)
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingDown);
			}
			// Standing still
			else if (direction.y == 0)
			{
				if (lastDirection.y < 0)
				{
					animation.ChangeAnimation(AnimationType::EntityStandingUp);
				}
				else
				{
					animation.ChangeAnimation(AnimationType::EntityStandingDown);
				}
			}
			// Moving up vertically
			else
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingUp);
			}
		}
		else if (direction.x > 0)
		{
			// Moving down-right
			if (direction.y > 0)
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingDown);
			}
			// Moving right horizontally
			else if (direction.y == 0)
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingRight);
			}
			// Moving up-right
			else
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingUp);
			}
		}
		else
		{
			// Moving down-left
			if (direction.y > 0)
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingDown);
			}
			// Moving left horizontally
			else if (direction.y == 0)
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingLeft);
			}
			// Moving up-left
			else
			{
				animation.ChangeAnimation(AnimationType::EntityWalkingUp);
			}
		}
	}

	float magnitude = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f normalizedDirection(0, 0);
	if (magnitude != 0)
	{
		normalizedDirection = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
	}
	float dx = normalizedDirection.x * GetSpeed();
	float dy = normalizedDirection.y * GetSpeed();

	animation.Update(deltaTime);
	GetBody()->setTextureRect(animation.GetUVRect());
	GetBody()->move(dx * deltaTime, dy * deltaTime);
}
