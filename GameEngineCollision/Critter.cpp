#include "stdafx.h"
#include "Critter.h"

void Critter::initHitbox()
{
	m_hitbox.left = 0.f;
	m_hitbox.top = 0.f;
	m_hitbox.width = 24.f;
	m_hitbox.height = 32.f;
}

void Critter::initHealth()
{
	m_currentHealth = 2;
}

void Critter::initOrientation()
{
	m_facingRight = false;
}

void Critter::initPhysics()
{
	m_gravity = 0.5f;
}

Critter::Critter()
{
	initHitbox();
	initHealth();
	initOrientation();
	initPhysics();
}

void Critter::setPosition(const int x, const int y)
{
	m_hitbox.left = x;
	m_hitbox.top  = y;
}

const int& Critter::updateHealth(const int healthPoints)
{
	//Updates health and returns new health points
	m_currentHealth += healthPoints;
	return m_currentHealth;
}

//Functions
void Critter::updateOrientation(Player& player)
{
	if (player.getPosition().x > m_hitbox.left)
		m_facingRight = true;
	else
		m_facingRight = false;
}

void Critter::updateMovement(Player& player)
{
	m_critterState = CritterState::IDLE; //IDLE state by default
	float distanceWithPlayerX = std::abs(player.getPosition().x - m_hitbox.getPosition().x);
	float distanceWithPlayerY = std::abs(player.getPosition().y - m_hitbox.getPosition().y);
	float euclideanDistance = std::sqrt((distanceWithPlayerX * distanceWithPlayerX) + (distanceWithPlayerY * distanceWithPlayerY));

	if (euclideanDistance < 150 && euclideanDistance > 110)
	{
		m_critterState = CritterState::NOTICING; //NOTICING if distance is between 30 and 50 pixels
	}
	else if(euclideanDistance < 110)
	{
		m_critterState = CritterState::JUMPING;  //JUMPING if distance is less than 30
		//Give velocity in x direction until the condition in not false

			if (!m_jumping)
			{
				if (m_movementTimer.getElapsedTime().asSeconds() >= 2.f)
				{
					m_velocity.y = -8.f;
					m_jumping = true;
					m_lockjump = true;
					m_movementTimer.restart();
				}
			}
			if (m_facingRight)
				m_velocity.x = 0.8f;
			else
				m_velocity.x = -0.8f;
			if (m_velocity.y >= 0 && !m_jumping)
				m_velocity.x = 0;
	}
	if (m_critterState == CritterState::IDLE)
		m_velocity.x = 0;
}

void Critter::updatePlayerEnemyCollision(Player& player)
{
	if (m_hitbox.intersects(player.getHitbox()) && !player.isRevivalStateActive())
	{
		player.updateHP(-1);
		player.setRevivalState(true);
	}
}

void Critter::updateCritterWallCollision()
{
	//Check for slopes (only if moving down) 
	if (m_velocity.y > 0)
	{
		int tsx, tsy;				//Slope tile coordinates

		//Hitbox's bottom-horizontal side's middle point
		//Case 1: Critter enters a slope
		int sx = m_hitbox.left + (m_hitbox.width / 2) + m_velocity.x;

		//Check collision of above mentioned point with the sloped tile (if present)
		if (collisionSlope(m_hitbox, sx, (m_hitbox.top + m_hitbox.height), tsx, tsy))
		{
			m_hitbox.left += m_velocity.x;
			//Y has already been set by collisionSlope function

			unlockJump();			//Critter hits the ground therefore the critter may jump again

			m_velocity.y = 1;		//Test against the ground again in the next frame 
			//(We only check for slope if velocity.y is > 0)
			m_prevTileX = tsx;
			m_prevTileY = tsy;		//Save tile coordinates

			return;
		}
		else
		{
			//Critter is not on a slope in this frame, now check if the critter came from a slope
			//-1 ... Critter is not on a slope
			//0  ... Critter left the slope after moving down
			//1  ... Critter left the slope after moving up
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
				//Case 2: Critter left the slope
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

					/*Test one tile lower than the bottom of the slope,
					it's physically incorrect, but looks a lot smoother in game*/
					sy = m_hitbox.top + m_hitbox.height + TILESIZE;

				}

				//Case 3: Critter again landed on slope after leaving a slope
				if (collisionSlope(m_hitbox, sx, sy, tsx, tsy))
				{
					m_hitbox.left += m_velocity.x;

					unlockJump();

					m_velocity.y = 1;

					m_prevTileX = tsx;
					m_prevTileY = tsy;

					return;
				}
			}
		}
	}


	//No slope collisions detected hence check for normal tile collisions

	/*
	* The idea is to split our evaluation process to x-axis, y-axis
	* We evaluate the collison on x-axis first, reset the position on x-axis if critter collides with wall
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
			unlockJump();
		}
		else
		{	//Falling (in air)
			m_hitbox.top += m_velocity.y;									  //No collision
			m_velocity.y += m_gravity;
			m_lockjump = true;												  //Lock jump (since falling)
		}
	}

	m_prevTileX = (m_hitbox.left + (m_hitbox.width / 2)) / TILESIZE;
	m_prevTileY = (m_hitbox.top + m_hitbox.height) / TILESIZE;
}


void Critter::unlockJump()
{
	m_lockjump = false;
	m_jumping = false;
}

//Accessors
const sf::FloatRect& Critter::getBounds() const
{
	return m_hitbox;
}

void Critter::update(Player& player)
{
	updateOrientation(player);
	updateMovement(player);
	updatePlayerEnemyCollision(player);
	updateCritterWallCollision();
	updateCritterAnimation(m_facingRight);
}

void Critter::render(sf::RenderTarget* target)
{
	renderCritterAnimation(target, m_hitbox);
}