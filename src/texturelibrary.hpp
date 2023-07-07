#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureLibrary {
public:
	TextureLibrary();
	~TextureLibrary();

	static TextureLibrary& getInstance();

	bool loadTexture(std::string name, std::string filePath);
	sf::Texture& getTexture(std::string name);

private:

	std::unordered_map<std::string, sf::Texture> textures;
};