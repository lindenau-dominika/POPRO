#pragma once
#include <SFML/Graphics.hpp>
namespace AnimationType {
	enum AnimationType {
		// StandingDown = 0,
		// StandingUp = 1,
		// StandingLeft = 2,
		// StandingRight = 3,
		// WalkingDown = 4,
		// WalkingUp = 5,
		// WalkingLeft = 6,
		// WalkingRight = 7,
		// Default = StandingDown,

		// Temporary values
		StandingDown = 3,
		StandingUp = 4,
		StandingLeft = 3,
		StandingRight = 3,
		WalkingDown = 1,
		WalkingUp = 2,
		WalkingLeft = 5,
		WalkingRight = 0,
		Default = StandingDown,
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

