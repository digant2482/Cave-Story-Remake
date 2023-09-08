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
	Tilemap m_tilemap;  

	//Level
	int m_currentLevel; //Current level of the game (1-6)

	//Start Menu
	sf::Texture m_startMenuLoadGameTexture;
	sf::Texture m_startMenuNewGameTexture;
	sf::Sprite m_startMenuLoadGameSprite;
	sf::Sprite m_startMenuNewGameSprite;
	bool m_newGame;
	sf::Clock m_startMenuSwitchTimer;

	//Pause menu
	sf::Texture m_pauseMenuTexture;
	sf::Sprite m_pauseMenuSprite;
	bool m_pauseWindow; 
	sf::Clock m_pauseWindowTimer;

	//Player
	Player m_player;
	bool m_playerHasGun;

	//Player Weapon
	Gun m_gun;

	//Enemies
	std::vector<std::unique_ptr<Bat>> m_batArray;
	std::vector<std::unique_ptr<Critter>> m_critterArray;

	//Initializers
	void initWindow();
	void initStartMenu();
	void initPauseMenu();

	//Updates Game
	void windowPollEvents();

	bool gameUpdateStartMenu();
	void gameRenderStartMenu();
	void gameUpdate();
	void gameRender();
	void gameUpdatePauseMenu();
	void gameRenderPauseMenu();

	//Levels
	void loadLevel1();
	void loadLevel2();
	void loadLevel3();
	void loadLevel4();
	void loadLevel5();
	void loadLevel6();
	void loadSavedProgress();

	void saveProgress();
	void exitLevel();

public:
	Game();
	~Game();

	void run();
};