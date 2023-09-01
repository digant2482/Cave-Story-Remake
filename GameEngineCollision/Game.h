#pragma once

#include "Player.h"		//Player
#include "Gun.h"        //Player Weapon
#include "Bat.h"		//Enemy
#include "Tilemap.h"	//Map
#include "Critter.h"	//Enemy
#include "HUD.h"		//Heads-up Display

class Game
{
private:
	//Window
	sf::RenderWindow* m_window;

	//HUD
	HUD m_hud;

	//Tilemap
	Tilemap m_tilemap;  //Only to intialize tilemap

	//Player
	Player m_player;
	bool m_playerHasGun;

	//Player Weapon
	Gun m_gun;

	//Enemies
	Bat m_bat;
	Critter m_critter;

	//Initializers
	void initWindow();
	void initPlayer();
	void initEnemies();

	void windowPollEvents();

	//Player/Wall Collision
	void gameUpdate();
	void gameRender();
public:
	Game();
	~Game();

	//Functions
	void run();
};