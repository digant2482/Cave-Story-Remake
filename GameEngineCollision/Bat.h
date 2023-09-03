#pragma once
#include "Player.h"
class Bat
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	//Animation
	sf::IntRect m_currentFrame;
	sf::Clock m_animationTimer;

	//Orientation
	bool m_facingRight;

	//Initial Position
	sf::Vector2f m_initialPos;

	//Initializers
	void initSprite();
	void initOrientation();
	void initAnimation();

	//Functions
	void updateOrientation(Player& player);
	void updateMovement();

	void updatePlayerEnemyCollision(Player& player);

	void updateAnimation();
public:
	Bat();
	Bat(const float x, const float y);

	//Modifiers
	void setPosition(const float x, const float y);

	//Accessors
	const sf::FloatRect getBounds() const;

	void update(Player& player);
	void render(sf::RenderTarget* target);
};