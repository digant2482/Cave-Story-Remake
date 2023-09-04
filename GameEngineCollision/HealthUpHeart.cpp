#include "stdafx.h"
#include "HealthUpHeart.h"

void HealthUpHeart::initSprite()
{
	/* Initializes texture and spritesheet */
	if (!m_texture.loadFromFile("Textures/NpcSym.bmp"))
		std::cout << "ERROR::HealthUpHeart::INITSPRITE::FAILED TO LOAD TEXTURE" << '\n';
	m_spriteSheet.setScale(2.f, 2.f);
}

HealthUpHeart::HealthUpHeart(sf::Vector2f position)
{
	/* Call initializers and sets position of the heart */
	initSprite();
	m_spriteSheet.setPosition(position);
}

//Accessors
const sf::FloatRect HealthUpHeart::getBounds() const
{
	/* @return Heart's bounds */
	return m_spriteSheet.getGlobalBounds();
}

void HealthUpHeart::render(sf::RenderTarget* target)
{
	/* Renders heart */
	m_spriteSheet.setTexture(m_texture);
	m_spriteSheet.setTextureRect(sf::IntRect(34, 84, 10, 10));
	target->draw(m_spriteSheet);
}