#include "player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float fps, float speed) :
	animation(texture, imageCount, fps)

	this->speed = speed;
this->jumpHeight = jumpHeight;
