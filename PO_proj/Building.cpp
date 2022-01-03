#include "Building.h"

Building::Building(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

Building::Building(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::FloatRect customCollisionBox) : Building(texture, size, position)
{
	this->useCustomCollisionBox = true;
	this->customCollisionBox = customCollisionBox;
}

Building::~Building()
{
}

void Building::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(body);
}

void Building::HandleCollision(Entity &entity)
{
	auto bounds = GetBounds(), entityBounds = entity.GetBounds();
	auto centerX = bounds.left + bounds.width / 2, centerY = bounds.top + bounds.height / 2;
	auto otherCenterX = entityBounds.left + entityBounds.width / 2, otherCenterY = entityBounds.top + entityBounds.height / 2;
	auto dx = centerX - otherCenterX, dy = centerY - otherCenterY;

	auto radiusX = bounds.width / 2, radiusY = bounds.height / 2;
	auto otherRadiusX = entityBounds.width / 2, otherRadiusY = entityBounds.height / 2;

	if (abs(dx) < radiusX + otherRadiusX && abs(dy) < radiusY + otherRadiusY)
	{
		if (abs(dx) > abs(dy))
		{
			int side = (dx > 0) - (dx < 0);
			entity.GetBody()->move(-side * (radiusX + otherRadiusX - abs(dx)), 0);
		}
		else
		{
			int side = (dy > 0) - (dy < 0);
			entity.GetBody()->move(0, -side * (radiusY + otherRadiusY - abs(dy)));
		}
	}
}

sf::FloatRect Building::GetBounds() const
{
	if (useCustomCollisionBox)
	{
		return customCollisionBox;
	}
	else
	{
		return body.getGlobalBounds();
	}
}

sf::RectangleShape *Building::GetBody()
{
	return &body;
}