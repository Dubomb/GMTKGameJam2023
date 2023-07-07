#include "texturelibrary.hpp"

TextureLibrary::TextureLibrary() {

}

TextureLibrary::~TextureLibrary() {

}

TextureLibrary& TextureLibrary::getInstance() {
	static TextureLibrary instance;
	return instance;
}

bool TextureLibrary::loadTexture(std::string name, std::string filePath) {
	sf::Texture texture;

	if (!texture.loadFromFile(filePath)) {
		return false;
	}

	textures[name] = texture;

	return true;
}

sf::Texture& TextureLibrary::getTexture(std::string name) {
	return textures[name];
}