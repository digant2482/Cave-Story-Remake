#include "stdafx.h"
#include "Gun.h"

void Gun::initSprite()
{
	/* Loads bullet's and gun's texture from file
	*  Loads bullet's and gun's texture into spritesheet
	*  Sets texture rectangle of gun (for right and left direction)
	*/

	if (!m_gunTexture.loadFromFile("Textures/Weapons/NpcSym.bmp"))
		std::cout << "ERROR::GUN::INITSPRITE::FAILED TO LOAD GUN" << '\n';
	m_gunSpriteSheet.setTexture(m_gunTexture);
	m_gunSpriteSheet.scale(1.75f, 1.75f);

	//Texture rectangle for gun facing right and left direction
	m_gunLeft  = sf::IntRect(189, 163, 9, 3);
	m_gunRight = sf::IntRect(186, 179, 9, 3);

	if (!m_bulletTexture.loadFromFile("Textures/Weapons/Bullet.bmp"))
		std::cout << "ERROR::GUN::INITSPRITE::FAILED TO LOAD GUN" << '\n';
	m_bulletSpriteSheet.setTexture(m_bulletTexture);
}

void Gun::initGunLevel()
{
	/* Initializes gun's level and gun's level points */
	m_gunLevel = 1;
	m_gunLevelPoints = 0;
}

void Gun::initVariables()
{
	/* Initializes bullet velocity and LSHIFT key (LSHIFT key is used to fire gun)*/
	m_bulletVelocity = 2.5f;
	m_heldLSHIFT = false;
}

void Gun::initLevelTextureRect()
{
	/* Initializes bullet's texture rectangle */
	m_bulletLevel1Rect = sf::IntRect(128, 38, 16, 3);
	m_bulletLevel2Rect = sf::IntRect(160, 36, 16, 6);
	m_bulletLevel3Rect = sf::IntRect(32, 38, 16, 6);
}

Gun::Gun()
{
	/* Calls the initializers */
	initGunLevel();
	initSprite();
	initVariables();
	initLevelTextureRect();
}

//Modifiers
void Gun::setGunLevelCurrentPoints(int x)
{
	/* Sets current level points of a gun (Used for loading saved progress) */
	m_gunLevelPoints = x;
}


void Gun::updateGunLevelPoints()
{
	/* Updates gun's level points 
	*  Updates gun's level is gun's level points is more than 5 */
	if (m_gunLevelPoints >= 5)
	{
		if (m_gunLevel != 3)
		{
			//Clear bullets of previous level (Free memory)
			if (m_gunLevel == 1)
				m_bulletsLev1.clear();
			else if (m_gunLevel == 2)
				m_bulletsLev2.clear();

			//Update gun's level
			m_gunLevel++;
			m_gunLevelPoints = 0;
		}
		else
		{
			//Reset points to max points
			m_gunLevelPoints = 5;
		}
	}
}

void Gun::updateGunPosition(Player& player)
{
	/* Updates gun's position according to player's position 
	*  Updates gun's texture rectangle according to gun's orientation
	*/
	m_gunSpriteSheet.setPosition(player.getPosition().x, player.getPosition().y);
	if (player.isFacingRight())
	{
		m_gunSpriteSheet.setTextureRect(m_gunRight);
		m_gunSpriteSheet.move(9.f, 22.f);
	}
	else
	{
		m_gunSpriteSheet.setTextureRect(m_gunLeft);
		m_gunSpriteSheet.move(-16.f, 22.f);
	}
}

void Gun::updateFire(Player& player)
{
	/* Evaluates fire direction using player's orientation 
	*  Fires a bullet is LSHIFT key is not pressed
	*  Appends in the bullet in relevant bullet array
	*  Sets m_heldLSHIFT to true 
	*/

	int fireDirection = player.isFacingRight() ? 1 : -1;
	if (!m_heldLSHIFT)
	{
		if (m_gunLevel == 1)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				m_heldLSHIFT = true;
				m_bulletsLev1.emplace_back(BulletLev1(m_gunSpriteSheet.getPosition().x + 2.f,
					m_gunSpriteSheet.getPosition().y, fireDirection));
			}
		}
		else if (m_gunLevel == 2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				m_heldLSHIFT = true;
				m_bulletsLev2.emplace_back(BulletLev2(m_gunSpriteSheet.getPosition().x + 2.f,
					m_gunSpriteSheet.getPosition().y, fireDirection));
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				m_heldLSHIFT = true;
				m_bulletsLev3.emplace_back(BulletLev3(m_gunSpriteSheet.getPosition().x + 2.f,
					m_gunSpriteSheet.getPosition().y, fireDirection));
			}
		}
	}
}

//Bullet Collisions
bool Gun::bulletWallCollision(const sf::FloatRect& bulletBounds, int x, int y)
{
	/* Checks bullet's collision with the walls in x-axis
	*  This function is taken from wall collision class' verticalCollision function
	*/

	int tileYpixels = y - (y % TILESIZE);
	int testEnd = y + bulletBounds.height;

	int tileCoordX = x / TILESIZE;

	int tileCoordY = tileYpixels / TILESIZE;

	while (tileYpixels <= testEnd)
	{
		if (Tilemap::map(tileCoordX, tileCoordY) == SOLID)
			return true;

		tileCoordY++;
		tileYpixels += TILESIZE;
	}

	return false;
}

bool Gun::bulletBatCollision(const sf::FloatRect& bulletBounds, std::vector<std::unique_ptr<Bat>>& batArray)
{
	/* Checks if bullet kills the bat 
	*  Loops through all the bats and checks if the bullet hit (intersects) the bat's bounds
	*  If any bat is hit, bat is erased and reward widget is created at the position of bat's death
	*  Reward widget (HealthUpHeart, GunLevelPointsTriangle is randomly selected using srand function
	*  @return true if bat is hit else false
	*/

	for (int j = 0; j < batArray.size(); j++)
	{
		//If player hits the enemy, delete the enemy
		if (bulletBounds.intersects(batArray[j]->getBounds()))
		{
			//33% chance for health up reward and 67% chance for gun level points reward
			int selector = rand() % 1;
			if (selector == 1)
				m_healthUpArray.emplace_back(HealthUpHeart(batArray[j]->getBounds().getPosition()));
			else
				m_gunLevelPointsArray.emplace_back(GunLevelPointsTriangle(batArray[j]->getBounds().getPosition()));

			batArray.erase(batArray.begin() + j);
			return true;
		}
	}
	//Return false if no intersection found
	return false;
}

bool Gun::bulletCritterCollision(const sf::FloatRect& bulletBounds, std::vector<std::unique_ptr<Critter>>& critterArray)
{
	/* Checks if bullet kills the critter
	*  Loops through all the critters and checks if the bullet hit (intersects) the critter's bounds
	*  If any critter is hit, critter's health is decreased by 1 unit
	*  Reward widget is created at the position of critter's death if critter dies (health reaches zero)
	*  Reward widget (HealthUpHeart, GunLevelPointsTriangle is randomly selected using srand function
	*  @return true if critter is hit else false
	*/
	for (int j = 0; j < critterArray.size(); j++)
	{
		//If player hit the enemy, delete the enemy
		if (bulletBounds.intersects(critterArray[j]->getBounds()))
		{
			//If critter's health is zero, delete critter
			if (!critterArray[j]->updateHealth(-1))
			{
				//33% chance for health up reward and 67% chance for gun level points reward
				int selector = rand() % 1;
				if (selector == 1)
					m_healthUpArray.emplace_back(HealthUpHeart(critterArray[j]->getBounds().getPosition()));
				else
				{
					m_gunLevelPointsArray.emplace_back(GunLevelPointsTriangle(critterArray[j]->getBounds().getPosition()));
					m_gunLevelPointsArray.emplace_back(GunLevelPointsTriangle(critterArray[j]->getBounds().getPosition()));
				}
				critterArray.erase(critterArray.begin() + j);
			}
			return true;
		}
	}
	//Return false if no intersection is found
	return false;
}

void Gun::updateBulletPositionAndCollision(std::vector<std::unique_ptr<Bat>>& batArray, std::vector<std::unique_ptr<Critter>>& critterArray)
{
	/*
	* Updates bullet's position (distance travelled)
	* Deletes bullet if out of range (distance travelled greater than range)
	* Deletes bullet if colliding with wall
	* Deletes bullet that hits the enemy
	*/

	if (m_gunLevel == 1)
	{
		int i = 0;
		while (i < m_bulletsLev1.size())
		{
			auto& bullet = m_bulletsLev1[i];
			float distanceTravelled = bullet.fireDirection * m_bulletVelocity;

			bullet.bulletBounds.left += distanceTravelled;
			bullet.distanceTravelled += distanceTravelled;

			sf::FloatRect& bulletBounds = bullet.bulletBounds;
			if (std::abs(bullet.distanceTravelled) > bullet.range) //Bullet out of range
			{
				m_bulletsLev1.erase(m_bulletsLev1.begin() + i);
			}
			else if (bulletWallCollision(bulletBounds, bulletBounds.left + bulletBounds.width, bulletBounds.top)) //Bullet collision with wall
			{
				m_bulletsLev1.erase(m_bulletsLev1.begin() + i);
			}
			else if (bulletBatCollision(bulletBounds, batArray)) //If bats are present
			{
				m_bulletsLev1.erase(m_bulletsLev1.begin() + i);
			}
			else if (bulletCritterCollision(bulletBounds, critterArray)) //If bats are present
			{
				m_bulletsLev1.erase(m_bulletsLev1.begin() + i);
			}
			else
				i++;
		}
	}
	else if (m_gunLevel == 2)
	{
		int i = 0;
		while (i < m_bulletsLev2.size())
		{
			auto& bullet = m_bulletsLev2[i];
			float distanceTravelled = bullet.fireDirection * m_bulletVelocity;

			bullet.bulletBounds.left += distanceTravelled;
			bullet.distanceTravelled += distanceTravelled;

			sf::FloatRect& bulletBounds = bullet.bulletBounds;
			if (std::abs(bullet.distanceTravelled) > bullet.range) //Bullet out of range
			{
				m_bulletsLev2.erase(m_bulletsLev2.begin() + i);
			}
			else if (bulletWallCollision(bulletBounds, bulletBounds.left + bulletBounds.width, bulletBounds.top)) //Bullet collision with wall
			{
				m_bulletsLev2.erase(m_bulletsLev2.begin() + i);
			}
			else if (bulletBatCollision(bulletBounds, batArray)) //If bats are present
			{
				m_bulletsLev2.erase(m_bulletsLev2.begin() + i);
			}
			else if (bulletCritterCollision(bulletBounds, critterArray)) //If bats are present
			{
				m_bulletsLev2.erase(m_bulletsLev2.begin() + i);
			}
			else
				i++;
		}
	}
	else
	{
		int i = 0;
		while (i < m_bulletsLev3.size())
		{
			auto& bullet = m_bulletsLev3[i];
			float distanceTravelled = bullet.fireDirection * m_bulletVelocity;

			bullet.bulletBounds.left += distanceTravelled;
			bullet.distanceTravelled += distanceTravelled;

			sf::FloatRect& bulletBounds = bullet.bulletBounds;
			if (std::abs(bullet.distanceTravelled) > bullet.range) //Bullet out of range
			{
				m_bulletsLev3.erase(m_bulletsLev3.begin() + i);
			}
			else if (bulletWallCollision(bulletBounds, bulletBounds.left + bulletBounds.width, bulletBounds.top)) //Bullet collision with wall
			{
				m_bulletsLev3.erase(m_bulletsLev3.begin() + i);
			}
			else if (bulletBatCollision(bulletBounds, batArray)) //If bats are present
			{
				m_bulletsLev3.erase(m_bulletsLev3.begin() + i);
			}
			else if (bulletCritterCollision(bulletBounds, critterArray)) //If bats are present
			{
				m_bulletsLev3.erase(m_bulletsLev3.begin() + i);
			}
			else
				i++;
		}
	}
}

void Gun::updatePlayerRewards(Player& player)
{
	/* Updates player's rewards 
	 * Increases the health by 1 unit if player collects (intersects with reward's bounds) the health reward
	 * Increases gun level points by 1 unit if player collects (intersects with reward's bounds) the gun level points reward
	 */

	int i = 0;
	while (i < m_healthUpArray.size())
	{
		if (m_healthUpArray[i].getBounds().intersects(player.getHitbox()))
		{
			player.updateHP(1);
			m_healthUpArray.erase(m_healthUpArray.begin() + i);
		}
		else
			i++;
	}

	i = 0;
	while (i < m_gunLevelPointsArray.size())
	{
		if (m_gunLevelPointsArray[i].getBounds().intersects(player.getHitbox()))
		{
			if (m_gunLevelPoints < 5)
				m_gunLevelPoints += 1;
			m_gunLevelPointsArray.erase(m_gunLevelPointsArray.begin() + i);
		}
		else
			i++;
	}
}

void Gun::updateFiringKey()
{
	/* Sets m_heldLSHIFT to false if LSHIFT key is released */
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		m_heldLSHIFT = false;
}

//Accessors
const std::pair<int, int> Gun::getGunLevelInfo() const
{
	/*@return Gun level points and gun level */
	return std::make_pair(m_gunLevelPoints, m_gunLevel);
}

void Gun::update(Player& player, std::vector<std::unique_ptr<Bat>>& batArray,
						std::vector<std::unique_ptr<Critter>>& critterArray)

	/* Updates gun position (relative to player's position) 
	*  Updates fire (fires if player has pressed LSHIFT key)
	*  Updates firing key (LSHIFT key), sets m_heldLSHIFT to false if the key is released
	*  Updates bullets position and collision (with wall or enemy)
	*  Updates player rewards (Increase player health or increase gun level points)
	*/
{
	updateGunPosition(player);
	updateFire(player);
	updateFiringKey();
	updateBulletPositionAndCollision(batArray, critterArray);
	updatePlayerRewards(player);
	updateGunLevelPoints();

}

void Gun::renderGun(sf::RenderTarget* target)
{
	/* Renders gun */
	target->draw(m_gunSpriteSheet);
}

void Gun::renderBullets(sf::RenderTarget* target)
{
	/* Renders bullet according to it's level */
	if (m_gunLevel == 1)
	{
		m_bulletSpriteSheet.setTextureRect(m_bulletLevel1Rect);
		for (auto& bullet : m_bulletsLev1)
		{
			m_bulletSpriteSheet.setPosition(bullet.bulletBounds.getPosition());
			target->draw(m_bulletSpriteSheet);
		}
	}
	else if (m_gunLevel == 2)
	{
		m_bulletSpriteSheet.setTextureRect(m_bulletLevel2Rect);
		for (auto& bullet : m_bulletsLev2)
		{
			m_bulletSpriteSheet.setPosition(bullet.bulletBounds.getPosition());
			target->draw(m_bulletSpriteSheet);
		}
	}
	else
	{
		m_bulletSpriteSheet.setTextureRect(m_bulletLevel3Rect);
		for (auto& bullet : m_bulletsLev3)
		{
			m_bulletSpriteSheet.setPosition(bullet.bulletBounds.getPosition());
			target->draw(m_bulletSpriteSheet);
		}
	}
}

void Gun::renderRewards(sf::RenderTarget* target)
{
	/* Renders player's reward HealthUpHeart and GunLevelPointTriangle*/
	for (auto& healthUp : m_healthUpArray)
	{
		healthUp.render(target);
	}
	for (auto& gunLevelPoints : m_gunLevelPointsArray)
	{
		gunLevelPoints.render(target);
	}
}

void Gun::render(sf::RenderTarget* target)
{
	/* Call rendering functions */
	renderBullets(target);
	renderGun(target);
	renderRewards(target);
}