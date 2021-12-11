#include "animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float fps)
{
	//just some cute pointers that everybody loves and admire
	this->imageCount = imageCount;
	this->deltaTime = deltaTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	//setting the proper frame for an object
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{

}
void Animation::Update(int row, float deltaTime, bool faceRight)
{

	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= deltaTime)
	{
		
	}
}