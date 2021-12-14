#include "player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float deltaTime, float speed) :
	animation(texture, imageCount, switchTime) {
	this->speed = speed;
	maxHp = hp = 1337;

	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(60.0f, 64.0f));
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

	
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity.x * deltaTime, velocity.y * deltaTime);	
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(body);
}

int Player::GetHp()
{
	return hp;
}

int Player::GetMaxHp()
{
	return maxHp;
}

void Player::SubHp(int damage)
{
	if (damage > hp) {
		hp = 0;
	}
	else {
		hp -= damage;
	}
}
