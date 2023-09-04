#include "stdafx.h"
#include "PlayerAnimation.h"

//Initializers
void PlayerAnimation::initSprite()
{
	/* Initializes player sprite */
	if (!m_texture.loadFromFile("Textures/Player/Quote.png"))
		std::cout << "ERROR::PLAYER::INITSPRITE::FAILED TO LOAD TEXTURE" << '\n';
	m_spriteSheet.setTexture(m_texture);
}

void PlayerAnimation::initIntRect()
{
	/* Initializes texture rect (To be snipped from m_spriteSheet) */
	m_runRight  = sf::IntRect(0, 32, 32, 32);
	m_runLeft   = sf::IntRect(0, 0, 32, 32);
}

void PlayerAnimation::initVariables()
{
	/* Initializes :
	* Player's moving state
	* Player's facing direction (m_facingRight)
	* Player's revival state
	* Animation Timer 
	*/
	m_playerState = IDLE;
	m_facingRight = true;
	m_revivalState = false;
	m_animationTimer.restart();
}

//Constructor
PlayerAnimation::PlayerAnimation()
{
	initSprite();
	initIntRect();
	initVariables();
}

const sf::IntRect PlayerAnimation::getIdleRightTexture()
{
	/* Returns IntRect (to be snipped from spritesheet) of idle right facing player */
	return sf::IntRect(0, 32, 32, 32);
}

const sf::IntRect PlayerAnimation::getIdleLeftTexture()
{
	/* Returns IntRect of idle left facing player */
	return sf::IntRect(0, 0, 32, 32);
}

const sf::IntRect PlayerAnimation::getRunLeftTexture()
{
	/* Returns IntRect of running left facing player */
	m_runLeft.left += 32;
	if (m_runLeft.left >= 64)
		m_runLeft.left = 0;
	return m_runLeft;
}

const sf::IntRect PlayerAnimation::getRunRightTexture()
{
	/* Returns IntRect of running right facing player */
	m_runRight.left += 32;
	if (m_runRight.left >= 64)
		m_runRight.left = 0;
	return m_runRight;
}

//Modifiers
void PlayerAnimation::setRevivalState(const bool state)
{
	/* Sets player's revival state
	 * Starts the revival state timer if player is hit */

	m_revivalState = state;

	if (m_revivalState)
	{
		m_revivalStateTimer.restart();
		m_animationTimer.restart();
	}
}

//Accessors
const bool& PlayerAnimation::isFacingRight() const
{
	/* Returns player's orientation */
	return m_facingRight;
}

const bool& PlayerAnimation::isRevivalStateActive() const
{
	/* Returns player's revival state */
	return m_revivalState;
}

//Functions

void PlayerAnimation::updateRevivalState()
{
	/* Sets revival state to false after revival period (3 seconds) */
	if (m_revivalState && m_revivalStateTimer.getElapsedTime().asSeconds() >= 3.f)
		m_revivalState = false;
}

void PlayerAnimation::updatePlayerAnimation()
{
	/* Selects the currentFrame (Texture rectangle to be snipped from spritesheet) according to player's moving state 
	 * Animation timer is used to delay rendering a new state for around 0.1 seconds (to make animation smoother)
	 * When switching state, the animation timer is ignored by comparing with previous player state (again to make animation smoother)
	 */

	if (m_playerState == IDLE)
	{
		//If animation is switched from moving to idle, timer is ignored
		if (m_animationTimer.getElapsedTime().asSeconds() >= 0.2f || m_previousPlayerState != m_playerState)
		{
			//If previous state is right facing, new state should be right facing
			if (m_facingRight)
				m_currentFrame = getIdleRightTexture();
			else
				m_currentFrame = getIdleLeftTexture();
			m_animationTimer.restart();
		}
	}
	else if (m_playerState == MOVING_RIGHT)
	{
		m_facingRight = true;
		if (m_animationTimer.getElapsedTime().asSeconds() >= 0.1f || m_previousPlayerState != m_playerState)
		{
			m_currentFrame = getRunRightTexture();
			m_animationTimer.restart();
		}
	}
	else if (m_playerState == MOVING_LEFT)
	{
		m_facingRight = false;
		if (m_animationTimer.getElapsedTime().asSeconds() >= 0.1f || m_previousPlayerState != m_playerState)
		{
			m_currentFrame = getRunLeftTexture();
			m_animationTimer.restart();
		}
	}
}

void PlayerAnimation::renderPlayerAnimation(sf::RenderTarget* target, sf::FloatRect& playerHitbox)
{
	/* Renders player's sprite */
	m_spriteSheet.setPosition(playerHitbox.left - 10, playerHitbox.top);
	m_previousPlayerState = m_playerState;
	m_spriteSheet.setTextureRect(m_currentFrame);

	/* Two types of rendering:
	a) The player is not hit (Normal rendering)
	b) The player is hit    (Jittery rendering) */
	if (!m_revivalState || (m_revivalState && m_revivalAnimationTimer.getElapsedTime().asSeconds() > 0.1f))
	{
		target->draw(m_spriteSheet);
		m_revivalAnimationTimer.restart();
	}
}