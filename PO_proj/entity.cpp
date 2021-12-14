#include "entity.h"
#include "animation.h"

Entity::Entity(int hp, sf::Texture* texture, float speed, sf::Vector2u imageCount, float switchTime)
{
	this->speed = speed;
	row = 0;
    this->hp = hp;
    this->maxHp = hp;
}

Entity::~Entity() 
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(body);
}

int Entity::GetHp()
{
	return hp;
}

int Entity::GetMaxHp()
{
	return maxHp;
}

void Entity::SubHp(int damage)
{
	if (damage > hp) {
		hp = 0;
	}
	else {
		hp -= damage;
	}
}
