#include "stdafx.h"
#include "Player.h"
#include "Tilemap.h"

#define TILESIZE 40 //Size of tile in pixels

//Initializers
void Player::initHitbox()
{
	m_hitbox.left = 10;
	m_hitbox.top = 0;
	m_hitbox.width = 12;
	m_hitbox.height = 32;
}
void Player::initPhysics()
{
	m_velocityMaxX = 1;
	m_velocityMaxY = 7;
	m_velocityMin = 1;
	m_acceleration = 2;
	m_drag = 0.7f;
	m_gravity = 0.3f;
}

void Player::initVariables()
{
	m_lockjump = false;
	m_jumping = false;
}


Player::Player()
{
	initHitbox();
	initPhysics();
	initVariables();
}

Player::Player(int x, int y)
{
	m_hitbox.left = x;
	m_hitbox.top = y;
	initHitbox();
	initPhysics();
	initVariables();
}

void Player::setPosition(int x, int y)
{
	m_hitbox.left = x;
	m_hitbox.top = y;
}

const sf::Vector2i Player::getPosition()
{
	return sf::Vector2i(m_hitbox.left, m_hitbox.top);
}

//New Functions

bool Player::verticalCollision(int x, int y, int& tileCoordX) 
{
	/*
	* Checks collision on x-axis
	* Updates the co-ordinate of tile (which is colliding with player)
	*/

	//Find y co-ordinate of colliding tile (in pixels)
	int tileYpixels = y - (y % TILESIZE);
	int testEnd = y + m_hitbox.height;

	tileCoordX = x / TILESIZE;

	int tileCoordY = tileYpixels / TILESIZE;

	while (tileYpixels <= testEnd) 
	{
		if (Tilemap::map(tileCoordX, tileCoordY) == SOLID)
			return true;
		if (m_velocity.y < 0 && Tilemap::map(tileCoordX, tileCoordY) != NONSOLID)
			if (Tilemap::map(m_slopePrevTileX, m_slopePrevTileY) == NONSOLID)
					return true;

		tileCoordY++;
		tileYpixels += TILESIZE;
	}

	return false;
}

bool Player::collisionHorizontalUp(int x, int y, int& tileCoordY)
{
	int tileXpixels = x - (x % TILESIZE);    //calculate the x position (pixels) of the tiles we check against
	int testEnd = x + m_hitbox.width;		 //calculate the end of testing (to save the x+w calculation each for loop)

	tileCoordY = y / TILESIZE;				 //calculate the y position (map coordinates) of the tiles we want to test

	int tileCoordX = tileXpixels / TILESIZE; //calculate map x coordinate for first tile

	//loop while the start point (pixels!) of the test tile is inside the hitbox
	while (tileXpixels <= testEnd)
	{
		if (Tilemap::map(tileCoordX, tileCoordY) != NONSOLID) //only this changed: when jumping (moving up) we don't want to go through slopes
			return true;

		tileCoordX++;				    //increase tile x map coordinate
		tileXpixels += TILESIZE;		//increase tile x pixel coordinate
	}
	return false;
}

bool Player::collisionHorizontalDown(int x, int y, int& tileCoordY)
{
	int tileXpixels = x - (x % TILESIZE);	  //calculate the x position (pixels!) of the tiles we check against
	int testEnd = x + m_hitbox.width;

	tileCoordY = y / TILESIZE;			      //calculate the y position (map coordinates!) of the tiles we want to test

	int tileCoordX = tileXpixels / TILESIZE;  //calculate map x coordinate for first tile


	//loop while the start point (pixels!) of the test tile is inside the hitbox
	while (tileXpixels <= testEnd)
	{
		if (Tilemap::map(tileCoordX, tileCoordY) == SOLID)	//is a solid tile is found at tilecoordx, tilecoordy?
			return true;

		tileCoordX++;											//increase tile x map coordinate
		tileXpixels += TILESIZE;								//increase tile x pixel coordinate
	}
	return false;
}

bool Player::collisionSlope(int sx, int sy, int& tsx, int& tsy)
{
	/*
	* Checks tile containing the player is sloped tile
	* If tile is sloped, adjust y co-ordinate of player according to x
	*/

	//Find tile's co-ordinates 
	tsx = sx / TILESIZE;
	tsy = sy / TILESIZE;

	//Checks tile's type
	TileType t = Tilemap::map(tsx, tsy);
	//If tile is sloped set y according to slope.
	if (t == LEFTSLOPED) 
	{
		//leftslope -> \  
		if (TILESIZE - (sy - tsy * TILESIZE) > TILESIZE - (sx - tsx * TILESIZE) + 1)
			m_hitbox.top += std::ceil(((sx - tsx * TILESIZE) - (sy - tsy * TILESIZE)) * 0.2);
		else
			m_hitbox.top = (tsy + 1) * TILESIZE - (TILESIZE - (sx % TILESIZE)) - m_hitbox.height - 1;
		return true;
	}
	else if (t == RIGHTSLOPED)
	{
		//rightslope -> /
		if ((TILESIZE - (sy - tsy*TILESIZE)) > (sx - tsx*TILESIZE) + 1)
			m_hitbox.top += std::ceil(((TILESIZE - (sy - tsy * TILESIZE)) - (sx - tsx * TILESIZE))*0.2);
		else
			m_hitbox.top = (tsy + 1) * TILESIZE - (sx % TILESIZE) - m_hitbox.height - 1;
		return true;
	}
	return false;
}

void Player::updateMapCollision()
{
	//check for slopes (only if moving down) 
	if (m_velocity.y > 0) 
	{
		int tsx, tsy;				//slope tile coordinates

		//Hitbox's bottom-horizontal side's middle point
		//Case 1: Player Enter a slope
		int sx = m_hitbox.left + (m_hitbox.width>>1) + m_velocity.x;	
		
		//Check collision of above mentioned point with the sloped tile (if present)
		if (collisionSlope(sx, (m_hitbox.top + m_hitbox.height), tsx, tsy))
		{
			m_hitbox.left += m_velocity.x;	
			//y has been set by collisionSlope function

			unlockjump();	//we hit the ground - the player may jump again
			 
			m_velocity.y = 1;		//test against the ground again in the next frame (We only check for slope if velocity.y is > 0)

			m_slopePrevTileX = tsx;	//save slope coordinate
			m_slopePrevTileY = tsy;

			return;
		}
		else 
		{	
			//player is not on a slope in this frame, now check if we came from a slope
			//-1 ... we are not on a slope
			//0  ... we left a slope after moving down
			//1  ... we left a slope after moving up
			int stateCode = -1;

			if (Tilemap::map(m_slopePrevTileX, m_slopePrevTileY) == LEFTSLOPED)
			{
				if (m_velocity.x > 0)
					stateCode = 0;  //moving down the slope
				else
					stateCode = 1;	//moving up the slope
			}
			else if (Tilemap::map(m_slopePrevTileX, m_slopePrevTileY) == RIGHTSLOPED)
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
				if (collisionSlope(sx, sy, tsx, tsy)) 
				{
					m_hitbox.left += m_velocity.x;

					unlockjump();

					m_velocity.y = 1;

					m_slopePrevTileX = tsx;
					m_slopePrevTileY = tsy;

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
		if (verticalCollision(m_hitbox.left + m_hitbox.width + m_velocity.x, m_hitbox.top, tileCoord))	//collision on the right side
			m_hitbox.left = tileCoord * TILESIZE - m_hitbox.width - 1;			//move to the edge of the tile (tile on the right - player width)
		else
			m_hitbox.left += m_velocity.x; //No collision
	}
	else if (m_velocity.x < 0)
	{	//moving left
		if (verticalCollision(m_hitbox.left + m_velocity.x, m_hitbox.top, tileCoord))		//collision on the left side
			m_hitbox.left = (tileCoord + 1) * TILESIZE + 1;									//move to the edge of the tile
		else
			m_hitbox.left += m_velocity.x;
	}
	

	// y axis collision (|)
	if (m_velocity.y < 0)
	{	//moving up
		if (collisionHorizontalUp(m_hitbox.left, m_hitbox.top + m_velocity.y, tileCoord))
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
		if (collisionHorizontalDown(m_hitbox.left, m_hitbox.top + m_hitbox.height + m_velocity.y, tileCoord))
		{	//on ground
			m_hitbox.top = tileCoord * TILESIZE - m_hitbox.height - 1;
			m_velocity.y = 1;				//1 so we test against the ground again in the next frame (0 would test against the ground in the next+1 frame)

			unlockjump();
		}
		else 
		{	//falling (in air)
			m_hitbox.top += m_velocity.y;
			m_velocity.y += m_gravity;

			//if (m_velocity.y >= TILESIZE)		//if the speed is higher than this we might fall through a tile
			//	m_velocity.y = TILESIZE;        //Since we are limiting the speed we don't need this

			m_lockjump = true;			        //lock jump if falling
		}
	}

	m_slopePrevTileX = (m_hitbox.left + (m_hitbox.width >> 1)) / TILESIZE;
	m_slopePrevTileY = (m_hitbox.top + m_hitbox.height) / TILESIZE;
}

void Player::unlockjump() 
{
	//the player may jump again:
	//a) if he fell off an edge (!jumping) - without releasing the jump key on the ground
	//b) if he jumped - only when he releases the jump key on the ground	
	if (!m_jumping || !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_lockjump = false;
		m_jumping = false;
	}
}

//Functions
void Player::movePlayerBy(sf::Vector2f& velocity)
{
	m_hitbox.left += velocity.x;
	m_hitbox.top += velocity.y;
}

void Player::updateMovement()
{
	/*
	- Moves player in a specified direction
	- Sets animation state of the player (Idle, Moving left, Moving Right)
	- Allow player to jump
	*/
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

	//Jump when touching the bottom of window or any hard object
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_lockjump)
	{
		m_velocity.y = -8;
		m_lockjump = true;   //Player not allowed to jump
		m_jumping = true;
	}
}

void Player::updatePhysics()
{
	/*
	- Limits velocity if max velocity in y direction is attained
	- Enforces drag in x direction
	- Stops the player if min velocity is attained (both x, y direction)
	*/

	//Limit velocity
	if (std::abs(m_velocity.x) >= m_velocityMaxX)
		m_velocity.x = m_velocityMaxX * ((m_velocity.x < 0) ? -1 : 1);

	if (std::abs(m_velocity.y) >= m_velocityMaxY)
		m_velocity.y = m_velocityMaxY * ((m_velocity.y < 0) ? -1 : 1);

	m_velocity.x *= m_drag;

	if (std::abs(m_velocity.x) <= m_velocityMin)
		m_velocity.x = 0;
	/*if (std::abs(m_velocity.y) <= m_velocityMin)
		m_velocity.y = 0;*/
}

//Public Functions
void Player::update()
{
	updateMovement();
	updateMapCollision();
	updatePlayerAnimation();
	updatePhysics();
}

void Player::render(sf::RenderTarget* target)
{
	/*
	- Renders Player
	*/

	renderPlayerAnimation(target, m_hitbox);
}