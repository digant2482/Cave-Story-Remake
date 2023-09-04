#pragma once

//Player animation states
enum PlayerState { IDLE = 0, MOVING_RIGHT, MOVING_LEFT, JUMPING }; 

class PlayerAnimation
{
private:
	//Player Sprite
	sf::Texture m_texture;
	sf::Sprite m_spriteSheet;

	//Texture Rectangles (to be snipped from spritesheet)
	sf::IntRect m_runLeft;                   //Running left texture rectangle
	sf::IntRect m_runRight;					 //Running right texture rectangle

	//Animation Variables
	PlayerState m_previousPlayerState;       //Player's moving state in previous frame
	sf::Clock m_animationTimer;              //Times the interval (0.2 seconds) after which new graphic is rendered (for smooth movement)
	sf::Clock m_revivalStateTimer;	         //Times player's revival state (3 seconds)
	sf::Clock m_revivalAnimationTimer;		 //Times the interval for which not to render player sprite during revival (0.1 seconds)
	sf::IntRect m_currentFrame;				 //Variable that is assigned current texture rectangle
	bool m_facingRight;

	//Initializers
	void initSprite();
	void initIntRect();
	void initVariables();

	//Private Functions
	const sf::IntRect getIdleRightTexture(); //Gets texture rectangle for idle state facing right
	const sf::IntRect getIdleLeftTexture();  //Gets texture rectangle for idle state facing left
	const sf::IntRect getRunLeftTexture();   //Gets texture rectangle for running state facing left
	const sf::IntRect getRunRightTexture();  //Gets texture rectangle for running state facing right

protected:
	PlayerAnimation();

	//Player Moving State
	PlayerState m_playerState;               //Player's moving state

	//Player Revival State
	bool m_revivalState;			         //True when player is hit, player cannot be hit again if true

	//Functions
	void updateRevivalState();				 //Updates player's revival state
	void updatePlayerAnimation();            //Updates player's animation state
	void renderPlayerAnimation(sf::RenderTarget* target, sf::FloatRect& playerHitbox);

public:
	//Modifiers
	void setRevivalState(const bool state);  //Sets player's revival state

	//Accessors
	const bool& isFacingRight() const;		 //True if player is facing right
	const bool& isRevivalStateActive() const;//True if revival state is true
};