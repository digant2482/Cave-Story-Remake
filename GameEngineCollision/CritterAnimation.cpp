#include "stdafx.h"
#include "CritterAnimation.h"

//Initializers
void CritterAnimation::initSprite()
{
	/* Loads texture and sets texture to the spritesheet */
	if (!m_textureSheet.loadFromFile("Textures/Enemies/Enemies Sprite.png"))
		std::cout << "ERROR::ENEMIES::CRITTER::INITSPRITE::FAILED TO LOAD TEXTURE" << '\n';
	m_spriteSheet.setTexture(m_textureSheet);
	m_spriteSheet.setScale(2.0f, 2.0f);
}

void CritterAnimation::initVariables()
{
	/* Initializes critter's state and resets animation timer */
	m_critterState = CritterState::IDLE;
	m_animationTimer.restart();
}

void CritterAnimation::initStates()
{
	/* Assigns texture rectangle's dimensions and co-ordinates */
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
	/* Sets current frame (texture rectangle to be snipped from spritesheet) */
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
	/* Render the critter animation using its current frame and position */
	m_spriteSheet.setPosition(critterHitbox.left + 6.f, critterHitbox.top);
	m_spriteSheet.setTextureRect(m_currentFrame);
	target->draw(m_spriteSheet);
}