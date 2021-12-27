#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "entity.h"

class Player :  public Entity
{
private:
	Animation animation;
	sf::Vector2i direction;
	sf::Vector2i lastDirection;
	int row;
	int level;
	int lvl();
	int exp();
	int lvlUp();

public:
	Player(int hp, int level, sf::Texture* texture, int animations, int frames, float switchTime, float speed);
	~Player();
	void Move(sf::Vector2i direction);
	//creating the functions responsible for updating the display, so the player wont be leaving any pixels behind 
	void update(float deltaTime);
	/*const sf::FloatRect getBounds() const;*/



};

