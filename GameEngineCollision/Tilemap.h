#pragma once

#include "AnimatedTiles.h"

enum TileType { NONSOLID, SOLID, RIGHTSLOPED, LEFTSLOPED };

struct Tile
{
	TileType tileType;
	Tile()
	{
		tileType = NONSOLID;
	}
};

class Tilemap : public AnimatedTiles
{
private:
	sf::Texture m_backgroundTexture;
	sf::Sprite	m_backgroundSprite;
	static std::vector<std::vector<Tile>> m_levelMap;

	void initBackground();
	void initLevelmap();
public:	
	static const sf::FloatRect healthFillUpStationTile;
	static const sf::FloatRect increaseMaxHealthTile;
	static const sf::FloatRect saveDiskTile;
	Tilemap();
	static TileType map(int x, int y);

	//Functions
	void render(sf::RenderTarget* target, Player& player);
};