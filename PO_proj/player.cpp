#include "player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float deltaTime, float speed) :
	animation(texture, imageCount, deltaTime) {
	this->speed = speed;

	body.setSize(sf::Vector2f(80.0f, 112.0f));
	body.setPosition(128.0f, 450.0f);
	body.setOrigin(40.0f, 56.0f);
	body.setTexture(texture);
}

Player::~Player()
{

}
//declaring the movement
void Player::update(float deltaTime) 
{
	bound = body.getGlobalBounds();
	velocity.x = 0.0f;
	velocity.y = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y = speed;
	}

	body.move(velocity.x * deltaTime, velocity.y * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}