#include "Teleport.h"

Teleport::Teleport(sf::FloatRect teleport_box, sf::Vector2f exit_position) : bounding_box(teleport_box), exit_position(exit_position)
{
}

Teleport::~Teleport()
{
}

const sf::FloatRect Teleport::GetBounds() const
{
	return this->bounding_box;
}


sf::Vector2f Teleport::GetExitPosition() const
{
	return exit_position;
}