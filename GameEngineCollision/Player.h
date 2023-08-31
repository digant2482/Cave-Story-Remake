#pragma once

#include "PlayerAnimation.h"
#include "WallCollision.h"

class Player : public PlayerAnimation, public WallCollision
{
private:
	//Hitbox
	sf::FloatRect m_hitbox;

	//Health
	int m_currentHealth;
	int m_maxHealth;

	//Physics
	sf::Vector2f m_velocity; //Player velocity
	float m_velocityMaxX; //Terminal velocity in x direction
	float m_velocityMaxY;
	float m_velocityMin;  //Stops if velocity below this value
	float m_acceleration; //Acceleration in x direction
	float m_drag;		  //Deceleration in x direction
	float m_gravity;	  //Gravity

	//Jump
	bool m_lockjump;		//Denies the player to jump
	bool m_jumping;			//Is player jumping ?

	//The tile at slopex, slopey in the last frame
	int m_prevTileX;
	int m_prevTileY;

	//Initializers
	void initHitbox();
	void initHealth();
	void initPhysics();
	void initVariables();

	//Jump and movements
	void unlockjump();											//Player may jump again if the conditions in this function are true
	void movePlayerBy(sf::Vector2f& velocity);					//Player's position is moved by velocity
	void updateMapCollision();									//Checks collison of player with the map
	void updateMovement();										//Take inputs from keyboard
	void updatePhysics();

public:
	Player();

	//Modifiers
	void setPosition(const int x, const int y);
	void updateHP(const int x);                   //Updates player's health

	//Accessors
	const sf::Vector2i& getPosition() const;
	const std::pair<int, int> getHealth() const;
	const sf::FloatRect& getHitbox() const;

	//Functions
	void update();                                //Updates all the aspects of the player (see definition)
	void render(sf::RenderTarget* target);		  //Renders all the aspects of the player
};