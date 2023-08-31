#pragma once

enum TileType {NONSOLID, SOLID, RIGHTSLOPED, LEFTSLOPED};

struct Tile
{
	TileType tileType;
	Tile()
	{
		tileType = NONSOLID;
	}
};

class Tilemap
{
private:
	sf::Texture m_backgroundTexture;
	sf::Sprite	m_backgroundSprite;
	static std::vector<std::vector<Tile>> m_levelMap;

	void initBackground();
	void initLevelmap();
public:	

	Tilemap();
	static TileType map(int x, int y);

	//Functions
	void render(sf::RenderTarget* target);
};