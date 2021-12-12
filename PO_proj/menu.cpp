#include "menu.h"

Menu::Menu(const std::string& title, sf::Font &font) : font(font)
{
	this->title.setFont(font);
	this->title.setString(title);
	this->title.setCharacterSize(TITLE_SIZE);
	this->title.setFillColor(TITLE_COLOR);
	this->title.setPosition(TITLE_POSITION);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(title);
	for (auto& option : options) {
		target.draw(option);
	}
}

void Menu::add_option(const std::string& contents, const sf::Vector2f position) {
	sf::Text text;
	text.setFont(font);
	text.setString(contents);
	text.setPosition(position);

	// Select new option by default if there are no other options
	if (options.size() == 0) {
		text.setCharacterSize(SELECTED_SIZE);
		text.setFillColor(SELECTED_COLOR);
	}
	else {
		text.setCharacterSize(UNSELECTED_SIZE);
		text.setFillColor(UNSELECTED_COLOR);
	}

	// Add new option to the list of options
	options.push_back(std::move(text));
}

void Menu::select(int index)
{
	// Check for out-of-bounds index
	if (index >= 0 && index < options.size()) {
		// Unselect currently selected option
		options.at(selected).setCharacterSize(UNSELECTED_SIZE);
		options.at(selected).setFillColor(UNSELECTED_COLOR);

		// Select new option
		selected = index;
		options.at(index).setCharacterSize(SELECTED_SIZE);
		options.at(index).setFillColor(SELECTED_COLOR);
	}
}

void Menu::move_up()
{
	int index = (selected - 1) % static_cast<int>(options.size());
	select(index);
}

void Menu::move_down()
{
	int index = (selected + 1) % static_cast<int>(options.size());
	select(index);
}

int Menu::get_selected_option() const
{
	return selected;
}
