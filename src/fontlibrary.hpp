#pragma once

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class FontLibrary {
public:
	FontLibrary();
	~FontLibrary();

	static FontLibrary& getInstance();

	bool loadFont(std::string name, std::string filePath);
	sf::Font& getFont(std::string name);

private:

	std::unordered_map<std::string, sf::Font> fonts;
};