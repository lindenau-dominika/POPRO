#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Teleport
{
private:
	sf::FloatRect bounding_box;
	sf::Vector2f exit_position;

public:
	Teleport(sf::FloatRect teleport_box, sf::Vector2f exit_position);
	~Teleport();

	const sf::FloatRect GetBounds() const;
	// bool IsStandingOnTeleport(sf::Vector2f position) const ;
	sf::Vector2f GetExitPosition() const;



};

/*

Teleport -> teleportowa³

Kurcze szefie, s³uszna uwaga ^^^^

*/