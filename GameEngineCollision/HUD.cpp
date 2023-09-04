#include "stdafx.h"
#include "HUD.h"

void HUD::initSprite()
{
	/* Initializes texture and spritesheet for HUD */

	if (!m_texture.loadFromFile("Textures/Textbox/TextBox.bmp"))
		std::cout << "ERROR::HUD::INITSPRITE::FAILED TO LOAD SPRITE" << '\n';
	m_spriteSheet.setTexture(m_texture);
	m_spriteSheet.setScale(2.f, 2.f);
}

void HUD::initBars()
{
	/* Initializes texture rectangle of:
	*  Health bar background 
	*  Current health bar
	*  Gun level points background
	*  Current gun level points
	*/

	//Initiating gun and health bar
	m_healthBarBackground = sf::IntRect(0, 40, 64, 8);
	m_gunLevelBarBackground = sf::IntRect(0, 72, 40, 8);

	//Health's bar
	m_currentHealthBar.setSize(sf::Vector2f(m_maxBarWidth, m_barHeight));
	m_currentHealthBar.setFillColor(sf::Color::Red);

	//Gun's level bar
	m_currentGunLevelBar.setSize(sf::Vector2f(m_maxBarWidth, m_barHeight));
	m_currentGunLevelBar.setFillColor(sf::Color::Yellow);

	//Height and width of current bar (health and gun level)
	m_maxBarWidth = 78.f;
	m_barHeight = 10.f;
}

void HUD::initNumbers()
{
	/* Initializes texture rectangle of:
	*  Health number    (current health)
	*  Gun level number (current gun level)
	*/

	//Health number
	m_healthNumber.top = 56;
	m_healthNumber.width = 8;
	m_healthNumber.height = 8;

	//Gun Level in number
	m_gunLevelNumber.top = 56;
	m_gunLevelNumber.width = 8;
	m_gunLevelNumber.height = 8;
}

void HUD::initText()
{
	/* Initialize text LV's texture rectangle */

	m_textLV.left = 80;
	m_textLV.top = 80;
	m_textLV.width = 12;
	m_textLV.height = 8;
}

void HUD::initPositions()
{
	/* Sets position of:
	* 
	*  Health bar background
	*  Current health bar
	*  Gun level bar background
	*  Current gun level bar
	*  
	*  Health number (current health)
	*  Gun level number (current gun level)
	* 
	*  Plain LV text 
	*/
	
	//Bars
	m_gunLevelBarBackgroundPos = sf::Vector2f(68.f, 20.f);
	m_currentGunLevelBar.setPosition(sf::Vector2f(68.f, 22.f));

	m_healthBarBackgroundPos   = sf::Vector2f(20.f, 36.f);
	m_currentHealthBar.setPosition(sf::Vector2f(68.f, 38.f));

	//Numbers
	m_healthNumberPos   = sf::Vector2f(50.f, 36.f);
	m_gunLevelNumberPos = sf::Vector2f(50.f, 20.f);

	//Text
	m_textLVPos         = sf::Vector2f(20.f, 20.f);
}
HUD::HUD()
{
	initSprite();
	initBars();
	initNumbers();
	initText();
	initPositions();
}

void HUD::updateCurrentBars(Player& player, Gun& gun)
{
	/* Updates current Health Bar
	*  Updates current Gun Level Bar
	*/
	auto [currHealth, maxHealth] = player.getHealth();
	float width = (static_cast<float>(currHealth) / maxHealth) * m_maxBarWidth;
	m_currentHealthBar.setSize(sf::Vector2f(width, m_barHeight));
	m_currentHealth = currHealth;

	auto [currGunLevelPoints, currGunLevel] = gun.getGunLevelInfo();
	width = (static_cast<float>(currGunLevelPoints) / 5) * m_maxBarWidth;
	m_currentGunLevelBar.setSize(sf::Vector2f(width, m_barHeight));
	m_currentGunLevel = currGunLevel;
}

void HUD::updateText()
{
	/* Updates x co-ordinate of m_healthNumber texture rectangle in spritesheet
	*  Updates x co-ordinate of m_gunLevelNumber texture rectangle in spritesheet
	*/

	m_healthNumber.left = m_currentHealth * 8;
	m_gunLevelNumber.left = m_currentGunLevel * 8;
}

void HUD::update(Player& player, Gun& gun)
{
	/* Updates bars, numbers, text */
	updateCurrentBars(player, gun);
	updateText();
}

void HUD::render(sf::RenderTarget* target)
{
	/* Renders bars, numbers, text */

	//Renders gun level bar background and current gun level bar
	m_spriteSheet.setPosition(m_gunLevelBarBackgroundPos);
	m_spriteSheet.setTextureRect(m_gunLevelBarBackground);
	target->draw(m_spriteSheet);
	target->draw(m_currentGunLevelBar);

	//Renders gun LV text
	m_spriteSheet.setPosition(m_textLVPos);
	m_spriteSheet.setTextureRect(m_textLV);
	target->draw(m_spriteSheet);

	//Renders gun level number
	m_spriteSheet.setPosition(m_gunLevelNumberPos);
	m_spriteSheet.setTextureRect(m_gunLevelNumber);
	target->draw(m_spriteSheet);

	//Renders health bar background and current health bar
	m_spriteSheet.setPosition(m_healthBarBackgroundPos);
	m_spriteSheet.setTextureRect(m_healthBarBackground); 
	target->draw(m_spriteSheet);
	target->draw(m_currentHealthBar);

	//Renders health number
	m_spriteSheet.setPosition(m_healthNumberPos);
	m_spriteSheet.setTextureRect(m_healthNumber);
	target->draw(m_spriteSheet);
}