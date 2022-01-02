#include "ResourceManager.h"

std::unordered_map<ResourceIDs::Textures, std::string> ResourceManager::texturePaths = {
	{ResourceIDs::Textures::MenuBackground, "assets/menu.png"},
	{ResourceIDs::Textures::PlayerSpriteSheet, "assets/player.png"},
	{ResourceIDs::Textures::PlayerAvatar, "assets/interface.png"},
	{ResourceIDs::Textures::HealthBar, "assets/healthbar.png"},
	{ResourceIDs::Textures::EnemySpriteSheet, "assets/enemo.png"},
	{ResourceIDs::Textures::Ground, "assets/basicc.png"},
	{ResourceIDs::Textures::ArrowSpriteSheet, "assets/arrow_animation.png"},
	{ResourceIDs::Textures::Tavern, "assets/tavern.png"},
};

std::unordered_map<ResourceIDs::Fonts, std::string> ResourceManager::fontPaths = {
	{ResourceIDs::Fonts::General, "assets/arial.ttf"}
};

std::unordered_map<ResourceIDs::Music, std::string> ResourceManager::musicPaths = {
	{ResourceIDs::Music::Overworld, "assets/soundtrack.wav"}
};


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
	for (auto const& [id, path] : texturePaths) {
		LoadTexture(id, path);
	}

	// Load fonts
	for (auto const& [id, path] : fontPaths) {
		LoadFont(id, path);
	}

	// Load music
	for (auto const& [id, path] : musicPaths) {
		LoadMusic(id, path);
	}
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
