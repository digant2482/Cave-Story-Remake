#pragma once
#include "CritterAnimation.h"
#include "WallCollision.h"
#include "Player.h"

class Critter : public CritterAnimation, public WallCollision
{
private:
	sf::FloatRect m_hitbox;

	//Health
	int m_currentHealth;

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
	void initHitbox(const float x, const float y);
	void initHealth();
	void initOrientation();
	void initPhysics();

	//Functions
	void updateOrientation(Player& player);
	void updateMovement(Player& player);

	void updatePlayerEnemyCollision(Player& player);

	void updateCritterWallCollision();
	void unlockJump();
public:
	Critter(const float x, const float y);

	//Modifiers
	const int& updateHealth(const int healthPoints);

	//Accessors
	const sf::FloatRect& getBounds() const;

	void update(Player& player);
	void render(sf::RenderTarget* target);
};