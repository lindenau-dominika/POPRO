#include "ResourceManager.h"

std::shared_ptr<sf::Texture> ResourceManager::GetTexture(ResourceIDs::Textures id) const
{
	return textures.at(id);
}

std::shared_ptr<sf::Font> ResourceManager::GetFont(ResourceIDs::Fonts id) const
{
	return fonts.at(id);
}

std::shared_ptr<sf::Music> ResourceManager::GetMusic(ResourceIDs::Music id) const
{
	return music.at(id);
}

void ResourceManager::LoadAll()
{
	// Load textures
	LoadTexture(ResourceIDs::Textures::MenuBackground, "assets/menu.png");
	LoadTexture(ResourceIDs::Textures::PlayerSpriteSheet, "assets/player.png");
	LoadTexture(ResourceIDs::Textures::PlayerAvatar, "assets/interface.png");
	LoadTexture(ResourceIDs::Textures::HealthBar, "assets/healthbar.png");
	LoadTexture(ResourceIDs::Textures::EnemySpriteSheet, "assets/enemo.png");
	LoadTexture(ResourceIDs::Textures::Ground, "assets/basicc.png");

	// Load fonts
	LoadFont(ResourceIDs::Fonts::General, "assets/arial.ttf");

	// Load music
	LoadMusic(ResourceIDs::Music::Overworld, "assets/soundtrack.wav");
}

void ResourceManager::LoadTexture(ResourceIDs::Textures id, std::string path)
{
	auto texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(path)) {
		throw("Couldn't load texture: " + path);
	}

	textures[id] = texture;
}

void ResourceManager::LoadFont(ResourceIDs::Fonts id, std::string path)
{
	auto font = std::make_shared<sf::Font>();
	if (!font->loadFromFile(path)) {
		throw("Couldn't load font: " + path);
	}

	fonts[id] = font;
}


void ResourceManager::LoadMusic(ResourceIDs::Music id, std::string path)
{
	auto music = std::make_shared<sf::Music>();
	if (!music->openFromFile(path)) {
		throw("Couldn't load music: " + path);
	}

	this->music[id] = music;
}
