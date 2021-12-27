#include "entity.h"
#include "animation.h"

Entity::Entity(int hp, sf::Texture* texture, float speed, float switchTime)
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
//void Entity::looseHp(const int hp)
//{
//	if (this->entity)
//	{
//	this->entity->looseHp(hp);
//	}
//}
//
//const bool Entity::isDead() const
//{
//	if(this->entity)
//	{
//		return this->entity->isDead();
//	}
//	return this-> hp <=0;
//}

void Entity::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//bot
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		//top
		velocity.y = 0.0f;
	}
}

const sf::FloatRect Entity::getBounds() const {
	return bound;
}
