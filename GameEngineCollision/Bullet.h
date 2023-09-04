/* Bullets are categorised into three levels corresponding to the level of gun
* 
*  Bullet struct has:
*  FloatRect (Rectangle bounding the bullet)
*  Range (distance the bullet can travel before being deleted)
*  Distance travelled (distance covered by the bullet)
*  Fire direction (Direction in which bullet was fired left (-1), right (1))
*/

struct BulletLev1
{
	sf::FloatRect bulletBounds;
	int range = 70;
	int distanceTravelled = 0;
	int fireDirection;
	BulletLev1(const float x, const float y, const int fireDirection) : fireDirection(fireDirection)
	{
		bulletBounds.left = x;
		bulletBounds.top = y;
		bulletBounds.width = 16;
		bulletBounds.height = 1;
	}
};

struct BulletLev2
{
	sf::FloatRect bulletBounds;
	int range = 90;
	int distanceTravelled = 0;
	int fireDirection;
	BulletLev2(const float x, const float y, const int fireDirection) : fireDirection(fireDirection)
	{
		bulletBounds.left = x;
		bulletBounds.top = y;
		bulletBounds.width = 16;
		bulletBounds.height = 3;
	}

};

struct BulletLev3
{
	sf::FloatRect bulletBounds;
	int range = 120;
	int distanceTravelled = 0;
	int fireDirection;
	BulletLev3(const float x, const float y, const int fireDirection) : fireDirection(fireDirection)
	{
		bulletBounds.left = x;
		bulletBounds.top = y;
		bulletBounds.width = 16;
		bulletBounds.height = 8;
	}
};