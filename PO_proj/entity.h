#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "animation.h"

class Entity : public sf::Drawable
{
public:
	Entity(int hp, sf::Texture* texture, float speed, sf::Vector2u imageCount, float switchTime);
	~Entity();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void OnCollision(sf::Vector2f direction);
	const sf::FloatRect getBounds() const;

	sf::Vector2f GetPosition()
	{
		return body.getPosition();
	}
	Collider GetCollider()
	{
		return Collider(body);
	}

	int GetHp();
	int GetMaxHp();
	void looseHp();
	void SubHp(int damage);
	bool getExists();
	void kill();
	const bool isDead() const;
	

    //we gotta think about inheritance 
public:
	sf::RectangleShape body;
	float speed;
	unsigned int row;
	bool faceRight;
	sf::Vector2f velocity;
	sf::FloatRect bound;
	bool exists;
	int hp;
	int maxHp;
};
