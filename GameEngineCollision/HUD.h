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
	int m_currentGunLevel;
	float m_currentBarWidthMax;
	float m_currentBarHeight;

	//Elements
	sf::IntRect m_healthBarBackground;
	sf::RectangleShape m_currentHealthBar;
	sf::IntRect m_gunLevelBarBackground;
	sf::RectangleShape m_currentGunLevelBar;
	sf::IntRect m_healthNumber;
	sf::IntRect m_gunLevelNumber;
	sf::IntRect m_textLV;

	//Element's positions
	sf::Vector2f m_healthBarBackgroundPos;
	sf::Vector2f m_gunLevelBarBackgroundPos;
	sf::Vector2f m_healthNumberPos;
	sf::Vector2f m_gunLevelNumberPos;
	sf::Vector2f m_textLVPos;

	void initSprite();
	void initVariables();
	void initElements();
	void initElementPositions();

	void setCurrentBars(Player& player, Gun& gun);
	void setText();
public:
	HUD();

	void update(Player& player, Gun& gun);
	void render(sf::RenderTarget* target);
};