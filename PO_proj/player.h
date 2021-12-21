#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "entity.h"

class Player :  public Entity
{
private:
	Animation animation;
	int row;
	int level;
	int lvl();
	int exp();
	int lvlUp();

public:
	Player(int hp, int level, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();
	//creating the functions responsible for updating the display, so the player wont be leaving any pixels behind 
	void update(float deltaTime);
	/*const sf::FloatRect getBounds() const;*/



};

