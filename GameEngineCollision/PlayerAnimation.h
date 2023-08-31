#pragma once

enum PlayerState { IDLE = 0, MOVING_RIGHT, MOVING_LEFT, JUMPING }; //playeranimationstate

class PlayerAnimation
{
private:
	//Player Sprite
	sf::Texture m_textureSheet;
	sf::Sprite m_sprite;

	//IntRect of states
	sf::IntRect m_runLeft;
	sf::IntRect m_runRight;

	//Variables
	PlayerState m_previousPlayerState;
	sf::Clock m_animationTimer;
	sf::IntRect m_currentFrame;
	bool m_facingRight;

	//Initializers
	void initSprite();
	void initIntRect();
	void initVariables();

	//Private Functions
	const sf::IntRect getIdleRightTexture();
	const sf::IntRect getIdleLeftTexture();
	const sf::IntRect getRunLeftTexture();
	const sf::IntRect getRunRightTexture();

protected:
	PlayerAnimation();

	//Variables
	PlayerState m_playerState;

	//Revival State
	bool m_revivalState;			//Activates when player is hit, player cannot be hit again if activated
	sf::Clock m_revivalStateTimer;	//Time for which player is in revival state
	sf::Clock m_revivalAnimationTimer;


	//Functions
	void updateRevivalState();
	void updatePlayerAnimation();
	void renderPlayerAnimation(sf::RenderTarget* target, sf::FloatRect& playerHitbox);

public:
	//Modifiers
	void setRevivalState(const bool state);

	//Accessors
	const bool& isFacingRight();
	const bool& isRevivalStateActive() const;
};