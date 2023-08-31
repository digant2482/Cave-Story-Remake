#include "stdafx.h"
#include "HUD.h"

void HUD::initSprite()
{
	if (!m_texture.loadFromFile("Textures/Textbox/TextBox.bmp"))
		std::cout << "ERROR::HUD::INITSPRITE::FAILED TO LOAD SPRITE" << '\n';
	m_spriteSheet.setTexture(m_texture);
	m_spriteSheet.setScale(2.f, 2.f);
}

void HUD::initVariables()
{
	//Height and width of current bar (health and gun level)
	m_currentBarWidthMax = 78.f;
	m_currentBarHeight   = 8.f;
}

void HUD::initElements()
{
	/*
	- Set IntRect (dimension to selected from spritesheet) for health bar, gun level bar, health number
	*/
	//Initiating gun and health bar
	m_healthBarBackground = sf::IntRect(0, 40, 64, 8);
	m_gunLevelBarBackground = sf::IntRect(0, 72, 40, 8);

	//Health's bar
	m_currentHealthBar.setSize(sf::Vector2f(m_currentBarWidthMax, m_currentBarHeight));
	m_currentHealthBar.setFillColor(sf::Color::Red);

	//Gun's level bar
	m_currentGunLevelBar.setSize(sf::Vector2f(m_currentBarWidthMax, m_currentBarHeight));
	m_currentGunLevelBar.setFillColor(sf::Color::Yellow);

	//Health in number
	m_healthNumber.top = 56;
	m_healthNumber.width = 8;
	m_healthNumber.height = 8;
}

void HUD::initElementPositions()
{
	// Sets position of health bar and gun's level bar on screen
	m_gunLevelBarBackgroundPos = sf::Vector2f(68.f, 20.f);
	m_currentGunLevelBar.setPosition(sf::Vector2f(68.f, 22.f));

	m_healthBarBackgroundPos = sf::Vector2f(20.f, 36.f);
	m_currentHealthBar.setPosition(sf::Vector2f(68.f, 38.f));

	m_healthNumberPos = sf::Vector2f(50.f, 36.f);
}
HUD::HUD()
{
	initSprite();
	initVariables();
	initElements();
	initElementPositions();
}

void HUD::setCurrentBars(Player& player)
{
	/*
	- Updates current Health Bar
	- Updates current Gun Level Bar
	*/
	auto [currHealth, maxHealth] = player.getHealth();
	float width = (static_cast<float>(currHealth) / maxHealth) * m_currentBarWidthMax;
	m_currentHealthBar.setSize(sf::Vector2f(width, m_currentBarHeight));
	m_currentHealth = currHealth;
}

void HUD::setText()
{
	//Sets x co-ordinate of health number graphic in spritesheet
	m_healthNumber.left = m_currentHealth * 8;
}

void HUD::update(Player& player)
{
	setCurrentBars(player);
	setText();
}

void HUD::render(sf::RenderTarget* target)
{
	//Draws gun level bar background
	m_spriteSheet.setPosition(m_gunLevelBarBackgroundPos);
	m_spriteSheet.setTextureRect(m_gunLevelBarBackground);
	target->draw(m_spriteSheet);

	//Draws health bar background and current health bar
	m_spriteSheet.setPosition(m_healthBarBackgroundPos);
	m_spriteSheet.setTextureRect(m_healthBarBackground); 
	target->draw(m_spriteSheet);
	target->draw(m_currentHealthBar);

	//Draws health number
	m_spriteSheet.setPosition(m_healthNumberPos);
	m_spriteSheet.setTextureRect(m_healthNumber);
	target->draw(m_spriteSheet);
}