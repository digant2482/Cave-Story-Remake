#pragma once

#include "Player.h"
#include "Gun.h"

class HUD
{
private:
	sf::Texture m_texture;
	sf::Sprite m_spriteSheet;

	//Health and Gun Variables
	int m_currentHealth;
	float m_currentBarWidthMax;
	float m_currentBarHeight;
	int m_currentGunLevel;
	int m_maxGunLevel;

	//Elements
	sf::IntRect m_healthBarBackground;
	sf::RectangleShape m_currentHealthBar;
	sf::IntRect m_gunLevelBarBackground;
	sf::RectangleShape m_currentGunLevelBar;
	sf::IntRect m_healthNumber;

	//Element's positions
	sf::Vector2f m_healthBarBackgroundPos;
	sf::Vector2f m_gunLevelBarBackgroundPos;
	sf::Vector2f m_healthNumberPos;

	void initSprite();
	void initVariables();
	void initElements();
	void initElementPositions();

	void setCurrentBars(Player& player);
	void setText();
public:
	HUD();

	void update(Player& player);
	void render(sf::RenderTarget* target);
};