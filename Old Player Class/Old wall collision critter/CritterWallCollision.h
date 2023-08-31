#pragma once
class CritterWallCollision
{
protected:
	//Tests for collision with tiles on the vertical line from [x,y] to [x,y+height]
	bool verticalCollision(sf::FloatRect& hitbox, int x, int y, int& tileCoordX);
	bool collisionHorizontalUp(sf::FloatRect& hitbox, int x, int y, int& tilecoordy);		//horizontal line from [x,y] to [x+width, y]
	bool collisionHorizontalDown(sf::FloatRect& hitbox, int x, int y, int& tilecoordy);//same as horUp, but we don't want to go through slopes here
	bool collisionSlope(sf::FloatRect& hitbox, int sx, int sy, int& tsx, int& tsy);	//Test for collisions against a slope at sx, sy - if a slope is found y is set accordingly
};