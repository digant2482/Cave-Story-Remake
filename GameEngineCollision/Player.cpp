#include "stdafx.h"
#include "Player.h"
#define JUMPVELOCITY -8.5f

//Initializers
void Player::initHitbox()
{
	/* Player's hitbox (used for player's collision) 
	*  Hitbox's height and width are set using trial and error
	*/
	m_hitbox.left = 0;
	m_hitbox.top = 0;
	m_hitbox.width = 12;
	m_hitbox.height = 32;
}

void Player::initHealth()
{
	m_maxHealth = 3;				//Player's max health
	m_currentHealth = m_maxHealth;  //Player's health
	m_revivalState = false;	     	//Player's revival state
}

void Player::initPhysics()
{							
	m_velocityMaxX = 1;				//Terminal velocity in x direction	
	m_velocityMaxY = 8.5f;			//Terminal velocity in y direction
	m_velocityMin = 1;				//Player stops if velocity falls below this value
	m_acceleration = 2;				//Acceleration in x direction
	m_drag = 0.7f;					//Deceleration in x direction
	m_gravity = 0.3f;				//Gravity
}

void Player::initVariables()
{
	m_lockjump = false;             //Denies the player to jump
	m_jumping = false;				//Is player jumping ?
}

Player::Player()
{
	initHitbox();
	initHealth();
	initPhysics();
	initVariables();
}

//Modifiers
void Player::setPosition(int x, int y)
{
	/* Updates player's position */
	m_hitbox.left = x;
	m_hitbox.top = y;
}

void Player::updateHP(const int x)
{
	//Health should not go below zero (It will be automatically adjusted when the player exits game at zero health)
	if (m_currentHealth)
		m_currentHealth += x;
}

void Player::setHealth(const int x, const int y)
{
	/* Sets current health and max health 
	*  Used to restore progress when loading a saved game
	*/
	m_currentHealth = x;
	m_maxHealth = y;
}

//Accessors
const sf::Vector2f& Player::getPosition() const
{
	/* Returns player's position */
	return sf::Vector2f(m_hitbox.left, m_hitbox.top);
}

const std::pair<int, int> Player::getHealth() const
{
	/* Returns player's health */
	return std::make_pair(m_currentHealth, m_maxHealth);
}

const sf::FloatRect& Player::getHitbox() const
{
	/* Returns player's hitbox */
	return m_hitbox;
}

//Functions
void Player::updateMapCollision()
{
	/* The function checks for slope collision first
	*  If slope collision is not detected, the function checks normal tile collision
	*/



	//Check for slopes (only if moving down) 
	if (m_velocity.y > 0) 
	{
		int tsx, tsy;				//Slope tile coordinates

		//Hitbox's bottom-horizontal side's middle point
		//Case 1: Player enters a slope
		int sx = m_hitbox.left + (m_hitbox.width/2) + m_velocity.x;	
		
		//Check collision of above mentioned point with the sloped tile (if present)
		if (collisionSlope(m_hitbox, sx, (m_hitbox.top + m_hitbox.height), tsx, tsy))
		{
			m_hitbox.left += m_velocity.x;	
			//Y has already been set by collisionSlope function

			unlockjump();			//Player hits the ground therefore the player may jump again
			 
			m_velocity.y = 1;		//Test against the ground again in the next frame 
									//(We only check for slope if velocity.y is > 0)
			m_prevTileX = tsx;	     
			m_prevTileY = tsy;		//Save tile coordinates

			return;
		}
		else 
		{	
			//Player is not on a slope in this frame, now check if the player came from a slope
			//-1 ... Player is not on a slope
			//0  ... Player left the slope after moving down
			//1  ... Player left the slope after moving up
			int stateCode = -1;

			if (Tilemap::map(m_prevTileX, m_prevTileY) == LEFTSLOPED)
			{
				if (m_velocity.x > 0)
					stateCode = 0;  //Moving down the slope
				else
					stateCode = 1;	//Moving up the slope
			}
			else if (Tilemap::map(m_prevTileX, m_prevTileY) == RIGHTSLOPED)
			{
				if (m_velocity.x < 0)	
					stateCode = 0;  //Moving down the slope
				else
					stateCode = 1;	//Moving up the slope
			}

			if (stateCode != -1) 
			{
				//Case 2: Player left the slope
				int sy;

				if (stateCode == 1) 
				{
					//Move y to the top of slope tile
					m_hitbox.top = tsy * TILESIZE - m_hitbox.height - 1;		
					sy = m_hitbox.top + m_hitbox.height;
				}
				else 
				{
					//Move y to the bottom of the slope tile
					m_hitbox.top = (tsy + 1) * TILESIZE - m_hitbox.height - 1;	

					/* Test one tile lower than the bottom of the slope,
					it's physically incorrect, but looks a lot smoother in game */
					sy = m_hitbox.top + m_hitbox.height + TILESIZE;			

				}

				//Case 3: Player again landed on slope after leaving a slope
				if (collisionSlope(m_hitbox, sx, sy, tsx, tsy)) 
				{
					m_hitbox.left += m_velocity.x;

					unlockjump();

					m_velocity.y = 1;

					m_prevTileX = tsx;
					m_prevTileY = tsy;

					return;
				}
			}
		}
	}


	/* No slope collisions detected hence check for normal tile collisions */

	/*
	* The idea is to split our evaluation process to x-axis, y-axis
	* We evaluate the collison on x-axis first, reset the position on x-axis if player collides with wall
	* Then we do the same process on y-axis 
	*/

	int tileCoord;   //Co-ordinate of colliding tile (could be x or y co-ordinate depending on axis)

	//X axis collision (--)
	if (m_velocity.x > 0) 
	{	//Moving right (Collision on the right side)
		if (verticalCollision(m_hitbox, m_hitbox.left + m_hitbox.width + m_velocity.x, m_hitbox.top, tileCoord))	
			m_hitbox.left = tileCoord * TILESIZE - m_hitbox.width - 1;        //Move to the edge of the tile 
		else
			m_hitbox.left += m_velocity.x;									  //No collision
	}
	else if (m_velocity.x < 0)
	{	//Moving left (Collision on the left side)
		if (verticalCollision(m_hitbox, m_hitbox.left + m_velocity.x, m_hitbox.top, tileCoord))		
			m_hitbox.left = (tileCoord + 1) * TILESIZE + 1;					  //Move to the edge of the tile
		else
			m_hitbox.left += m_velocity.x;									  //No collision
	}

	//Y axis collision (|)
	if (m_velocity.y < 0)
	{	//Moving up
		if (collisionHorizontalUp(m_hitbox, m_hitbox.left, m_hitbox.top + m_velocity.y, tileCoord))
		{
			m_hitbox.top = (tileCoord + 1) * TILESIZE + 1;					  //Move to the edge of the tile
			m_velocity.y = 0;
		}
		else 
		{
			m_hitbox.top += m_velocity.y;									  //No collision
			m_velocity.y += m_gravity;
		}
	}
	else 
	{	
		//Moving down / On ground
		if (collisionHorizontalDown(m_hitbox, m_hitbox.left, m_hitbox.top + m_hitbox.height + m_velocity.y, tileCoord))
		{	//On ground
			m_hitbox.top = tileCoord * TILESIZE - m_hitbox.height - 1;
			m_velocity.y = 1;					//Velocity is set to 1, to test against the ground in the next frame 
												//0 would test against the ground in next to next frame
			unlockjump();
		}
		else 
		{	//Falling (in air)
			m_hitbox.top += m_velocity.y;									  //No collision
			m_velocity.y += m_gravity;
			m_lockjump = true;												  //Lock jump (since falling)
		}
	}

	m_prevTileX = (m_hitbox.left + (m_hitbox.width/2)) / TILESIZE;
	m_prevTileY = (m_hitbox.top + m_hitbox.height) / TILESIZE;
}

void Player::unlockjump() 
{
	/* The player may jump again:
	a) If the player fell off an edge (!jumping) and (W) -> jump key is not pressed and hits the ground
	b) If the player jumped and the player releases the jump key on the ground */

	if (!m_jumping || !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_lockjump = false;
		m_jumping = false;
	}
}

void Player::movePlayerBy(sf::Vector2f& velocity)
{
	/* Moves player by it's velocity in x and y direction */

	m_hitbox.left += velocity.x;
	m_hitbox.top += velocity.y;
}

void Player::updateMovement()
{
	/* Moves player based on user input (W, A, D keys) */

	m_playerState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x -= m_acceleration;
		m_playerState = MOVING_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x += m_acceleration;
		m_playerState = MOVING_RIGHT;
	}

	/* Jump if jump is allowed and the player presses the jump key(W) */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_lockjump)
	{
		m_velocity.y = JUMPVELOCITY;
		m_lockjump = true;   //Player not allowed to jump
		m_jumping = true;
	}
}

void Player::updatePhysics()
{
	/* Limit velocity, apply drag, and stop the player if min velocity is reached */

	if (std::abs(m_velocity.x) >= m_velocityMaxX)
		m_velocity.x = m_velocityMaxX * ((m_velocity.x < 0) ? -1 : 1);

	if (std::abs(m_velocity.y) >= m_velocityMaxY)
		m_velocity.y = m_velocityMaxY * ((m_velocity.y < 0) ? -1 : 1);

	m_velocity.x *= m_drag;

	if (std::abs(m_velocity.x) <= m_velocityMin)
		m_velocity.x = 0;
}

void Player::updateMiscellaneousItems()
{
	/* Check interactions with health fill up station, increase max health widget */

	if (Tilemap::getHealthFillUpStationTileBounds().intersects(m_hitbox))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_currentHealth = m_maxHealth;
		}
	}

	if (Tilemap::getIncreaseMaxHealthTileBounds().intersects(m_hitbox))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (m_maxHealth < 6)
			{
				m_maxHealth += 3;
				m_currentHealth += 3;
			}
		}
	}
}

void Player::update()
{
	/*
	* Updates player's movement (takes input from keyboard)
	* Updates player's collision with the tiles (sets player's position according to collision algorithm)
	* Updates player's revival state (if player is hit by enemy, player cannot be hit again while in revival state)
	* Updates player's animation (adjusts player's animation according to player's hitbox)
	* Updates player's physics (updates player velocity)
	* Updates player's interaction with health fill up station, save progress, increase max health
	*/

	updateMovement();
	updateMapCollision();
	updateRevivalState();
	updatePlayerAnimation();
	updatePhysics();
	updateMiscellaneousItems();
}

void Player::render(sf::RenderTarget* target)
{
	/* Renders Player */
	renderPlayerAnimation(target, m_hitbox);
}