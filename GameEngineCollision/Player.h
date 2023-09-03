#pragma once

#include "PlayerAnimation.h"
#include "WallCollision.h"

class Player : public PlayerAnimation, public WallCollision
{
private:
	//Hitbox
	sf::FloatRect m_hitbox;

	//Health
	int m_currentHealth;        //Player's health
	int m_maxHealth;			//Player's max health

	//Physics
	sf::Vector2f m_velocity;    //Player velocity
	float m_velocityMaxX;		//Terminal velocity in x direction
	float m_velocityMaxY;		//Terminal velocity in y direction
	float m_velocityMin;		//Player stops if velocity falls below this value
	float m_acceleration;		//Acceleration in x direction
	float m_drag;				//Deceleration in x direction
	float m_gravity;			//Gravity

	//Jump
	bool m_lockjump;		    //Denies the player to jump
	bool m_jumping;			    //Is player jumping ?

	int m_prevTileX;			//Previous Tile's X co-ordinate (Tile encompassing player co-ordinates) 
	int m_prevTileY;			//Previous Tile's Y co-ordinate (Tile encompassing player co-ordinates) 

	//Initializers
	void initHitbox();
	void initHealth();
	void initPhysics();
	void initVariables();

	//Jump and movements
	void unlockjump();											//Player may jump again if the conditions in this function are true
	void movePlayerBy(sf::Vector2f& velocity);					//Player's position is moved by velocity
	void updateMapCollision();									//Checks collison of player with the tiles
	void updateMovement();										//Take inputs from keyboard
	void updatePhysics();										//Updates physics 
	void updateMiscellaneousItems();							//Updates health fill up station, save progress, increase max health

public:
	Player();

	//Modifiers
	void setPosition(const int x, const int y);
	void updateHP(const int x);                   //Updates player's health

	//Accessors
	const sf::Vector2f& getPosition() const;
	const std::pair<int, int> getHealth() const;
	const sf::FloatRect& getHitbox() const;

	//Functions
	void update();                                //Updates all the aspects of the player (see definition)
	void render(sf::RenderTarget* target);		  //Renders all the aspects of the player
};