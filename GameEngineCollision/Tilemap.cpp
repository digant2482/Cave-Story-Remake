#include "stdafx.h"
#include "Tilemap.h"

//Non-member function
const std::vector<std::vector<Tile>> initializeLevelmap(std::string level)
{
	/* Loads tilemap of "tile type" from a text file into a vector 
	*  @returns a vector of vector of tiles
	*/

	std::vector<std::vector<Tile>> levelMap(16, std::vector<Tile>(21));
	std::string path = "Levels/level" + level + ".txt";
	std::ifstream stream(path);
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
std::vector<std::vector<Tile>> Tilemap::m_levelMap;
sf::FloatRect Tilemap::m_healthFillUpStationTile;
sf::FloatRect Tilemap::m_increaseMaxHealthTile;
sf::FloatRect Tilemap::m_saveDiskTile;

//Levels
void Tilemap::loadLevel1()
{
	/* Loads background */
	if (!m_backgroundTexture.loadFromFile("Levels/Level 1.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);

	Tilemap::m_levelMap = initializeLevelmap("1");

	//Animated tiles' tile rectangles wrt to window (Used for collision checking for player)
	m_healthFillUpStationTile   = sf::FloatRect(560.f, 280.f, 40.f, 40.f);
	m_increaseMaxHealthTile     = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);
	m_saveDiskTile              = sf::FloatRect(600.f, 280.f, 40.f, 40.f);

	//Rendering booleans
	m_renderHealthFillUpStation = true;
	m_renderIncreaseMaxHealth   = false;
	m_renderSaveDisk            = true;

	//Level exit tile
	m_levelExitTile = sf::FloatRect(400.f, 120.f, 40.f, 40.f);
}

void Tilemap::loadLevel2()
{
	/* Loads background */
	if (!m_backgroundTexture.loadFromFile("Levels/Level 2.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);

	Tilemap::m_levelMap = initializeLevelmap("2");

	//Animated tiles' tile rectangles wrt to window (Used for collision checking for player)
	m_healthFillUpStationTile   = sf::FloatRect(760.f, 400.f, 40.f, 40.f);
	m_increaseMaxHealthTile     = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);
	m_saveDiskTile              = sf::FloatRect(40.f, 400.f, 40.f, 40.f);

	//Rendering booleans
	m_renderHealthFillUpStation = true;
	m_renderIncreaseMaxHealth   = false;
	m_renderSaveDisk            = true;

	//Level exit tile
	m_levelExitTile = sf::FloatRect(720.f, 160.f, 40.f, 40.f);
}

void Tilemap::loadLevel3()
{
	/* Loads background */
	if (!m_backgroundTexture.loadFromFile("Levels/Level 3.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);

	Tilemap::m_levelMap = initializeLevelmap("3");

	//Animated tiles' tile rectangles wrt to window (Used for collision checking for player)
	m_healthFillUpStationTile   = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);
	m_increaseMaxHealthTile     = sf::FloatRect(760.f, 320.f, 40.f, 40.f);
	m_saveDiskTile              = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);

	//Rendering booleans
	m_renderHealthFillUpStation = false;
	m_renderIncreaseMaxHealth   = true;
	m_renderSaveDisk            = false;

	//Level exit tile
	m_levelExitTile = sf::FloatRect(80.f, 560.f, 40.f, 40.f);
}

void Tilemap::loadLevel4()
{
	/* Loads background */
	if (!m_backgroundTexture.loadFromFile("Levels/Level 4.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);

	Tilemap::m_levelMap = initializeLevelmap("4");

	//Animated tiles' tile rectangles wrt to window (Used for collision checking for player)
	m_healthFillUpStationTile   = sf::FloatRect(720.f, 160.f, 40.f, 40.f);
	m_increaseMaxHealthTile     = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);
	m_saveDiskTile              = sf::FloatRect(760.f, 160.f, 40.f, 40.f);

	//Rendering booleans
	m_renderHealthFillUpStation = true;
	m_renderIncreaseMaxHealth   = false;
	m_renderSaveDisk            = true;

	//Level exit tile
	m_levelExitTile = sf::FloatRect(120.f, 560.f, 40.f, 40.f);
}

void Tilemap::loadLevel5()
{
	/* Loads background */
	if (!m_backgroundTexture.loadFromFile("Levels/Level 5.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);

	Tilemap::m_levelMap = initializeLevelmap("5");

	//Animated tiles' tile rectangles wrt to window (Used for collision checking for player)
	m_healthFillUpStationTile   = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);
	m_increaseMaxHealthTile     = sf::FloatRect(320.f, 400.f, 40.f, 40.f);
	m_saveDiskTile              = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);

	//Rendering booleans
	m_renderHealthFillUpStation = false;
	m_renderIncreaseMaxHealth   = true;
	m_renderSaveDisk            = false;

	//Level exit tile
	m_levelExitTile = sf::FloatRect(480.f, 280.f, 40.f, 40.f);
}

void Tilemap::loadLevel6()
{
	/* Loads background */
	if (!m_backgroundTexture.loadFromFile("Levels/Level 6.png"))
		std::cout << "ERROR::TILEMAP::INITVARIABLES::FAILED TO LOAD MAP" << '\n';
	m_backgroundSprite.setTexture(m_backgroundTexture);

	Tilemap::m_levelMap = initializeLevelmap("6");

	//Animated tiles' tile rectangles wrt to window (Used for collision checking for player)
	m_healthFillUpStationTile = sf::FloatRect(680.f, 120.f, 40.f, 40.f);
	m_increaseMaxHealthTile   = sf::FloatRect(-10.f, -10.f, 0.f, 0.f);
	m_saveDiskTile            = sf::FloatRect(760.f, 120.f, 40.f, 40.f);

	//Rendering booleans
	m_renderHealthFillUpStation = true;
	m_renderIncreaseMaxHealth   = false;
	m_renderSaveDisk            = true;
}

//Constructor
Tilemap::Tilemap()
{
	/* Calls initializers */
	loadLevel1();
}

TileType Tilemap::map(int x, int y)
{
	/* @return tiletype at map co-ordinate (x, y) */
	return m_levelMap[y][x].tileType;
}

//Accessors
sf::FloatRect Tilemap::getHealthFillUpStationTileBounds()
{
	/* @returns health station tile bounds*/
	return m_healthFillUpStationTile;
}

sf::FloatRect Tilemap::getIncreaseMaxHealthTileBounds()
{
	/* @return increase max health tile bounds*/
	return m_increaseMaxHealthTile;
}

sf::FloatRect Tilemap::getSaveDiskTileBounds()
{
	/* @return save disk tile bounds*/
	return m_saveDiskTile;
}

const sf::FloatRect& Tilemap::getLevelExitTile() const
{
	/* @return level exit tile */
	return m_levelExitTile;
}


void Tilemap::render(sf::RenderTarget* target, Player& player)
{
	/* Renders tilemap (whole background) 
	*  Renders animated tiles
	*/

	target->draw(m_backgroundSprite);
	renderAnimatedTiles(target, player, m_healthFillUpStationTile.getPosition(), m_saveDiskTile.getPosition(), 
		m_increaseMaxHealthTile.getPosition(), m_renderHealthFillUpStation, m_renderSaveDisk, m_renderIncreaseMaxHealth);
}