#include "stdafx.h"
#include "Bat.h"
#define PI 3.14159

void Bat::initSprite()
{
	if (!m_texture.loadFromFile("Textures/Enemies/Enemies Sprite.png"))
		std::cout << "ERROR::ENEMY::BAT::INITSPRITE::SPRITE NOT LOADED" << '\n';
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(2.f, 2.f);
}

void Bat::initOrientation()
{
	m_facingRight = false;
}

void Bat::initAnimation()
{
	m_currentFrame = sf::IntRect(351, 207, 16, 16);
	m_sprite.setTextureRect(m_currentFrame);
	m_animationTimer.restart();
}

Bat::Bat(const float x, const float y)
{
	m_initialPos = sf::Vector2f(x, y);
	m_sprite.setPosition(m_initialPos);
	initSprite();
	initOrientation();
	initAnimation();
}

Bat::Bat()
{
	m_initialPos = sf::Vector2f(270, 300);
	m_sprite.setPosition(m_initialPos);
	initSprite();
	initOrientation();
	initAnimation();
}

void Bat::setPosition(const float x, const float y)
{
	m_initialPos = sf::Vector2f(x, y);
	m_sprite.setPosition(m_initialPos);

}

//Functions
void Bat::updateOrientation(Player& player)
{
	if (player.getPosition().x > m_sprite.getGlobalBounds().left)
		m_facingRight = true;
	else
		m_facingRight = false;
}

void Bat::updateMovement()
{
	static float theta = 0;
	theta += PI / 60;
	if (theta >= 2*PI)
		theta = 0;
;	m_sprite.setPosition(m_initialPos.x, m_initialPos.y + 30 * std::cos(theta));
}

void Bat::updatePlayerEnemyCollision(Player& player)
{
	if (m_sprite.getGlobalBounds().intersects(player.getHitbox()) && !player.isRevivalStateActive())
	{
		player.updateHP(-1);
		player.setRevivalState(true);
	}
}

void Bat::updateAnimation()
{
	if (m_animationTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		if (m_facingRight)
			m_currentFrame.top = 223;
		else
			m_currentFrame.top = 207;

		m_currentFrame.left += 16;
		if (m_currentFrame.left > 383)
			m_currentFrame.left -= 48;
		m_sprite.setTextureRect(m_currentFrame);
		m_animationTimer.restart();
	}
}

void Bat::update(Player& player)
{
	updateOrientation(player);
	updateMovement();
	updatePlayerEnemyCollision(player);
	updateAnimation();
}

void Bat::render(sf::RenderTarget* target)
{
	target->draw(m_sprite);
	//Bounded Box
	/*sf::RectangleShape rect;
	rect.setPosition(m_sprite.getPosition());
	rect.setSize(sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	rect.setOutlineThickness(2.f);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	target->draw(rect);*/
}