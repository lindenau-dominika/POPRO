#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"

class Entity : public sf::Drawable
{
public:
	Entity(sf::Texture *texture, float speed, int maxHp);

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::RectangleShape *GetBody();
	sf::FloatRect GetBounds() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetLastDirection() const;
	sf::Vector2f GetDirection() const;
	sf::Vector2f GetVelocity() const;
	float GetSpeed() const;
	int GetHP() const;
	int GetMaxHP() const;
	bool IsAlive() const;
	void TakeDamage(int damage);
	void Kill();

	void SetPosition(sf::Vector2f position);
	void SetDirection(sf::Vector2f direction);
	void SetVelocity(sf::Vector2f velocity);

	void HandleCollision(Entity &other);
	void SetDamageCooldown(float coolDown)
	{
		damageCooldown = coolDown;
	}

protected:
	void UpdateCooldown(float deltaTime)
	{
		timeSinceLastDamage += deltaTime;
	}

private:
	sf::RectangleShape body;
	sf::FloatRect bound;

	sf::Vector2f direction;
	sf::Vector2f lastDirection;

	sf::Vector2f velocity;
	float speed;

	float damageCooldown = 1.0f;
	float timeSinceLastDamage = damageCooldown;

	int hp;
	int maxHp;
	bool alive = true;
};
