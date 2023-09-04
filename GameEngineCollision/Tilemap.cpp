#include "stdafx.h"
#include "Tilemap.h"

//Non-member function
const std::vector<std::vector<Tile>> initializeLevelmap()
{
	/* Loads tilemap of "tile type" from a text file into a vector 
	*  @returns a vector of vector of tiles
	*/
	std::vector<std::vector<Tile>> levelMap(16, std::vector<Tile>(21));
	std::ifstream stream("Levels/level1.txt");
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			std::string symbol;
			stream >> symbol;
			if (symbol == "W")
				levelMap[i][j].tileType = SOLID;
			else if (symbol == "L")
				levelMap[i][j].tileType = LEFTSLOPED;
			else if (symbol == "R")
				levelMap[i][j].tileType = RIGHTSLOPED;
		}
	}
	stream.close();
	return levelMap;
}

//Define the static member variable
const std::vector<std::vector<Tile>> Tilemap::m_levelMap = initializeLevelmap();

//Animated tiles' tile rectangles wrt to window (Used for collision checking for player)
const sf::FloatRect Tilemap::healthFillUpStationTile = sf::FloatRect(560.f, 280.f, 40.f, 40.f);
const sf::FloatRect Tilemap::increaseMaxHealthTile   = sf::FloatRect(440.f, 120.f, 40.f, 40.f);
const sf::FloatRect Tilemap::saveDiskTile            = sf::FloatRect(600.f, 280.f, 40.f, 40.f);

//Member functions
void Tilemap::initBackground()
{
	/* Loads background */
	if (!m_backgroundTexture.loadFromFile("Levels/L1.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);
}

Tilemap::Tilemap()
{
	/* Calls initializers */
	initBackground();
}

TileType Tilemap::map(int x, int y)
{
	/*@return tiletype at map co-ordinate (x, y)*/
	return m_levelMap[y][x].tileType;
}

void Tilemap::render(sf::RenderTarget* target, Player& player)
{
	/* Renders tilemap (whole background) 
	*  Renders animated tiles
	*/

	target->draw(m_backgroundSprite);
	sf::CircleShape cir;
	cir.setRadius(2.f);
	cir.setFillColor(sf::Color::Red);
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			cir.setPosition(40 * j, 40 * i);
			target->draw(cir);
		}
	}
	renderAnimatedTiles(target, player);
}