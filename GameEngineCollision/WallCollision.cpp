#include "stdafx.h"
#include "WallCollision.h"
#include "Tilemap.h"

#define TILESIZE 40

bool WallCollision::collisionSlope(sf::FloatRect& hitbox, int sx, int sy, int& tsx, int& tsy)
{
	/* Checks if tile is sloped tile
	*  If tile is sloped, adjust y co-ordinate of WallCollision according to x
	*  Updates hitbox's y co-ordinate if the hitbox collides with the tile
	*  Object's y co-ordinate is adjusted using line equation to make the landing smoother
	* 
	*  @param hitbox is the hitbox of any object (player, enemy, bullet)
	*  @param sx is the x co-ordinate of bottom-horiztonal side's middle point
	*  @param sy is the y co-ordinate of bottom-horiztonal side's middle point
	*  @param tsx is the x co-ordinate of tile we are evaluating
	*  @param tsy is the y co-ordinate of tile we are evaluating
	*  @return true if tile is sloped else false
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
		//If block checks if the player is not touching the slope than it will descend at a predefined rate (to make smoother landing)
		//else block checks if the player is on the slope, than it stays on the slope
		if (TILESIZE - (sy - tsy * TILESIZE) > TILESIZE - (sx - tsx * TILESIZE) + 1)
			hitbox.top += std::ceil(((sx - tsx * TILESIZE) - (sy - tsy * TILESIZE)) * 0.2);
		else
			hitbox.top = (tsy + 1) * TILESIZE - (TILESIZE - (sx % TILESIZE)) - hitbox.height - 1;
		return true;
	}
	else if (t == RIGHTSLOPED)
	{
		//rightslope -> /
		if ((TILESIZE - (sy - tsy * TILESIZE)) > (sx - tsx * TILESIZE) + 1)
			hitbox.top += std::ceil(((TILESIZE - (sy - tsy * TILESIZE)) - (sx - tsx * TILESIZE)) * 0.2);
		else
			hitbox.top = (tsy + 1) * TILESIZE - (sx % TILESIZE) - hitbox.height - 1;
		return true;
	}
	return false;
}

bool WallCollision::collisionHorizontalUp(sf::FloatRect& hitbox, int x, int y, int& tileCoordY)
{
	/*
	*  Checks collision on y-axis
	*  Updates the co-ordinate of tile (for further analysis)
	*
	*  @param hitbox is the hitbox of any object (player, enemy, bullet)
	*  @param x is the x co-ordinate of player's hitbox
	*  @param y is the y co-ordinate of player's hitbox
	*  @param tileCoordY is the y co-ordinate of tile we are evaluating
	*  @return true is object collides with the tile else false
	*/

	int tileXpixels = x - (x % TILESIZE);    //Calculate the x co-ordinate (pixels) of the tile to be checked
	int testEnd = x + hitbox.width;		     //Calculate the end case (the last point on player's hitbox that can collide

	tileCoordY = y / TILESIZE;				 //Calculate the y position (map coordinates) of the tile to be checked

	int tileCoordX = tileXpixels / TILESIZE; //Calculate map x coordinate for first tile

	//Loops through all possible tiles that the object can collide with
	while (tileXpixels <= testEnd)
	{
		//When jumping (moving up) object doesn't go through slopes
		if (Tilemap::map(tileCoordX, tileCoordY) != NONSOLID)
			return true;

		tileCoordX++;				         //Increase tile's x map coordinate
		tileXpixels += TILESIZE;		     //increase tile's x pixel coordinate
	}
	return false;
}

bool WallCollision::collisionHorizontalDown(sf::FloatRect& hitbox, int x, int y, int& tileCoordY)
{
	/*
	*  Checks collision on y-axis
	*  Updates the co-ordinate of tile (for further analysis)
	*
	*  @param hitbox is the hitbox of any object (player, enemy, bullet)
	*  @param x is the x co-ordinate of player's hitbox
	*  @param y is the y co-ordinate of player's hitbox
	*  @param tileCoordY is the y co-ordinate of tile we are evaluating
	*  @return true is object collides with the tile else false
	*/

	int tileXpixels = x - (x % TILESIZE);	 //Calculate the x position (pixels!) of the tiles we check against
	int testEnd = x + hitbox.width;

	tileCoordY = y / TILESIZE;			     //Calculate the y position (map coordinates!) of the tiles we want to test

	int tileCoordX = tileXpixels / TILESIZE; //Calculate map x coordinate for first tile


	//Loops through all possible tiles that the object can collide with
	while (tileXpixels <= testEnd)
	{
		if (Tilemap::map(tileCoordX, tileCoordY) == SOLID)	
			return true;

		tileCoordX++;						 //Increase tile x map coordinate
		tileXpixels += TILESIZE;			 //Increase tile x pixel coordinate
	}
	return false;
}

bool WallCollision::verticalCollision(sf::FloatRect& hitbox, int x, int y, int& tileCoordX)
{
	/*
	*  Checks collision on x-axis
	*  Updates the co-ordinate of tile (for further analysis)
	*
	*  @param hitbox is the hitbox of any object (player, enemy, bullet)
	*  @param x is the x co-ordinate of player's hitbox
	*  @param y is the y co-ordinate of player's hitbox
	*  @param tileCoordX is the x co-ordinate of tile we are evaluating
	*  @return true is object collides with the tile else false
	*/

	//Find y co-ordinate of colliding tile (in pixels)
	int tileYpixels = y - (y % TILESIZE);
	//Last point where we need to check for a tile
	int testEnd = y + hitbox.height;

	tileCoordX = x / TILESIZE;

	int tileCoordY = tileYpixels / TILESIZE;

	//Loops through all possible tiles that the object can collide with
	while (tileYpixels <= testEnd)
	{
		//If colliding tile is SOLID return true
		if (Tilemap::map(tileCoordX, tileCoordY) == SOLID)
			return true;

		tileCoordY++;
		tileYpixels += TILESIZE;
	}
	return false;
}