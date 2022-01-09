#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "entity.h"


class NPC : public Entity
{
public:
	NPC(sf::Texture *texture, Animation animation, sf::FloatRect interaction_box, sf::Vector2f position);
	virtual void update(float deltaTime) override;

	const sf::FloatRect GetBounds() const;

private:
	sf::FloatRect bounding_box;
};

