#pragma once
class GunLevelPoints
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Sprite sprite;
	sf::FloatRect m_hitbox;

	void initSprite();
public:
	GunLevelPoints(sf::Vector2f position);

	//Accessors
	const sf::FloatRect& getBounds() const;

	void render(sf::RenderTarget* target);
};