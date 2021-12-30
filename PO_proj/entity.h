#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "animation.h"

class Entity : public sf::Drawable
{
public:
	Entity(sf::Texture* texture, float speed);

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape* GetBody();
	sf::FloatRect GetBounds() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2i GetLastDirection() const;
	sf::Vector2i GetDirection() const;
	sf::Vector2f GetVelocity() const;
	float GetSpeed() const;

	void SetPosition(sf::Vector2f position);
	void SetDirection(sf::Vector2i direction);
	void SetVelocity(sf::Vector2f velocity);

	void HandleCollision(Entity& other);
	
private:
	sf::RectangleShape body;
	sf::FloatRect bound;

	sf::Vector2i direction;
	sf::Vector2i lastDirection;

	sf::Vector2f velocity;
	float speed;
};
