#pragma once
#include <SFML/Graphics.hpp>

namespace AnimationType {
	enum AnimationType {
		// Entity (player or enemy) animation rows
		EntityStandingDown = 0,
		EntityStandingUp = 1,
		EntityStandingLeft = 2,
		EntityStandingRight = 3,
		EntityWalkingDown = 4,
		EntityWalkingUp = 5,
		EntityWalkingLeft = 6,
		EntityWalkingRight = 7,
		EntityDefault = EntityStandingDown,

		// Arrow animation rows
		ArrowDefault = 0,

		// Default
		Default = 0,
	};
}

class Animation
{
public:
	Animation(sf::Vector2u textureSize, int animations, int frames, float switchTime);

	void Update(float deltaTime);
	void ChangeAnimation(AnimationType::AnimationType animationType);
	sf::IntRect GetUVRect();

private:
	int animations;
	int frames;
	float switchTime;
	float totalTime = 0.0f;
	
	AnimationType::AnimationType currentAnimation = AnimationType::Default;
	int currentFrame = 0;

	sf::IntRect uvRect;
};

