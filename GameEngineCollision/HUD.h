#pragma once

#include "Player.h"
#include "Gun.h"

class HUD
{
private:
	sf::Texture m_texture;
	sf::Sprite m_spriteSheet;

	//Current health and current gun level
	int m_currentHealth;
	int m_currentGunLevel;

	//Bars
	sf::IntRect m_healthBarBackground;
	sf::IntRect m_gunLevelBarBackground;
	sf::RectangleShape m_currentHealthBar;
	sf::RectangleShape m_currentGunLevelBar;
	float m_maxBarWidth;
	float m_barHeight;

	//Numbers
	sf::IntRect m_healthNumber;
	sf::IntRect m_gunLevelNumber;

	//Text
	sf::IntRect m_textLV;

	//Element's positions
	//Bars
	sf::Vector2f m_healthBarBackgroundPos;
	sf::Vector2f m_gunLevelBarBackgroundPos;

	//Numbers
	sf::Vector2f m_healthNumberPos;
	sf::Vector2f m_gunLevelNumberPos;

	//Text
	sf::Vector2f m_textLVPos;

	void initSprite();
	void initBars();
	void initNumbers();
	void initText();
	void initPositions();

	void updateCurrentBars(Player& player, Gun& gun);
	void updateText();
public:
	HUD();

	void update(Player& player, Gun& gun);
	void render(sf::RenderTarget* target);
};