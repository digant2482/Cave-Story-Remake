#include "stdafx.h"
#include "Bat.h"
#define PI 3.14159

void Bat::initSprite()
{
	/* Initializes sprite (bat graphic) */
	if (!m_texture.loadFromFile("Textures/Enemies/Enemies Sprite.png"))
		std::cout << "ERROR::ENEMY::BAT::INITSPRITE::SPRITE NOT LOADED" << '\n';
	m_spriteSheet.setTexture(m_texture);
	m_spriteSheet.setScale(2.f, 2.f);
}

void Bat::initOrientation()
{
	/* Sets bat's orientation */
	m_facingRight = false;
}

void Bat::initAnimation()
{
	/* Initializes:
	* Current Frame (Rectangle box to be snipped from spritesheet)
	* Cuts first graphic from spritesheet using current frame
	* Restarts animation timer
	*/

	m_currentFrame = sf::IntRect(351, 207, 16, 16);
	m_spriteSheet.setTextureRect(m_currentFrame);
	m_animationTimer.restart();
}

Bat::Bat(const float x, const float y)
{
	/* Sets initial position for bat (Used as reference point for bat's motion)
	*  Calls initializing functions	
	*/
	m_initialPos = sf::Vector2f(x, y);
	m_spriteSheet.setPosition(m_initialPos);
	initSprite();
	initOrientation();
	initAnimation();
}

//Functions
void Bat::updateOrientation(Player& player)
{
	/* Sets bat's orientation acc. to the position of player */
	if (player.getPosition().x > m_spriteSheet.getGlobalBounds().left)
		m_facingRight = true;
	else
		m_facingRight = false;
}

void Bat::updateMovement()
{
	/* Utilizes simple harmonic motion (SHM) for bat's movement
	*  @param theta is the angle for SHM
	*/
	static float theta = 0;
	theta += PI / 60.f;
	if (theta >= 2*PI)
		theta = 0.f;
;	m_spriteSheet.setPosition(m_initialPos.x, m_initialPos.y + 30 * std::cos(theta));
}

void Bat::updatePlayerEnemyCollision(Player& player)
{
	/* Checks player's collision with enemy
	*  Decreases player's health in the event of collision
	*  Activates player's revival state
	*/
	if (m_spriteSheet.getGlobalBounds().intersects(player.getHitbox()) && !player.isRevivalStateActive())
	{
		player.updateHP(-1);
		player.setRevivalState(true);
	}
}

void Bat::updateAnimation()
{
	/* Updates animation after every 0.2 seconds 
	*  Sets texture rect (Snipped rectangle from whole sheet) 
	*/
	if (m_animationTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		if (m_facingRight)
			m_currentFrame.top = 223;
		else
			m_currentFrame.top = 207;

		m_currentFrame.left += 16;
		if (m_currentFrame.left > 383)
			m_currentFrame.left -= 48;
		m_spriteSheet.setTextureRect(m_currentFrame);
		m_animationTimer.restart();
	}
}

//Accessors
const sf::FloatRect Bat::getBounds() const
{
	/* Returns global bounds (Rectangle bounding bat's sprite) of bat's sprite */
	return m_spriteSheet.getGlobalBounds();
}

void Bat::update(Player& player)
{
	/* Updates bat's orientation (left or right)
	*  Updates bat's movement (Simple Harmonic Motion around initial position)
	*  Updates player enemy collision (checks collision, updates player health and revival state)
	*  Updates animation (sets bat's graphic according to bat's orientation)
	*/
	updateOrientation(player);
	updateMovement();
	updatePlayerEnemyCollision(player);
	updateAnimation();
}

void Bat::render(sf::RenderTarget* target)
{
	/* Renders bat */
	target->draw(m_spriteSheet);
}