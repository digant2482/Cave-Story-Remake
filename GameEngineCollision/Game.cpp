#include "stdafx.h"
#include "Game.h"

//Initializers
void Game::initWindow()
{
	/* Utility : initializes window (game screen) & sets frame rate */
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Cave Story", sf::Style::Titlebar | sf::Style::Close);
	m_window->setFramerateLimit(60);
}

void Game::initPlayer()
{
	m_player.setPosition(500, 270);
	m_playerHasGun = false;
}

void Game::initEnemies()
{
	m_bat.setPosition(360, 280);
	m_critter.setPosition(400, 400);
}

//Constructor / Destructor
Game::Game()
{
	initWindow();
	initPlayer();
	initEnemies();
}

Game::~Game()
{
	delete m_window;
}

//Functions
void Game::run()
{
	while (m_window->isOpen())
	{
		windowPollEvents();

		gameUpdate();

		gameRender();
	}
}

void Game::windowPollEvents()
{
	/* Utility : closes the game */
	sf::Event ev;
	while (m_window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			m_window->close();

		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			m_window->close();
	}
}

void Game::gameUpdate()
{
	/* Utility : updates all the parts of game */
	m_player.update();

	m_bat.update(m_player);

	m_critter.update(m_player);

	if (m_playerHasGun)
		m_gun.update(m_player);

	m_hud.update(m_player);
}

void Game::gameRender()
{
	/* Utility : Clears the window before next frame
	- Draws animation to the buffer
	- Displays the buffer
	*/
	m_window->clear();

	m_tilemap.render(m_window);

	if (m_playerHasGun)
		m_gun.render(m_window);

	m_player.render(m_window);

	m_bat.render(m_window);

	m_critter.render(m_window);

	m_hud.render(m_window);

	m_window->display();
}