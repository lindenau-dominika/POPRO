#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"

class Arrow
{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f deaccelaration_rate = sf::Vector2f(5.0f, 5.0f);

public:
    Arrow(sf::Vector2f initial_position, sf::Vector2f initial_velocity);
    void update(float delta_time);

};

