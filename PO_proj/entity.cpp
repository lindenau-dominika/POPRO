#include "entity.h"
#include "animation.h"

Entity::Entity(sf::Texture *texture, Animation animation, float speed, int hp) : animation(animation), speed(speed), maxHp(hp), hp(hp)
{
	alive = true;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(body);
}

sf::RectangleShape *Entity::GetBody()
{
	return &body;
}

sf::FloatRect Entity::GetBounds() const
{
	return body.getGlobalBounds();
}

sf::Vector2f Entity::GetPosition() const
{
	return body.getPosition();
}

sf::Vector2f Entity::GetLastDirection() const
{
	return lastDirection;
}

sf::Vector2f Entity::GetDirection() const
{
	return direction;
}

sf::Vector2f Entity::GetVelocity() const
{
	return velocity;
}

float Entity::GetSpeed() const
{
	return speed;
}

int Entity::GetHP() const
{
	return hp;
}

int Entity::GetMaxHP() const
{
	return maxHp;
}

bool Entity::IsAlive() const
{
	return alive;
}

void Entity::Kill()
{
	this->alive = false;
}

void Entity::TakeDamage(int damage)
{
	if (timeSinceLastDamage >= damageCooldown)
	{
		timeSinceLastDamage = 0.0f;
		hp -= damage;
		if (hp <= 0)
		{
			hp = 0;
			Kill();
		}
	}
}

void Entity::SetPosition(sf::Vector2f position)
{
	body.setPosition(position);
}

void Entity::SetDirection(sf::Vector2f direction)
{
	this->lastDirection = this->direction;
	this->direction = direction;
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Entity::HandleCollision(Entity &other)
{
	auto bounds = GetBounds(), otherBounds = other.GetBounds();
	auto centerX = bounds.left + bounds.width / 2, centerY = bounds.top + bounds.height / 2;
	auto otherCenterX = otherBounds.left + otherBounds.width / 2, otherCenterY = otherBounds.top + otherBounds.height / 2;
	auto dx = centerX - otherCenterX, dy = centerY - otherCenterY;

	auto radiusX = bounds.width / 2, radiusY = bounds.height / 2;
	auto otherRadiusX = otherBounds.width / 2, otherRadiusY = otherBounds.height / 2;

	if (abs(dx) < radiusX + otherRadiusX && abs(dy) < radiusY + otherRadiusY)
	{
		if (abs(dx) > abs(dy))
		{
			int side = (dx > 0) - (dx < 0);
			other.GetBody()->move(-side * (radiusX + otherRadiusX - abs(dx)) / 2, 0);
			GetBody()->move(side * (radiusX + otherRadiusX - abs(dx)) / 2, 0);
			other.TakeDamage(150);
		}
		else
		{
			int side = (dy > 0) - (dy < 0);
			other.GetBody()->move(0, -side * (radiusY + otherRadiusY - abs(dy)) / 2);
			GetBody()->move(0, side * (radiusY + otherRadiusY - abs(dy)) / 2);
			other.TakeDamage(150);
		}
	}
}

bool Entity::Shoot(sf::Vector2f direction) {
	if (timeSinceLastAttack >= attackCooldown) {
		timeSinceLastAttack = 0;
		timeSinceMovementCooldown = 0;

		if (direction.x >= 0) {
			GetAnimation().PlayAnimationOnce(AnimationType::AnimationType::EntityShootingRight, AnimationType::AnimationType::EntityStandingDown);
			SetDirection(sf::Vector2f(0, 0));
		}
		else {
			GetAnimation().PlayAnimationOnce(AnimationType::AnimationType::EntityShootingLeft, AnimationType::AnimationType::EntityStandingUp);
			SetDirection(sf::Vector2f(0, 0));
		}
		return true;
	}
	else {
		return false;
	}
}

void Entity::UpdateCooldown(float deltaTime)
{
	timeSinceLastDamage += deltaTime;
	timeSinceLastAttack += deltaTime;
	timeSinceMovementCooldown += deltaTime;
}

bool Entity::CanMove() const {
	return timeSinceMovementCooldown >= movementCooldown;
}

Animation& Entity::GetAnimation() {
	return animation;
}