#pragma once
class HealthUpHeart
{
private:
	sf::Texture m_texture;
	sf::Sprite m_spriteSheet;

	void initSprite();
public:
	HealthUpHeart(sf::Vector2f position);
	
	//Accessors
	const sf::FloatRect getBounds() const;

	void render(sf::RenderTarget* target);
};