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
		//check for slopes (only if moving down) 
	if (m_velocity.y > 0) 
	{
		int tsx, tsy;				//slope tile coordinates

		//Hitbox's bottom-horizontal side's middle point
		//Case 1: Player Enter a slope
		int sx = m_hitbox.left + (m_hitbox.width / 2) + m_velocity.x;
		
		//Check collision of above mentioned point with the sloped tile (if present)
		if (collisionSlope(m_hitbox, sx, (m_hitbox.top + m_hitbox.height), tsx, tsy))
		{
			m_hitbox.left += m_velocity.x;	
			//y has been set by collisionSlope function

			unlockJump();	//we hit the ground - the player may jump again
			 
			m_velocity.y = 1;		//test against the ground again in the next frame (We only check for slope if velocity.y is > 0)

			m_prevTileX = tsx;	//save slope coordinate
			m_prevTileY = tsy;

			return;
		}
		else 
		{	
			//player is not on a slope in this frame, now check if we came from a slope
			//-1 ... we are not on a slope
			//0  ... we left a slope after moving down
			//1  ... we left a slope after moving up
			int stateCode = -1;

			if (Tilemap::map(m_prevTileX, m_prevTileY) == LEFTSLOPED)
			{
				if (m_velocity.x > 0)
					stateCode = 0;  //moving down the slope
				else
					stateCode = 1;	//moving up the slope
			}
			else if (Tilemap::map(m_prevTileX, m_prevTileY) == RIGHTSLOPED)
			{
				if (m_velocity.x < 0)	
					stateCode = 0;  //moving down the slope
				else
					stateCode = 1;	//moving up the slope
			}

			if (stateCode != -1) 
			{
				//Case 2: Player left the slope
				int sy;

				if (stateCode == 1) 
				{
					m_hitbox.top = tsy * TILESIZE - m_hitbox.height - 1;		//move y to the top of slope tile
					sy = m_hitbox.top + m_hitbox.height;
				}
				else 
				{
					m_hitbox.top = (tsy + 1) * TILESIZE - m_hitbox.height - 1;	//move y to the bottom of the slope tile
					sy = m_hitbox.top + m_hitbox.height + TILESIZE;			//test one tile lower than the bottom of the slope (to test if we move down a long slope)
					//it's physically incorrect, but looks a lot smoother ingame
				}

				//Case 3: Player again landed on slope after he had left a slope
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


	//No slope collisions detected -> check for normal tile collisions
	
	/*
	* The idea is to split our evaluation process to x-axis, y-axis
	* We evaluate the collison on x-axis first, reset the position on x-axis if player collides with wall
	* Then we do the same process but on y-axis 
	*/
	int tileCoord;

	//x axis collision (--)
	if (m_velocity.x > 0) 
	{	//moving right
		if (verticalCollision(m_hitbox, m_hitbox.left + m_hitbox.width + m_velocity.x, m_hitbox.top, tileCoord)) //collision on the right side
			m_hitbox.left = tileCoord * TILESIZE - m_hitbox.width - 1;		//move to the edge of the tile (tile on the right - player width)
		else
			m_hitbox.left += m_velocity.x; //No collision
	}
	else if (m_velocity.x < 0)
	{	//moving left
		if (verticalCollision(m_hitbox, m_hitbox.left + m_velocity.x, m_hitbox.top, tileCoord))		//collision on the left side
			m_hitbox.left = (tileCoord + 1) * TILESIZE + 1;									//move to the edge of the tile
		else
			m_hitbox.left += m_velocity.x;
	}
	

	// y axis collision (|)
	if (m_velocity.y < 0)
	{	//moving up
		if (collisionHorizontalUp(m_hitbox, m_hitbox.left, m_hitbox.top + m_velocity.y, tileCoord))
		{
			m_hitbox.top = (tileCoord + 1) * TILESIZE + 1;
			m_velocity.y = 0;
		}
		else 
		{
			m_hitbox.top += m_velocity.y;
			m_velocity.y += m_gravity;
		}
	}
	else 
	{	
		//moving down / on ground
		if (collisionHorizontalDown(m_hitbox, m_hitbox.left, m_hitbox.top + m_hitbox.height + m_velocity.y, tileCoord))
		{	//on ground
			m_hitbox.top = tileCoord * TILESIZE - m_hitbox.height - 1;
			m_velocity.y = 1;				//1 so we test against the ground again in the next frame (0 would test against the ground in the next+1 frame)

			unlockJump();
		}
		else 
		{	//falling (in air)
			m_hitbox.top += m_velocity.y;
			m_velocity.y += m_gravity;

			m_lockjump = true;			        //lock jump if falling
		}
	}

	m_prevTileX = (m_hitbox.left + (m_hitbox.width/2)) / TILESIZE;
	m_prevTileY = (m_hitbox.top + m_hitbox.height) / TILESIZE;
}

void Critter::unlockJump()
{
	//the player may jump again:
	//a) if he fell off an edge (!jumping) - without releasing the jump key on the ground
	//b) if he jumped - only when he releases the jump key on the ground	

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