#include "MenuState.h"
#include "GameState.h"
#include "SettingsState.h"
#include "StateMachine.h"
#include <memory>
#include <cmath>
#include <math.h>

MenuState::MenuState(StateMachine &machine, const std::string &title, std::shared_ptr<ResourceManager> resourceManager) : State(machine), resourceManager(resourceManager), menuView(sf::View(sf::Vector2f(910.0f, 512.0f), sf::Vector2f(1820.0f, 1024.0f)))
{
	this->title.setFont(*resourceManager->GetFont(ResourceIDs::Fonts::General).get());
	this->title.setString(title);
	this->title.setCharacterSize(TITLE_SIZE);
	this->title.setFillColor(TITLE_COLOR);
	this->title.setPosition(TITLE_POSITION);

	/*
	std::vec
	*/

	menuBackground = sf::RectangleShape(sf::Vector2f(1820.0f, 1024.0f));
	menuBackground.setPosition(0.0, 0.0);
	menuBackground.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::MenuBackground).get());
	menuStars = sf::RectangleShape(sf::Vector2f(2135.f, 1281.f));
	menuStars.setPosition(0.0, 0.0);
	menuStars.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::MenuStars).get());
	menuStars1 = sf::RectangleShape(sf::Vector2f(2135.f, 1281.f));
	menuStars1.setPosition(0.0, 0.0);
	menuStars1.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::MenuStars1).get());
	menuStars2 = sf::RectangleShape(sf::Vector2f(2135.f, 1281.f));
	menuStars2.setPosition(0.0, 0.0);
	menuStars2.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::MenuStars2).get());
}

void MenuState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.setView(menuView);
	target.draw(title);
	target.draw(menuBackground);
	target.draw(menuStars);
	target.draw(menuStars2);
	for (auto &option : options)
	{
		target.draw(option);
	}
}

void MenuState::update(sf::RenderWindow &window, float deltaTime)
{
	sf::Event event;

	// Poll events
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == event.KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}

			if (event.key.code == sf::Keyboard::Down)
			{
				move_down();
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				move_up();
			}
			if (event.key.code == sf::Keyboard::Enter or event.key.code == sf::Keyboard::Space)
			{

				int selected_option = get_selected_option();
				if (selected_option == 0)
				{
					// Enter the play state
					GameState gameState(parent_machine, resourceManager);
					parent_machine.push_state(std::make_unique<GameState>(std::move(gameState)));
				}
				else if (selected_option == 1)
				{
					// Options menu state
					SettingsState settingsState(parent_machine, "U dont need this but ok. its W S A D. glhf", resourceManager);
					parent_machine.push_state(std::make_unique<SettingsState>(std::move(settingsState)));
				}
				else if (selected_option == 2)
				{
					window.close();
				}
			}
		}
	}
	
	// Move stars
	totalTime += deltaTime; 
	menuStars.move(deltaTime * -20.0f, deltaTime * -10.0f);
	menuStars2.move(deltaTime * -23.f, deltaTime * -12.f);
	float starsAlpha = std::abs(std::cosf(totalTime * 0.5f)) * 255.0f;
	float starsAlpha1 = std::abs(std::sinf(totalTime * 0.5f)) * 255.0f;
	menuStars.setFillColor(sf::Color(255, 255, 255, starsAlpha));
	menuStars2.setFillColor(sf::Color(255, 255, 255, starsAlpha1));
	if (starsAlpha <= 0.25f)
	{
		menuStars.setPosition(0.f, 0.f);
	}
	if (starsAlpha1 <= 0.25f)
	{
		menuStars2.setPosition(0.f, 0.f);
	}


}

void MenuState::add_option(const std::string &contents, const sf::Vector2f position)
{
	sf::Text text;
	text.setFont(*resourceManager->GetFont(ResourceIDs::Fonts::General));
	text.setString(contents);
	text.setPosition(position);
	text.setOutlineThickness(2);

	// Select new option by default if there are no other options
	if (options.size() == 0)
	{
		text.setCharacterSize(SELECTED_SIZE);
		text.setFillColor(SELECTED_COLOR);
	}
	else
	{
		text.setCharacterSize(UNSELECTED_SIZE);
		text.setFillColor(UNSELECTED_COLOR);
	}

	// Add new option to the list of options
	options.push_back(std::move(text));
}

void MenuState::select(int index)
{
	// Check for out-of-bounds index
	if (index >= 0 && index < options.size())
	{
		// Unselect currently selected option
		options.at(selected).setCharacterSize(UNSELECTED_SIZE);
		options.at(selected).setFillColor(UNSELECTED_COLOR);

		// Select new option
		selected = index;
		options.at(index).setCharacterSize(SELECTED_SIZE);
		options.at(index).setFillColor(SELECTED_COLOR);
	}
}

void MenuState::move_up()
{
	int index = selected - 1;
	if (selected == 0)
	{
		index = options.size() - 1;
	}
	select(index);
}

void MenuState::move_down()
{
	int index = selected + 1;
	if (selected == options.size() - 1)
	{
		index = 0;
	}
	select(index);
}

int MenuState::get_selected_option() const
{
	return selected;
}
