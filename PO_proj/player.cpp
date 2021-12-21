#include "player.h"
#include "entity.h"
#include "animation.h"

Player::Player(int hp, int level, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime), Entity(hp, texture, speed, imageCount, switchTime) {
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

//declaring the movement
void Player::update(float deltaTime) 
{
 	bound = body.getGlobalBounds();
	velocity.x = 0.0f;
	velocity.y = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -speed;
		row = 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = speed;
		row = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y = -speed;
		row = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y = speed;
		row = 1;
	}
	if (abs(velocity.x) < 0.1f && abs(velocity.y) < 0.1f)
	{
		row = 3;
	}
	// float a, b, c, d;
	// if (body.getPosition().x >= a &&  body.getPosition().y == b)
	// {

	// 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	// 	body.setPosition(-200.f, -200.f);
	// }
	// if (body.getPosition().x == c; body.getPosition().y == d)
	// {
	// 	body.setPosition(a, b + 20.f);
	// }

	
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity.x * deltaTime, velocity.y * deltaTime);	
}
