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
	Animation playerAnimation(playerTexture->getSize(), 8, 8, 0.07f);
	player = std::make_unique<Player>(1337, 1, playerTexture.get(), playerAnimation, 200.0f);

	// Set up enemies
	auto enemyTexture = resourceManager->GetTexture(ResourceIDs::Textures::EnemySpriteSheet);
	Animation enemyAnimation(enemyTexture->getSize(), 8, 8, 0.07f);
	enemies.emplace_back(std::make_unique<Enemy>(10, enemyTexture.get(), enemyAnimation, sf::Vector2f(1500.f, 1300.f), 20.0f));
	enemies.emplace_back(std::make_unique<Enemy>(5, enemyTexture.get(), enemyAnimation, sf::Vector2f(1800.f, 1300.f), 20.0f));

	// Set up background
	background = sf::RectangleShape(sf::Vector2f(1024.0f * 2, 1024.0f * 2));
	background.setPosition(450.0, 450.0);
	background.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::Ground).get());

	tavernFloor = sf::RectangleShape(sf::Vector2f(1024.0f, 1024.0f));
	tavernFloor.setPosition(45000.0, 45000.0);
	tavernFloor.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::TavernInside).get());

	// Set up interface
	avatar = sf::Sprite(*resourceManager->GetTexture(ResourceIDs::Textures::PlayerAvatar));
	avatar.setScale(0.125, 0.125);
	avatar.setPosition(2.0f, 2.0f);

	healthBar = sf::RectangleShape(sf::Vector2f(200, 17.f));
	healthBar.setTexture(resourceManager->GetTexture(ResourceIDs::Textures::HealthBar).get());
	healthBar.setScale(0.68f, 1.f);
	healthBar.setPosition(112.0f, 15.f);

	// Play music
	auto music = resourceManager->GetMusic(ResourceIDs::Music::Overworld);
	music->setVolume(0.f);
	music->setLoop(true);
	music->play();

	// Text
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

	// Set up FPS text
	fpsText.setFont(*font);
	fpsText.setString("X FPS");
	fpsText.setOrigin(0, fpsText.getLocalBounds().height);
	fpsText.setPosition(uiCenter.x - uiSize.x / 2, uiCenter.y + uiSize.y / 2);
	fpsText.setCharacterSize(10);

	// Set up debug texts
	enemyCountText.setFont(*font);
	enemyCountText.setString("dummy");
	enemyCountText.setOrigin(0, enemyCountText.getLocalBounds().height);
	enemyCountText.setPosition(uiCenter.x - uiSize.x / 2, uiCenter.y + uiSize.y / 2 - 20);
	enemyCountText.setCharacterSize(10);

	playerPositionText.setFont(*font);
	playerPositionText.setString("dummy");
	playerPositionText.setOrigin(0, playerPositionText.getLocalBounds().height);
	playerPositionText.setPosition(uiCenter.x - uiSize.x / 2, uiCenter.y + uiSize.y / 2 - 10);
	playerPositionText.setCharacterSize(10);

	// Teleports
	teleports.emplace_back(sf::FloatRect(1720.f, 1770.f, 20.0f, 20.0f), sf::Vector2f(45525.f, 45575.f));
	teleports.emplace_back(sf::FloatRect(45525, 45615, 20.0f, 20.0f), sf::Vector2f(1770.f, 1790.f));

	teleports.emplace_back(sf::FloatRect(1520.f, 1770.f, 20.0f, 20.0f), sf::Vector2f(1900.0f, 1770.0f));
	teleports.emplace_back(sf::FloatRect(1720.f, 1900.0f, 20.0f, 20.0f), sf::Vector2f(1900.0f, 1900.0f));

	// Set up tavern
	buildings.emplace_back(resourceManager->GetTexture(ResourceIDs::Textures::Tavern).get(), sf::Vector2f(137.5, 237.0), sf::Vector2f(1730.0f, 1688.0f), sf::FloatRect(1670.0f, 1620.0f, 120.0, 120.0));
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

		for (auto &[playerPos, endPos] : lines)
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
	target.draw(avatar);
	if (isPlayerInTeleport)
	{
		target.draw(useText);
	}

	// Draw FPS counter in debug mode
	if (GetDebugMode())
	{
		target.draw(fpsText);
		target.draw(enemyCountText);
		target.draw(playerPositionText);
	}
}

void GameState::update(sf::RenderWindow &window, float deltaTime)
{
	sf::Event event;
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
				parent_machine.pop_state();
				return;
			}

			if (event.key.code == sf::Keyboard::B)
			{
				SetDebugMode(!GetDebugMode());
			}
		}
	}

	// Player movement
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

	// Player action
	timeSinceShot += deltaTime;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (timeSinceShot > 0.5)
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, gameView);
			sf::Vector2f playerPos = player->GetPosition();

			lines.emplace_back(playerPos, worldPos);
			if (lines.size() > 4)
			{
				lines.pop_front();
			}

			sf::Vector2f direction = worldPos - playerPos;
			float magnitude = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
			sf::Vector2f normalizedDirection(0, 0);
			if (magnitude != 0)
			{
				normalizedDirection = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
			}

			auto arrowTexture = resourceManager->GetTexture(ResourceIDs::Textures::ArrowSpriteSheet);
			Animation arrowAnimation(arrowTexture->getSize(), 1, 4, 0.12f);
			Arrow arrow(arrowTexture.get(), arrowAnimation, playerPos, normalizedDirection, 330.0f, 3.0f);
			arrows.push_back(arrow);

			timeSinceShot = 0;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (timeSinceShot > 0.5)
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, gameView);

			auto enemyTexture = resourceManager->GetTexture(ResourceIDs::Textures::EnemySpriteSheet);
			Animation enemyAnimation(enemyTexture->getSize(), 8, 8, 0.07f);
			enemies.emplace_back(std::make_unique<Enemy>(9, enemyTexture.get(), enemyAnimation, worldPos, 120.0f));

			timeSinceShot = 0;
		}
	}

	player->Move(playerDirection);
	player->update(deltaTime);
	if (!player->IsAlive())
	{
		parent_machine.pop_state();
		return;
	}

	auto enemy = enemies.begin();
	while (enemy != enemies.end())
	{
		if (!(*enemy)->IsAlive())
		{
			enemy = enemies.erase(enemy);
		}
		else
		{
			(*enemy)->update(deltaTime);
			(*enemy)->HandleCollision(*player);

			sf::Vector2f direction = (*enemy)->GetPosition() - player->GetPosition();
			float magnitude = std::sqrtf(direction.x * direction.x + direction.y * direction.y);
			sf::Vector2f normalizedDirection(0, 0);
			if (magnitude != 0)
			{
				normalizedDirection = sf::Vector2f(direction.x / magnitude, direction.y / magnitude);
			}
			normalizedDirection *= -1.0f;

			(*enemy)->SetDirection(normalizedDirection);
			for (auto &otherEnemy : enemies)
			{
				//(*enemy)->HandleCollision(*otherEnemy);
			}
			enemy++;
		}
	}

	isPlayerInTeleport = false;
	for (auto &teleport : teleports)
	{
		isPlayerInTeleport |= player->GetBounds().intersects(teleport.GetBounds());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && isPlayerInTeleport)
		{
			player->SetPosition(teleport.GetExitPosition());
			isPlayerInTeleport = false;
		}
	}

	auto it = arrows.begin();
	while (it != arrows.end())
	{
		if (!it->IsAlive())
		{
			it = arrows.erase(it);
		}
		else
		{
			it->update(deltaTime);
			for (auto &enemy : enemies)
			{
				it->HandleCollision(*enemy);
			}
			it++;
		}
	}

	for (auto &building : buildings)
	{
		building.HandleCollision(*player);
		for (auto &enemy : enemies)
		{
			building.HandleCollision(*enemy);
		}
	}

	healthBar.setScale(static_cast<float>(player->GetHP()) / player->GetMaxHP() * 0.68f, 1.f);

	if (player->GetPosition().x < 30000)
	{
		gameView.setCenter(player->GetPosition());
		gameView.setSize(sf::Vector2f(700.0f, 384.0f));
	}
	else
	{
		gameView.setCenter(45525.f, 45475.f);
		gameView.setSize(sf::Vector2f(584.0f, 320.0f));
	}

	fpsText.setString(std::to_string(static_cast<int>(1 / deltaTime)) + " FPS");
	enemyCountText.setString(std::to_string(enemies.size()) + " enemies");
	playerPositionText.setString("XY: " + std::to_string(int(player->GetPosition().x)) + " " + std::to_string(int(player->GetPosition().y)) + ", HP: " + std::to_string(player->GetHP()));
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