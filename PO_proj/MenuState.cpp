#include "MenuState.h"
#include "GameState.h"
#include "SettingsState.h"
#include "StateMachine.h"
#include <memory>

MenuState::MenuState(StateMachine &machine, const std::string &title, std::shared_ptr<ResourceManager> resourceManager) : State(machine), resourceManager(resourceManager), menuView(sf::View(sf::Vector2f(910.0f, 512.0f), sf::Vector2f(1820.0f, 1024.0f)))
{
	this->title.setFont(*resourceManager->GetFont(ResourceIDs::Fonts::General).get());
	this->title.setString(title);
	this->title.setCharacterSize(TITLE_SIZE);
	this->title.setFillColor(TITLE_COLOR);
	this->title.setPosition(TITLE_POSITION);

	menuBackground = sf::RectangleShape(sf::Vector2f(1820.0f, 1024.0f));
	menuBackground.setPosition(0.0, 0.0);
	menuBackground.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::MenuBackground).get());
}

void MenuState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.setView(menuView);
	target.draw(title);
	target.draw(menuBackground);
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
}

void MenuState::add_option(const std::string &contents, const sf::Vector2f position)
{
	sf::Text text;
	text.setFont(*resourceManager->GetFont(ResourceIDs::Fonts::General));
	text.setString(contents);
	text.setPosition(position);
	text.setOutlineThickness(5);

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
