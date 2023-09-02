#include "stdafx.h"
#include "AnimatedTiles.h"
#define MAXLEVEL1HEALTH 6

void AnimatedTiles::initSprite()
{
	if (!m_animatedTilesTexture.loadFromFile("Textures/Animated Tiles/NpcSym.bmp"))
		std::cout << "ERROR::ANIMATEDTILES::INITSPRITE::FAILED TO LOAD TEXTURE" << '\n';
	m_animatedTilesSpriteSheet.setTexture(m_animatedTilesTexture);
	m_animatedTilesSpriteSheet.setScale(2.f, 2.f);
}

//Define static member variables outside the class (IntRect for animation)
sf::IntRect AnimatedTiles::m_healthFillUpStation = sf::IntRect(288, 0, 16, 16);
sf::IntRect AnimatedTiles::m_saveDisk = sf::IntRect(96, 16, 16, 16);
sf::IntRect AnimatedTiles::m_increaseMaxHealth = sf::IntRect(32, 96, 16, 16);

void AnimatedTiles::initAnimationVariables()
{
	m_healthFillUpStationPosition = sf::Vector2f(560.f, 280.f);
	m_saveDiskPosition = sf::Vector2f(600.f, 280.f);
	m_increaseMaxHealthPosition = sf::Vector2f(440.f, 120.f);

	m_animationTimer.restart();
}

AnimatedTiles::AnimatedTiles()
{
	initSprite();
	initAnimationVariables();
}

void AnimatedTiles::updateAnimatedTiles()
{
	if (m_animationTimer.getElapsedTime().asSeconds() > 0.1f)
	{
		m_healthFillUpStation.left += 16.f;
		if (m_healthFillUpStation.left > 304.f)
			m_healthFillUpStation.left = 288.f;

		m_saveDisk.left += 16.f;
		if (m_saveDisk.left > 208.f)
			m_saveDisk.left = 96.f;

		m_increaseMaxHealth.left += 16.f;
		if (m_increaseMaxHealth.left > 48.f)
			m_increaseMaxHealth.left = 32.f;
		m_animationTimer.restart();
	}
}

void AnimatedTiles::renderAnimatedTiles(sf::RenderTarget* target, Player& player)
{
	//Update the animation before renderings
	updateAnimatedTiles();

	//Animate Healthfill up station
	m_animatedTilesSpriteSheet.setPosition(m_healthFillUpStationPosition);
	m_animatedTilesSpriteSheet.setTextureRect(m_healthFillUpStation);
	target->draw(m_animatedTilesSpriteSheet);

	//Animate Savedisk 
	m_animatedTilesSpriteSheet.setPosition(m_saveDiskPosition);
	m_animatedTilesSpriteSheet.setTextureRect(m_saveDisk);
	target->draw(m_animatedTilesSpriteSheet);

	//Animate Increase Max health
	if (MAXLEVEL1HEALTH != player.getHealth().second)
	{

		m_animatedTilesSpriteSheet.setPosition(m_increaseMaxHealthPosition);
		m_animatedTilesSpriteSheet.setTextureRect(m_increaseMaxHealth);
		target->draw(m_animatedTilesSpriteSheet);
	}
}

//Accessors
const sf::IntRect& AnimatedTiles::getHealthFillUpStation()
{
	return m_healthFillUpStation;
}

const sf::IntRect& AnimatedTiles::getIncreaseMaxHealth() 
{
	return m_increaseMaxHealth;
}

const sf::IntRect& AnimatedTiles::getSaveDisk() 
{
	return m_saveDisk;
}