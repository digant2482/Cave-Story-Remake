#pragma once

enum class CritterState { IDLE = 0, NOTICING, JUMPING }; //CritterAnimationState

class CritterAnimation
{
private:
	//critter Sprite
	sf::Texture m_textureSheet;
	sf::Sprite m_sprite;

	//IntRect of states
	sf::IntRect m_idleRightTexture;
	sf::IntRect m_idleLeftTexture;
	sf::IntRect m_noticingRightTexture;
	sf::IntRect m_noticingLeftTexture;
	sf::IntRect m_jumpingRightTexture;
	sf::IntRect m_jumpingLeftTexture;

	//Variables
	sf::Clock m_animationTimer;
	sf::IntRect m_currentFrame;

	//Initializers
	void initSprite();
	void initVariables();
	void initStates();

protected:
	CritterAnimation();

	//Variables
	CritterState m_critterState;

	//Functions
	void updateCritterAnimation(bool& facingRight);
	void renderCritterAnimation(sf::RenderTarget* target, const sf::FloatRect& critterHitbox);
};