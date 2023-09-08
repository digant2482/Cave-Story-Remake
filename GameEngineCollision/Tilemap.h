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
	static sf::FloatRect m_healthFillUpStationTile;
	static sf::FloatRect m_increaseMaxHealthTile;
	static sf::FloatRect m_saveDiskTile;

	//Rendering booleans
	bool m_renderHealthFillUpStation;
	bool m_renderIncreaseMaxHealth;
	bool m_renderSaveDisk;

	//Level exit tile
	sf::FloatRect m_levelExitTile;

	static std::vector<std::vector<Tile>> m_levelMap;
public:	
	Tilemap();
	void loadLevel1();
	void loadLevel2();
	void loadLevel3();
	void loadLevel4();
	void loadLevel5();
	void loadLevel6();

	//Accessors
	static sf::FloatRect getHealthFillUpStationTileBounds();
	static sf::FloatRect getIncreaseMaxHealthTileBounds();
	static sf::FloatRect getSaveDiskTileBounds();
	const sf::FloatRect& getLevelExitTile() const;
	static TileType map(int x, int y);

	//Functions
	void render(sf::RenderTarget* target, Player& player);
};