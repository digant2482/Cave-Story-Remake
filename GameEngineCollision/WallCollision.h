#pragma once
class WallCollision
{
protected:
	bool verticalCollision(sf::FloatRect& hitbox, int x, int y, int& tileCoordX);       //Tests for collision on x-axis    
	bool collisionHorizontalUp(sf::FloatRect& hitbox, int x, int y, int& tilecoordy);   //Tests for collision on y-axis (above object)
	bool collisionHorizontalDown(sf::FloatRect& hitbox, int x, int y, int& tilecoordy); //Tests for collision on y-axis (below object)
	bool collisionSlope(sf::FloatRect& hitbox, int sx, int sy, int& tsx, int& tsy);  	//Tests for collision with slopes
};