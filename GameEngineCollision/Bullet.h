struct BulletLev1
{
	sf::FloatRect bulletBounds;
	int range = 50;
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
	int range = 70;
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
	int range = 100;
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