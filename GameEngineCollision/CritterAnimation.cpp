#include "stdafx.h"
#include "CritterAnimation.h"

//Initializers
void CritterAnimation::initSprite()
{
	if (!m_textureSheet.loadFromFile("Textures/Enemies/Enemies Sprite.png"))
		std::cout << "ERROR::ENEMIES::CRITTER::INITSPRITE::FAILED TO LOAD TEXTURE" << '\n';
	m_sprite.setTexture(m_textureSheet);
	m_sprite.setScale(2.0f, 2.0f);
}

void CritterAnimation::initVariables()
{
	m_critterState = CritterState::IDLE;
	m_animationTimer.restart();
}

void CritterAnimation::initStates()
{
	m_idleRightTexture      = sf::IntRect(319, 191, 16, 16);
	m_idleLeftTexture       = sf::IntRect(319, 175, 16, 16);
	m_noticingRightTexture  = sf::IntRect(335, 191, 16, 16);
	m_noticingLeftTexture   = sf::IntRect(335, 175, 16, 16);
	m_jumpingRightTexture   = sf::IntRect(351, 191, 16, 16);
	m_jumpingLeftTexture    = sf::IntRect(351, 175, 16, 16);
}

//Constructor
CritterAnimation::CritterAnimation()
{
	initSprite();
	initVariables();
	initStates();
}

//Functions
void CritterAnimation::updateCritterAnimation(bool& facingRight)
{
	if (m_animationTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		if (m_critterState == CritterState::IDLE)
		{
			if (facingRight)
				m_currentFrame = m_idleRightTexture;
			else
				m_currentFrame = m_idleLeftTexture;
		}
		else if (m_critterState == CritterState::NOTICING)
		{
			if (facingRight)
				m_currentFrame = m_noticingRightTexture;
			else
				m_currentFrame = m_noticingLeftTexture;
		}
		else if (m_critterState == CritterState::JUMPING)
		{			
			if (facingRight)
				m_currentFrame = m_jumpingRightTexture;
			else
				m_currentFrame = m_jumpingLeftTexture;
		}
		m_animationTimer.restart();
	}
}

void CritterAnimation::renderCritterAnimation(sf::RenderTarget* target, const sf::FloatRect& critterHitbox)
{
	m_sprite.setPosition(critterHitbox.left + 6.f, critterHitbox.top);
	m_sprite.setTextureRect(m_currentFrame);
	target->draw(m_sprite);
}