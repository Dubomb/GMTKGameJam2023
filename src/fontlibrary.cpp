#include "fontlibrary.hpp"

FontLibrary::FontLibrary() {

}

FontLibrary::~FontLibrary() {

}

FontLibrary& FontLibrary::getInstance() {
	static FontLibrary instance;
	return instance;
}

bool FontLibrary::loadFont(std::string name, std::string filePath) {
	sf::Font font;

	if (!font.loadFromFile(filePath)) {
		return false;
	}

	fonts[name] = font;

	return true;
}

sf::Font& FontLibrary::getFont(std::string name) {
	return fonts[name];
}
