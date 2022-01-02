#include "player.h"
#include "entity.h"
#include "animation.h"

Player::Player(int hp, int level, sf::Texture* texture, Animation animation, float speed) :
	animation(animation), Entity(texture, speed) {
	this->level = level;


	GetBody()->setSize(sf::Vector2f(32.0f, 38.4f));
	GetBody()->setPosition(450.0f, 450.0f);
	GetBody()->setTexture(texture);
	GetBody()->setOrigin(GetBody()->getSize().x / 2, GetBody()->getSize().y / 2);
}


void Player::Move(sf::Vector2i direction)
{
	SetDirection(direction);
}

//declaring the movement
void Player::update(float deltaTime)
{
	auto lastDirection = GetLastDirection();
	auto direction = GetDirection();

	if (lastDirection != direction) {
		if (direction.x == 0) {
			// Moving down vertically
			if (direction.y > 0) {
				animation.ChangeAnimation(AnimationType::WalkingDown);
			}
			// Standing still
			else if (direction.y == 0) {
				if (lastDirection.y < 0) {
					animation.ChangeAnimation(AnimationType::StandingUp);
				}
				else {
					animation.ChangeAnimation(AnimationType::StandingDown);
				}
			}
			// Moving up vertically
			else {
				animation.ChangeAnimation(AnimationType::WalkingUp);
			}
		}
		else if (direction.x > 0) {
			// Moving down-right
			if (direction.y > 0) {
				animation.ChangeAnimation(AnimationType::WalkingDown);
			}
			// Moving right horizontally
			else if (direction.y == 0) {
				animation.ChangeAnimation(AnimationType::WalkingRight);
			}
			// Moving up-right
			else {
				animation.ChangeAnimation(AnimationType::WalkingUp);
			}
		}
		else {
			// Moving down-left
			if (direction.y > 0) {
				animation.ChangeAnimation(AnimationType::WalkingDown);
			}
			// Moving left horizontally
			else if (direction.y == 0) {
				animation.ChangeAnimation(AnimationType::WalkingLeft);
			}
			// Moving up-left
			else {
				animation.ChangeAnimation(AnimationType::WalkingUp);
			}
		}
	}

	float magnitude = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f normalizedDirection(0, 0);
	if (magnitude != 0) {
		normalizedDirection = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
	}
	float dx = normalizedDirection.x * GetSpeed();
	float dy = normalizedDirection.y * GetSpeed();

	animation.Update(deltaTime);
	GetBody()->setTextureRect(animation.GetUVRect());
	GetBody()->move(dx * deltaTime, dy * deltaTime);	
}
