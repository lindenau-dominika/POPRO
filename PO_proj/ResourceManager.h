#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

namespace ResourceIDs {
	enum class Textures {
		MenuBackground,
		Ground,
		PlayerSpriteSheet,
		PlayerAvatar,
		HealthBar,
		EnemySpriteSheet,
		ArrowSpriteSheet,
		Tavern,
	};

	enum class Fonts {
		General,
	};

	enum class Music {
		Overworld,
	};
}

class ResourceManager {
public:
	std::shared_ptr<sf::Texture> GetTexture(ResourceIDs::Textures id) const;
	std::shared_ptr<sf::Font> GetFont(ResourceIDs::Fonts id) const;
	std::shared_ptr<sf::Music> GetMusic(ResourceIDs::Music id) const;

	void LoadAll();

	void LoadTexture(ResourceIDs::Textures id, std::string path);
	void LoadFont(ResourceIDs::Fonts id, std::string path);
	void LoadMusic(ResourceIDs::Music id, std::string path);

private:
	std::unordered_map<ResourceIDs::Textures, std::shared_ptr<sf::Texture>> textures;
	std::unordered_map<ResourceIDs::Fonts, std::shared_ptr<sf::Font>> fonts;
	std::unordered_map<ResourceIDs::Music, std::shared_ptr<sf::Music>> music;
 
	static std::unordered_map<ResourceIDs::Textures, std::string> texturePaths;
	static std::unordered_map<ResourceIDs::Fonts, std::string> fontPaths;
	static std::unordered_map<ResourceIDs::Music, std::string> musicPaths;
};