#pragma once
#include <SFML/Graphics.hpp>

namespace AnimationType
{
	enum AnimationType
	{
		// Entity (player or enemy) animation rows
		EntityStandingDown = 0,
		EntityStandingUp = 1,
		EntityStandingLeft = 2,
		EntityStandingRight = 3,
		EntityWalkingDown = 4,
		EntityWalkingUp = 5,
		EntityWalkingLeft = 6,
		EntityWalkingRight = 7,
		EntityShootingRight = 8,
		EntityShootingLeft = 9,
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
	void PlayAnimationOnce(AnimationType::AnimationType animationType, AnimationType::AnimationType nextAnimation);
	sf::IntRect GetUVRect();

private:
	int animations;
	int frames;
	float switchTime;
	float totalTime = 0.0f;

	// Determines if currently playing animation is supposed to play only once (not continuously)
	bool playOnce = false;

	// Currenty playing animation
	AnimationType::AnimationType currentAnimation = AnimationType::Default;

	// Animation that will play after the animation that was played once
	AnimationType::AnimationType nextAnimation = AnimationType::Default;

	int currentFrame = 0;

	sf::IntRect uvRect;
};
