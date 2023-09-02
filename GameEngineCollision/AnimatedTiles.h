#pragma once
class AnimatedTiles
{
private:
	sf::Texture m_animatedTilesTexture;
	sf::Sprite m_animatedTilesSpriteSheet;

	static sf::IntRect m_healthFillUpStation;
	static sf::IntRect m_saveDisk;
	static sf::IntRect m_increaseMaxHealth;
	sf::Vector2f m_healthFillUpStationPosition;
	sf::Vector2f m_saveDiskPosition;
	sf::Vector2f m_increaseMaxHealthPosition;

	sf::Clock m_animationTimer;

	//Initializers
	void initSprite();
	void initAnimationVariables();

protected:
	//Constructor
	AnimatedTiles();

	//Functions
	void updateAnimatedTiles();
	void renderAnimatedTiles(sf::RenderTarget* target);

public:
	//Accessors
	static const sf::IntRect& getHealthFillUpStation();
	static const sf::IntRect& getIncreaseMaxHealth();
	static const sf::IntRect& getSaveDisk();
};

