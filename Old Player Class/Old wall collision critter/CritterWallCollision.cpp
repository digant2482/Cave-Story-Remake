#include "stdafx.h"
#include "CritterWallCollision.h"
#include "Tilemap.h"

bool CritterWallCollision::verticalCollision(sf::FloatRect& hitbox, int x, int y, int& tileCoordX)
{
	/*
	* Checks collision on x-axis
	* Updates the co-ordinate of tile (which is colliding with CritterWallCollision)
	*/

	//Find y co-ordinate of colliding tile (in pixels)
	int tileYpixels = y - (y % TILESIZE);
	int testEnd = y + hitbox.height;

	tileCoordX = x / TILESIZE;

	int tileCoordY = tileYpixels / TILESIZE;

	while (tileYpixels <= testEnd)
	{
		if (Tilemap::map(tileCoordX, tileCoordY) == SOLID)
			return true;

		tileCoordY++;
		tileYpixels += TILESIZE;
	}

	return false;
}

bool CritterWallCollision::collisionHorizontalUp(sf::FloatRect& hitbox, int x, int y, int& tileCoordY)
{
	int tileXpixels = x - (x % TILESIZE);    //calculate the x position (pixels) of the tiles we check against
	int testEnd = x + hitbox.width;		 //calculate the end of testing (to save the x+w calculation each for loop)

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

bool CritterWallCollision::collisionHorizontalDown(sf::FloatRect& hitbox, int x, int y, int& tileCoordY)
{
	int tileXpixels = x - (x % TILESIZE);	  //calculate the x position (pixels!) of the tiles we check against
	int testEnd = x + hitbox.width;

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

bool CritterWallCollision::collisionSlope(sf::FloatRect& hitbox, int sx, int sy, int& tsx, int& tsy)
{
	/*
	* Checks tile containing the CritterWallCollision is sloped tile
	* If tile is sloped, adjust y co-ordinate of CritterWallCollision according to x
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