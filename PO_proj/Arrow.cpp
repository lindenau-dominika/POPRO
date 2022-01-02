#include "Arrow.h"
#include <cmath>

Arrow::Arrow(sf::Texture* texture, Animation animation, sf::Vector2f initialPosition, sf::Vector2f direction, float speed, float lifeTime) : animation(animation), position(initialPosition), lifeTime(lifeTime) {
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setPosition(position);
	body.setTexture(texture);
	velocity = sf::Vector2f(direction.x * speed, direction.y * speed);
}

void Arrow::update(float deltaTime) {
	// Update position
	float speed = std::sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
	body.move(velocity.x * deltaTime, velocity.y * deltaTime);

	// Update rotation
	const float PI = std::atan(1.0) * 4;
	float angle = std::atan2(velocity.y, velocity.x) * (180.0 / PI);
	body.setRotation(angle);

	// Update velocity
	velocity.x = velocity.x * (1 - deltaTime * deaccelaration_rate.x);
	velocity.y = velocity.y * (1 - deltaTime * deaccelaration_rate.y);

	// Update lifetime
	time += deltaTime;

	// Update animation
	animation.Update(deltaTime);
	body.setTextureRect(animation.GetUVRect());
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
