#include "Arrow.h"

Arrow::Arrow(sf::Vector2f initialPosition, sf::Vector2f direction, float speed, float lifeTime) : position(initialPosition), lifeTime(lifeTime) {
	body.setSize(sf::Vector2f(3.0f, 3.0f));
	body.setPosition(position);
	velocity = sf::Vector2f(direction.x * speed, direction.y * speed);
}

void Arrow::update(float deltaTime) {
	// Update velocity and position
	float speed = std::sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
	body.move(velocity.x * deltaTime, velocity.y * deltaTime);
	velocity.x = velocity.x * (1 - deltaTime * deaccelaration_rate.x);
	velocity.y = velocity.y * (1 - deltaTime * deaccelaration_rate.y);

	// Update lifetime
	time += deltaTime;
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body);
}

sf::Vector2f Arrow::GetPosition() const
{
	return body.getPosition();
}

sf::Vector2f Arrow::GetVelocity() const {
	return velocity;
}

bool Arrow::HasLifeTimeEnded() const
{
	return time > lifeTime;
}
