#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "animation.h"

class Arrow : public sf::Drawable
{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f deaccelaration_rate = sf::Vector2f(0.2f, 0.2f);
    sf::RectangleShape body;
    Animation animation;

    float lifeTime;
    float time = 0.0f;

public:
    Arrow(sf::Texture* texture, Animation animation, sf::Vector2f initialPosition, sf::Vector2f direction, float speed, float lifeTime);
    void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f GetPosition() const;
    sf::Vector2f GetVelocity() const;

    bool HasLifeTimeEnded() const;
};