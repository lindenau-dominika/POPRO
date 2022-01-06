#include "GameState.h"
#include "StateMachine.h"
#include "player.h"
#include "entity.h"
#include <algorithm>
#include <iostream>

GameState::GameState(StateMachine &machine, std::shared_ptr<ResourceManager> resourceManager) : State(machine), resourceManager(resourceManager),
																								gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(700.0f, 384.0f)), interfaceView(sf::Vector2f(480.0f, 270.0f), sf::Vector2f(960.0f, 540.0f))
{
	// Set up player
	auto playerTexture = resourceManager->GetTexture(ResourceIDs::Textures::PlayerSpriteSheet);
	Animation playerAnimation(playerTexture->getSize(), 10, 8, 0.07f);
	player = std::make_unique<Player>(1337, 1, playerTexture.get(), playerAnimation, 200.0f);

	// Set up enemies
	auto enemyTexture = resourceManager->GetTexture(ResourceIDs::Textures::EnemySpriteSheet);
	Animation enemyAnimation(enemyTexture->getSize(), 8, 8, 0.07f);
	enemies.emplace_back(std::make_unique<Enemy>(10, enemyTexture.get(), enemyAnimation, sf::Vector2f(1500.f, 1300.f), 20.0f));
	enemies.emplace_back(std::make_unique<Enemy>(5, enemyTexture.get(), enemyAnimation, sf::Vector2f(1800.f, 1300.f), 20.0f));

	// Set up teleports
	teleports.emplace_back(sf::FloatRect(1720.f, 1770.f, 20.0f, 20.0f), sf::Vector2f(45525.f, 45575.f));
	teleports.emplace_back(sf::FloatRect(45525, 45615, 20.0f, 20.0f), sf::Vector2f(1770.f, 1790.f));

	teleports.emplace_back(sf::FloatRect(1520.f, 1770.f, 20.0f, 20.0f), sf::Vector2f(1900.0f, 1770.0f));
	teleports.emplace_back(sf::FloatRect(1720.f, 1900.0f, 20.0f, 20.0f), sf::Vector2f(1900.0f, 1900.0f));

	// Set up buildings
	buildings.emplace_back(resourceManager->GetTexture(ResourceIDs::Textures::Tavern).get(), sf::Vector2f(137.5, 237.0), sf::Vector2f(1730.0f, 1688.0f), sf::FloatRect(1670.0f, 1620.0f, 120.0, 120.0));

	// Set up background
	background = sf::RectangleShape(sf::Vector2f(1024.0f * 2, 1024.0f * 2));
	background.setPosition(450.0, 450.0);
	background.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::Ground).get());

	tavernFloor = sf::RectangleShape(sf::Vector2f(1024.0f, 1024.0f));
	tavernFloor.setPosition(45000.0, 45000.0);
	tavernFloor.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::TavernInside).get());

	// Set up interface
	float interfaceScale = 0.125f;
	playerInterface = sf::Sprite(*resourceManager->GetTexture(ResourceIDs::Textures::PlayerAvatar));
	playerInterface.setScale(interfaceScale, interfaceScale);
	playerInterface.setPosition(2.0f, 2.0f);

	healthBar = sf::RectangleShape(sf::Vector2f(1079.0f, 133.0f) * interfaceScale);
	healthBar.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::HealthBar).get());
	healthBar.setPosition(playerInterface.getPosition() + sf::Vector2f(883.0f, 105.0f) * interfaceScale);

	// Play music
	auto music = resourceManager->GetMusic(ResourceIDs::Music::Overworld);
	music->setVolume(0.f);
	music->setLoop(true);
	music->play();

	// Set up text
	auto font = resourceManager->GetFont(ResourceIDs::Fonts::General);
	sf::Vector2f uiCenter = interfaceView.getCenter();
	sf::Vector2f uiSize = interfaceView.getSize();

	// Set up use text
	useText.setFont(*font);
	useText.setString("Press E to use");
	useText.setOrigin(useText.getLocalBounds().width / 2, useText.getLocalBounds().height);
	useText.setPosition(uiCenter.x, uiCenter.y + uiSize.y / 2 - 10);
	useText.setCharacterSize(20);
	useText.setOutlineThickness(1.0f);

	// Set up debug texts
	float debugCharacterSize = 10;
	float debugTextHeight = font->getLineSpacing(debugCharacterSize);

	fpsText.setFont(*font);
	fpsText.setOrigin(0, debugTextHeight);
	fpsText.setPosition(uiCenter.x - uiSize.x / 2, uiCenter.y + uiSize.y / 2 - debugCharacterSize * 0);
	fpsText.setCharacterSize(debugCharacterSize);

	playerPositionText.setFont(*font);
	playerPositionText.setOrigin(0, debugTextHeight);
	playerPositionText.setPosition(uiCenter.x - uiSize.x / 2, uiCenter.y + uiSize.y / 2 - debugCharacterSize * 1);
	playerPositionText.setCharacterSize(debugCharacterSize);

	enemyCountText.setFont(*font);
	enemyCountText.setOrigin(0, debugTextHeight);
	enemyCountText.setPosition(uiCenter.x - uiSize.x / 2, uiCenter.y + uiSize.y / 2 - debugCharacterSize * 2);
	enemyCountText.setCharacterSize(debugCharacterSize);
}

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Draw world
	target.setView(gameView);
	target.draw(background);
	target.draw(tavernFloor);

	// Object to draw
	struct DrawableObject
	{
		const sf::Drawable *object;
		sf::FloatRect bounds;
		float GetY() const
		{
			return bounds.top + bounds.height;
		}
		DrawableObject(const sf::Drawable *object, sf::FloatRect bounds) : object(object), bounds(bounds){};
	};
	std::vector<DrawableObject> objectsToDraw;

	// Collect buildings to draw
	for (auto &building : buildings)
	{
		objectsToDraw.emplace_back(&building, building.GetBounds());
	}

	// Collect enemies to draw
	for (auto &enemy : enemies)
	{
		objectsToDraw.emplace_back(enemy.get(), enemy->GetBounds());
	}

	// Add player to the list of objects to draw
	objectsToDraw.emplace_back(player.get(), player->GetBounds());

	// Sort objects by Y
	std::sort(objectsToDraw.begin(), objectsToDraw.end(), [](DrawableObject a, DrawableObject b)
			  { return a.GetY() < b.GetY(); });

	// Draw all objects
	for (auto &obj : objectsToDraw)
	{
		target.draw(*obj.object);
	}

	// Draw arrows
	for (auto &arrow : arrows)
	{
		target.draw(arrow);
	}

	// Draw teleports in debug mode
	if (GetDebugMode())
	{
		for (auto &teleport : teleports)
		{
			auto r = teleport.GetBounds();
			sf::RectangleShape tpRect(sf::Vector2f(r.width, r.height));
			tpRect.setPosition(r.left, r.top);
			tpRect.setFillColor(sf::Color(128, 128, 128, 255));
			tpRect.setOutlineThickness(1);
			tpRect.setOutlineColor(sf::Color::White);
			target.draw(tpRect);

			sf::CircleShape exit(3.0);
			exit.setPosition(teleport.GetExitPosition());
			tpRect.setFillColor(sf::Color(128, 128, 128, 255));
			tpRect.setOutlineThickness(1);
			tpRect.setOutlineColor(sf::Color::White);
			target.draw(exit);
		}

		for (auto &[playerPos, endPos] : shotLines)
		{
			sf::Vertex line[] = {
				playerPos,
				endPos};

			target.draw(line, 2, sf::Lines);
		}
	}

	// Draw UI
	target.setView(interfaceView);
	target.draw(healthBar);
	target.draw(playerInterface);
	if (isPlayerInTeleport)
	{
		target.draw(useText);
	}

	// Draw debug mode texts
	if (GetDebugMode())
	{
		target.draw(fpsText);
		target.draw(enemyCountText);
		target.draw(playerPositionText);
	}
}

void GameState::update(sf::RenderWindow &window, float deltaTime)
{
	// Handle window events
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == event.KeyPressed)
		{
			// Go back to main menu
			if (event.key.code == sf::Keyboard::Escape)
			{
				parent_machine.pop_state();
				return;
			}
			// Toggle debug mode
			if (event.key.code == sf::Keyboard::B)
			{
				SetDebugMode(!GetDebugMode());
			}
		}
	}

	// Calculate player movement direction vector
	sf::Vector2f playerDirection;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerDirection.x += -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerDirection.x += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerDirection.y += -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerDirection.y += 1;
	}
	player->SetDirection(playerDirection);

	// Update the player
	player->update(deltaTime);

	// Return to the main menu if player dies
	if (!player->IsAlive())
	{
		parent_machine.pop_state();
		return;
	}

	// Creating the if function which allows us to create an arrow directed to the mouse's position.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Get mouse click screen position
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

		// Get the world position corresponding to the position that was clicked on the screen
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, gameView);

		// Calculate direction vector of arrow
		sf::Vector2f direction = worldPos - player->GetPosition();

		// Create an arrow if player can shoot
		if (player->Shoot(direction))
		{
			// Add debug line between player's position and clicked position
			shotLines.emplace_back(player->GetPosition(), worldPos);

			// Store only last 4 shot lines
			if (shotLines.size() > 4)
			{
				shotLines.pop_front();
			}

			// Get arrow texture
			auto arrowTexture = resourceManager->GetTexture(ResourceIDs::Textures::ArrowSpriteSheet);
			Animation arrowAnimation(arrowTexture->getSize(), 1, 4, 0.12f);

			// Push new arrow onto the list of arrows
			Arrow arrow(arrowTexture.get(), arrowAnimation, player->GetPosition(), direction, 330.0f, 3.0f);
			arrows.push_back(arrow);
		}
	}

	// Update enemies
	auto enemy = enemies.begin();
	while (enemy != enemies.end())
	{
		// Check if enemy is alive
		if (!(*enemy)->IsAlive())
		{
			// Remove enemy if he is dead
			enemy = enemies.erase(enemy);
		}
		else
		{
			// Update enemy
			(*enemy)->update(deltaTime);

			// Handle collision with player
			(*enemy)->HandleCollision(*player);

			// Calculate direction vector to make enemy follow the player
			sf::Vector2f direction = (*enemy)->GetPosition() - player->GetPosition();
			float magnitude = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
			sf::Vector2f normalizedDirection(0, 0);
			if (magnitude != 0)
			{
				normalizedDirection = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
			}
			normalizedDirection *= -1.0f;
			(*enemy)->SetDirection(normalizedDirection);

			// Increment iterator
			enemy++;
		}
	}

	// Player teleportation
	isPlayerInTeleport = false;
	for (auto &teleport : teleports)
	{
		// Check if Player intersects with teleport
		isPlayerInTeleport |= player->GetBounds().intersects(teleport.GetBounds());

		// Interactive feature thanks to which the whole teleportation is going to work only if E is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && isPlayerInTeleport)
		{
			// Teleport player to the exit position
			player->SetPosition(teleport.GetExitPosition());
			isPlayerInTeleport = false;
		}
	}

	// Update arrows
	auto arrow = arrows.begin();
	while (arrow != arrows.end())
	{
		// Check if we are supposed to destroy arrow (after collision or after its lifetime ended)
		if (!arrow->IsAlive())
		{
			// Remove arrow from list of arrows
			arrow = arrows.erase(arrow);
		}
		else
		{
			// Update arrow
			arrow->update(deltaTime);

			// Handle arrow collision with enemies
			for (auto &enemy : enemies)
			{
				arrow->HandleCollision(*enemy);
			}

			// Increment iterator
			arrow++;
		}
	}

	// Handle building collision
	for (auto &building : buildings)
	{
		building.HandleCollision(*player);
		for (auto &enemy : enemies)
		{
			building.HandleCollision(*enemy);
		}
	}

	// Update interface
	healthBar.setScale(static_cast<float>(player->GetHP()) / player->GetMaxHP(), 1.f);

	// TEMP: Set game view center for free-roam and tavern
	if (player->GetPosition().x < 30000)
	{
		// Free-roam in open world
		gameView.setCenter(player->GetPosition());
		gameView.setSize(sf::Vector2f(700.0f, 384.0f));
	}
	else
	{
		// Centered view in tavern
		gameView.setCenter(45525.f, 45475.f);
		gameView.setSize(sf::Vector2f(584.0f, 320.0f));
	}

	// Update debug objects
	if (GetDebugMode())
	{
		UpdateDebugMode(window, deltaTime);
	}
}

bool GameState::GetDebugMode() const
{
	return debugMode;
}

void GameState::SetDebugMode(bool debugMode)
{
	this->debugMode = debugMode;
	if (debugMode)
	{
		player->GetBody()->setOutlineThickness(1);
		for (auto &enemy : enemies)
		{
			enemy->GetBody()->setOutlineThickness(1);
		}
		for (auto &tp : teleports)
		{
		}
		for (auto &building : buildings)
		{
			building.GetBody()->setOutlineThickness(1);
		}
	}
	else
	{
		player->GetBody()->setOutlineThickness(0);
		for (auto &enemy : enemies)
		{
			enemy->GetBody()->setOutlineThickness(0);
		}
		for (auto &tp : teleports)
		{
		}
		for (auto &building : buildings)
		{
			building.GetBody()->setOutlineThickness(0);
		}
	}
}

void GameState::UpdateDebugMode(sf::RenderWindow &window, float deltaTime)
{
	fpsText.setString(std::to_string(static_cast<int>(1 / deltaTime)) + " FPS");
	enemyCountText.setString(std::to_string(enemies.size()) + " enemies");
	playerPositionText.setString("XY: " + std::to_string(int(player->GetPosition().x)) + " " + std::to_string(int(player->GetPosition().y)) + ", HP: " + std::to_string(player->GetHP()));

	// Spawn enemies in debug mode
	timeSinceDebugAction += deltaTime;
	if (timeSinceDebugAction > 0.5)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, gameView);

			auto enemyTexture = resourceManager->GetTexture(ResourceIDs::Textures::EnemySpriteSheet);
			Animation enemyAnimation(enemyTexture->getSize(), 8, 8, 0.07f);
			enemies.emplace_back(std::make_unique<Enemy>(9, enemyTexture.get(), enemyAnimation, worldPos, 120.0f));

			timeSinceDebugAction = 0;
		}
	}
}
