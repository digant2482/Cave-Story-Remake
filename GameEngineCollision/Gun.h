#pragma once
#include "Bullet.h"
#include "Player.h"
#include "Bat.h"
#include "Critter.h"

class Gun
{
private:
	//Sprite and Textures
	sf::Texture m_gunTexture;
	sf::Texture m_bulletTexture;
	sf::Sprite m_bulletSpriteSheet;
	sf::Sprite m_gunSpriteSheet;

	//Animation Texture Squares
	sf::IntRect m_gunLeft;
	sf::IntRect m_gunRight;

	//Gun Levels
	int m_gunLevel;
	int m_gunLevelPoints;

	//Bullets
	std::vector<BulletLev1> m_bulletsLev1;
	std::vector<BulletLev2> m_bulletsLev2;
	std::vector<BulletLev3> m_bulletsLev3;
	float m_bulletVelocity;

	//Fire Variables
	sf::Clock m_fireTimer;
	bool m_heldLSHIFT;

	//Level texture rect
	sf::IntRect m_level1Rect;
	sf::IntRect m_level2Rect;
	sf::IntRect m_level3Rect;

	//Initializers
	void initSprite();
	void initGunLevel();
	void initVariables();
	void initLevelTextureRect();

	//Functions
	bool bulletWallCollision(const sf::FloatRect& bulletBounds, int x, int y);
	bool bulletBatCollision(const sf::FloatRect& bulletBounds, std::vector<std::unique_ptr<Bat>>& batArray);
	bool bulletCritterCollision(const sf::FloatRect& bulletBounds, std::vector<std::unique_ptr<Critter>>& critterArray);

	void updateGunLevelPoints();
	void updateGunPosition(Player& player);
	void updateFire(Player& player);
	void updateFiringKey();
	void updateBulletPositionAndCollision(std::vector<std::unique_ptr<Bat>>& batArray, std::vector<std::unique_ptr<Critter>>& critterArray);

	void renderGun(sf::RenderTarget* target);
	void renderBullets(sf::RenderTarget* target);
public:
	Gun();

	void update(Player& player, std::vector<std::unique_ptr<Bat>>& batArray, std::vector<std::unique_ptr<Critter>>& critterArray);
	void render(sf::RenderTarget* target);
};