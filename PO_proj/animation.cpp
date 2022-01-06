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

		// Handle animation's end
		if (currentFrame >= frames)
		{
			if (playOnce) {
				// Stop current animation and play the next animation continuously
				playOnce = false;
				ChangeAnimation(nextAnimation);
			}
			else {
				// Wrap around if we went past last frame and we are playing the animation continuously
				currentFrame = 0;
			}
		}
	}
	uvRect.left = currentFrame * uvRect.width;
	uvRect.top = currentAnimation * uvRect.height;
}

void Animation::ChangeAnimation(AnimationType::AnimationType animationType)
{
	// Revert to default animation if we try to use non-existing animation
	if (animationType >= animations)
	{
		animationType = AnimationType::EntityDefault;
	}

	if (animationType != currentAnimation)
	{
		if (playOnce) {
			nextAnimation = animationType;
		}
		else {
			totalTime = 0;
			currentAnimation = animationType;
			currentFrame = 0;
		}
	}
}

void Animation::PlayAnimationOnce(AnimationType::AnimationType animationType, AnimationType::AnimationType nextAnimation)
{
	// Revert to default animation if we try to use non-existing animation
	if (currentAnimation >= animations)
	{
		currentAnimation = AnimationType::EntityDefault;
	}

	totalTime = 0;
	currentAnimation = animationType;
	this->nextAnimation = nextAnimation;
	currentFrame = 0;
	playOnce = true;
}

sf::IntRect Animation::GetUVRect()
{
	return uvRect;
}
