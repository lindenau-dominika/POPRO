#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

const sf::Color SELECTED_COLOR = sf::Color::White;
const int SELECTED_SIZE = 100;
const sf::Color UNSELECTED_COLOR = sf::Color::Cyan;
const int UNSELECTED_SIZE = 90;
const sf::Color TITLE_COLOR = sf::Color::Cyan;
const int TITLE_SIZE = 120;
const sf::Vector2f TITLE_POSITION = sf::Vector2f(220.0f, 50.0f);


class Menu : public sf::Drawable {
private:
	int selected = 0;
	sf::Font font;
	sf::Text title;
	std::vector<sf::Text> options;
	void select(int index);
public:
	Menu(const std::string& title, sf::Font &font);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void add_option(const std::string& contents, const sf::Vector2f position);

	void move_up();
	void move_down();
	int get_selected_option() const;
};