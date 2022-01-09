#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "ResourceManager.h"


//const sf::Color SELECTED_COLOR = sf::Color::Color(245.f, 238.f, 245.f, 255.f);
//const sf::Color SELECTED_COLOR = sf::Color::Color(243.f, 242.f, 255.f, 255.f);
const sf::Color SELECTED_COLOR = sf::Color::Color(236.f, 235.f, 251.f, 255.f);
const int SELECTED_SIZE = 100;
//const sf::Color UNSELECTED_COLOR = sf::Color::Color(99.f, 166.f, 204.f, 160.f);
const sf::Color UNSELECTED_COLOR = sf::Color::Color(188.f, 190.f, 217.f, 255.f);
const int UNSELECTED_SIZE = 90;
const sf::Color TITLE_COLOR = sf::Color::Color(0.f, 128.f, 0.f, 255.f);
const int TITLE_SIZE = 120;
const sf::Vector2f TITLE_POSITION = sf::Vector2f(220.0f, 50.0f);

class MenuState : public State
{
private:
	float totalTime = 0.0f;
	int selected = 0;
	sf::Text title;
	std::vector<sf::Text> options;
	sf::View menuView;
	void select(int index);
	sf::RectangleShape menuBackground;
	sf::RectangleShape menuStars;
	sf::RectangleShape menuStars1;
	sf::RectangleShape menuStars2;

	std::shared_ptr<ResourceManager> resourceManager;

public:
	MenuState(StateMachine &machine, const std::string &title, std::shared_ptr<ResourceManager> resourceManager);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(sf::RenderWindow &window, float deltaTime);
	void add_option(const std::string &contents, const sf::Vector2f position);

	void move_up();
	void move_down();
	int get_selected_option() const;
};