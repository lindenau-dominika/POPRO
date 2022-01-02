#include "animation.h"

Animation::Animation(sf::Vector2u textureSize, int animations, int frames, float switchTime) : switchTime(switchTime), animations(animations), frames(frames)
{
	uvRect.width = textureSize.x / frames;
	uvRect.height = textureSize.y / animations;
}

void Animation::Update(float deltaTime)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentFrame += 1;

		// Wrap around if we went past last frame
		if (currentFrame >= frames)
		{
			currentFrame = 0;

		}
	}
	uvRect.left = currentFrame * uvRect.width;
	uvRect.top = currentAnimation * uvRect.height;
}

void Animation::ChangeAnimation(AnimationType::AnimationType animationType)
{
	if (animationType != currentAnimation) {
		// Revert to default animation if we try to use non-existing animation
		if (currentAnimation >= animations)
		{
			currentAnimation = AnimationType::EntityDefault;
		}

		totalTime = 0;
		currentAnimation = animationType;
		currentFrame = 0;
	}
}

sf::IntRect Animation::GetUVRect()
{
	return uvRect;
}

