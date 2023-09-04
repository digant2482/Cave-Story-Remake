#pragma once
class GunLevelPointsTriangle
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void initSprite();
public:
	GunLevelPointsTriangle(sf::Vector2f position);

	//Accessors
	const sf::FloatRect getBounds() const;

	void render(sf::RenderTarget* target);
};