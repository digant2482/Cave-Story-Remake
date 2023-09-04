#include "stdafx.h"
#include "GunLevelPointsTriangle.h"

void GunLevelPointsTriangle::initSprite()
{
	/* Initializes texture and spritesheet */
	if (!m_texture.loadFromFile("Textures/NpcSym.bmp"))
		std::cout << "ERROR::GunLevelPointsTriangle::INITSPRITE::FAILED TO LOAD TEXTURE" << '\n';
	m_sprite.setScale(2.f, 2.f);
}

GunLevelPointsTriangle::GunLevelPointsTriangle(sf::Vector2f position)
{
	/* Call initializers and sets position of the triangle */
	initSprite();
	m_sprite.setPosition(position);
}

//Accessors
const sf::FloatRect GunLevelPointsTriangle::getBounds() const
{
	/* @return Triangle' bounds */
	return m_sprite.getGlobalBounds();
}

void GunLevelPointsTriangle::render(sf::RenderTarget* target)
{
	/* Renders triangle */
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(19, 35, 10, 10));
	target->draw(m_sprite);
}
