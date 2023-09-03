#include "stdafx.h"
#include "GunLevelPoints.h"

void GunLevelPoints::initSprite()
{
	if (!m_texture.loadFromFile("Textures/Weapons/NpcSym.bmp"))
		std::cout << "ERROR::GunLevelPoints::INITSPRITE::FAILED TO LOAD TEXTURE" << '\n';
	m_sprite.setScale(2.f, 2.f);
}

GunLevelPoints::GunLevelPoints(sf::Vector2f position)
{
	initSprite();
	m_sprite.setPosition(position);
	m_hitbox.left = position.x;
	m_hitbox.top = position.y;
	m_hitbox.width = 16.f;
	m_hitbox.height = 16.f;
}

//Accessors
const sf::FloatRect& GunLevelPoints::getBounds() const
{
	return m_hitbox;
}

void GunLevelPoints::render(sf::RenderTarget* target)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(19, 35, 10, 10));
	target->draw(m_sprite);
}
