#include "player.h"
#include "entity.h"
#include "animation.h"

Player::Player(int hp, int level, sf::Texture* texture, int animations, int frames, float switchTime, float speed) :
	animation(texture->getSize(), animations, frames, switchTime), Entity(hp, texture, speed, switchTime) {
	this->speed = speed;
	this->level = level;
	row = 0;

	body.setSize(sf::Vector2f(32.0f, 38.4f));
	body.setPosition(450.0f, 450.0f);
	body.setOrigin(30.0f, 48.0f);
	body.setTexture(texture);
}

Player::~Player()
{

}

void Player::Move(sf::Vector2i direction)
{
	this->direction = direction;
}

//declaring the movement
void Player::update(float deltaTime) 
{
 	bound = body.getGlobalBounds();
	velocity.x = 0.0f;
	velocity.y = 0.0f;

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
		lastDirection = direction;
	}

	float magnitude = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f normalizedDirection(0, 0);
	if (magnitude != 0) {
		normalizedDirection = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
	}
	velocity.x = normalizedDirection.x * speed;
	velocity.y = normalizedDirection.y * speed;

	animation.Update(deltaTime);
	body.setTextureRect(animation.GetUVRect());
	body.move(velocity.x * deltaTime, velocity.y * deltaTime);	
}
