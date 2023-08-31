#pragma once
#include "CritterAnimation.h"
#include "WallCollision.h"
#include "Player.h"

class Critter : public CritterAnimation, public WallCollision
{
private:
	sf::FloatRect m_hitbox;

	//Animation
	sf::IntRect m_currentFrame;
	sf::Clock m_animationTimer;

	//Physics
	sf::Vector2f m_velocity;
	float m_gravity;
	bool m_jumping;
	bool m_lockjump;
	sf::Clock m_movementTimer;

	//Orientation
	bool m_facingRight;

	//Previous Tile 
	int m_prevTileX;
	int m_prevTileY;

	//Initializers
	void initHitbox();
	void initOrientation();
	void initPhysics();

	//Functions
	void updateOrientation(Player& player);
	void updateMovement(Player& player);

	void updatePlayerEnemyCollision(Player& player);

	void updateCritterWallCollision();
	void unlockJump();
public:
	Critter();

	//Modifiers
	void setPosition(const int x, const int y);

	void update(Player& player);
	void render(sf::RenderTarget* target);
};