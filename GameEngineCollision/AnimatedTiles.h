#pragma once
#include "Player.h"
class AnimatedTiles
{
private:
	//Texture and sprites
	sf::Texture m_animatedTilesTexture;
	sf::Sprite m_animatedTilesSpriteSheet;

	//Tiles' texture rectangles
	sf::IntRect m_healthFillUpStation;
	sf::IntRect m_saveDisk;
	sf::IntRect m_increaseMaxHealth;

	//Tiles' positions
	sf::Vector2f m_healthFillUpStationPosition;
	sf::Vector2f m_saveDiskPosition;
	sf::Vector2f m_increaseMaxHealthPosition;

	//Animation timer
	sf::Clock m_animationTimer;

	//Initializers
	void initSprite();
	void initTextureRectangles();
	void initTilesPositions();

protected:
	//Constructor
	AnimatedTiles();

	//Functions
	void updateTextureRectangles();
	void renderAnimatedTiles(sf::RenderTarget* target, Player& player);
};