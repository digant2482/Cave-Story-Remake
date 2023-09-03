#pragma once
class HealthUp
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::FloatRect m_hitbox;

	void initSprite();
public:
	HealthUp(sf::Vector2f position);
	
	//Accessors
	const sf::FloatRect& getBounds() const;

	void render(sf::RenderTarget* target);
};