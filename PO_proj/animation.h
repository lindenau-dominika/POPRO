#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
		Animation(sf::Texture* texture, sf::Vector2u imageCount, float deltaTime);
	~Animation();

	//metoda do aktualizowania animacji
	void Update(int row, float deltaTime, bool faceRight);
	sf::IntRect uvRect;
	void setSmooth(bool smooth);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	
	float totalTime;
	float deltaTime;
};

