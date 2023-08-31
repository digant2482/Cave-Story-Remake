#pragma once

#include "PlayerAnimation.h"

class Player : public PlayerAnimation
{
private:
	//Hitbox
	sf::IntRect m_hitbox;

	//Physics
	sf::Vector2f m_velocity; //Player velocity
	float m_velocityMaxX; //Terminal velocity in x direction
	float m_velocityMaxY;
	int m_velocityMin;  //Stops if velocity below this value
	float m_acceleration; //Acceleration in x direction
	float m_drag;		  //Deceleration in x direction
	float m_gravity;	  //Gravity

	//Jump
	bool m_lockjump;		//Denies the player to jump
	bool m_jumping;			//Is player jumping ?

	//The tile at slopex, slopey in the last frame
	int m_slopePrevTileX;
	int m_slopePrevTileY;

	//Private Functions

	//Initializers
	void initHitbox();
	void initPhysics();
	void initVariables();

	//Collision Detection
	bool verticalCollision(int x, int y, int& tilecoordx);			//tests for collision with a tile on the vertikal line from [x,y] to [x,y+height]
	bool collisionHorizontalUp(int x, int y, int& tilecoordy);		//horizontal line from [x,y] to [x+width, y]
	bool collisionHorizontalDown(int x, int y, int& tilecoordy);//same as horUp, but we don't want to go through slopes here
	bool collisionSlope(int sx, int sy, int& tsx, int& tsy);	//Test for collisions against a slope at sx, sy - if a slope is found y is set accordingly
	
	//Jump and movements
	void unlockjump();											//Player may jump again if the conditions in this function are true
	void movePlayerBy(sf::Vector2f& velocity);					//Player's position is moved by velocity
	void updateMapCollision();									//Checks collison of player with the map
	void updateMovement();										//Take inputs from keyboard
	void updatePhysics();
public:
	Player();
	Player(int x, int y);

	//Modifiers
	void setPosition(int x, int y);

	//Accessors
	const sf::Vector2i getPosition();

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};