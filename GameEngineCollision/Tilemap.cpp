#include "stdafx.h"
#include "Tilemap.h"

// Define the static member variable
std::vector<std::vector<Tile>> Tilemap::m_levelMap;

//Animated tiles FloatRect wrt to window
const sf::FloatRect Tilemap::healthFillUpStationTile = sf::FloatRect(560.f, 280.f, 40.f, 40.f);
const sf::FloatRect Tilemap::increaseMaxHealthTile   = sf::FloatRect(440.f, 120.f, 40.f, 40.f);
const sf::FloatRect Tilemap::saveDiskTile            = sf::FloatRect(600.f, 280.f, 40.f, 40.f);

void Tilemap::initBackground()
{
	//Use case : Render the background on window
	if (!m_backgroundTexture.loadFromFile("Levels/L1.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);
}

void Tilemap::initLevelmap()
{
	//Use case : Tilemap creation

	m_levelMap.resize(16, std::vector<Tile>(21));
	std::ifstream stream("Levels/level1.txt");
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			std::string symbol;
			stream >> symbol;
			if (symbol == "W")
				m_levelMap[i][j].tileType = SOLID;
			else if (symbol == "L")
				m_levelMap[i][j].tileType = LEFTSLOPED;
			else if (symbol == "R")
				m_levelMap[i][j].tileType = RIGHTSLOPED;
		}
	}
	stream.close();
}

Tilemap::Tilemap()
{
	initBackground();
	initLevelmap();
}

TileType Tilemap::map(int x, int y)
{
	return m_levelMap[y][x].tileType;
}

void Tilemap::render(sf::RenderTarget* target, Player& player)
{
	sf::CircleShape cir;
	cir.setRadius(2.f);
	cir.setFillColor(sf::Color::Red);
	target->draw(m_backgroundSprite);
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