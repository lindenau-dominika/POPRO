#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"

class Building : public sf::Drawable
{
public:
	Building(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	Building(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::FloatRect customCollisionBound);
	~Building();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
	void HandleCollision(Entity& entity);
	sf::FloatRect GetBounds() const;
	sf::RectangleShape* GetBody();
	sf::Vector2f GetPosition() const {
		return body.getPosition();
	}
private:
	sf::RectangleShape body;
	sf::FloatRect customCollisionBox;
	bool useCustomCollisionBox = false;
};