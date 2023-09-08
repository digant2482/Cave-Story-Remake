#include "stdafx.h"
#include "Game.h"

//Initializers
void Game::initWindow()
{
	/* Initializes window (game screen) & sets frame rate
	*  Sets pause window to false
	*/
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Cave Story", sf::Style::Titlebar | sf::Style::Close);
	m_window->setFramerateLimit(60);
}

void Game::initStartMenu()
{
	/* Loads start menu (LOAD GAME AND NEW GAME) texture into start menu sprite 
	*  Sets m_newGame (alias for cursor pointing to new game) to false
	*/

	if (!m_startMenuLoadGameTexture.loadFromFile("Textures/Menus/StartMenu Load.png"))
		std::cout << "ERROR::GAME::INITSTARTMENU::FAILED TO LOAD TEXTURE";
	m_startMenuLoadGameSprite.setTexture(m_startMenuLoadGameTexture);

	if (!m_startMenuNewGameTexture.loadFromFile("Textures/Menus/StartMenu New.png"))
		std::cout << "ERROR::GAME::INITSTARTMENU::FAILED TO LOAD TEXTURE";
	m_startMenuNewGameSprite.setTexture(m_startMenuNewGameTexture);

	m_newGame = false;
	m_startMenuSwitchTimer.restart();
}

void Game::initPauseMenu()
{
	/* Loads start menu texture into start menu sprite
	*  Set pause window boolean to false
	*/

	if (!m_pauseMenuTexture.loadFromFile("Textures/Menus/Pause Menu.png"))
		std::cout << "ERROR::GAME::INITSTARTMENU::FAILED TO LOAD TEXTURE";
	m_pauseMenuSprite.setTexture(m_pauseMenuTexture);
	m_pauseWindow = false;
}

//Levels
void Game::loadLevel1()
{
	/* Loads the level
	*  Sets current level
	*  Initializes player position & set player's weapon status 
	*  Set player's current health and max health
	*  Set gun's level points
	*  Clears enemy arrays (In case the game is reset)
	*/

	m_currentLevel = 1;

	//Player's position
	m_player.setPosition(415, 320);
	m_playerHasGun = false;

	// Player's current health and max health
	m_player.setHealth(3, 3);

	// Gun's level points
	m_gun.setGunLevelCurrentPoints(0);

	// Enemy arrays 
	m_batArray.clear();
	m_critterArray.clear();

	m_tilemap.loadLevel1();
}

void Game::loadLevel2()
{
	/* Loads the level
	*  Sets current level
	*  Initializes player position & set player's weapon status
	*  Clears enemy arrays (In case the game is reset)
	*  Instantiates new enemies
	*/

	m_currentLevel = 2;

	//Player position
	m_player.setPosition(80, 560);
	m_playerHasGun = false;

	//Clear enemy arrays 
	m_batArray.clear();
	m_critterArray.clear();

	//Instantiates enemies 
	m_batArray.emplace_back(std::make_unique<Bat>(200, 160));
	m_batArray.emplace_back(std::make_unique<Bat>(360, 160));
	m_batArray.emplace_back(std::make_unique<Bat>(480, 160));

	m_critterArray.emplace_back(std::make_unique<Critter>(360, 480));
	m_critterArray.emplace_back(std::make_unique<Critter>(720, 400));

	m_tilemap.loadLevel2();
}

void Game::loadLevel3()
{
	/* Loads the level
	*  Sets current level
	*  Initializes player position & set player's weapon status
	*  Clears enemy arrays (In case the game is reset)
	*  Instantiates new enemies
	*/

	m_currentLevel = 3;

	//Player position
	m_player.setPosition(80, 120);
	m_playerHasGun = true;

	//Clear enemy arrays 
	m_batArray.clear();
	m_critterArray.clear();

	//Instantiates enemies 
	m_batArray.emplace_back(std::make_unique<Bat>(400, 120));
	m_batArray.emplace_back(std::make_unique<Bat>(520, 200));
	m_batArray.emplace_back(std::make_unique<Bat>(600, 120));
	m_batArray.emplace_back(std::make_unique<Bat>(80, 320));

	m_critterArray.emplace_back(std::make_unique<Critter>(720, 320));
	m_critterArray.emplace_back(std::make_unique<Critter>(40, 440));
	m_critterArray.emplace_back(std::make_unique<Critter>(80, 440));
	m_critterArray.emplace_back(std::make_unique<Critter>(680, 560));
	m_critterArray.emplace_back(std::make_unique<Critter>(720, 560));
	m_critterArray.emplace_back(std::make_unique<Critter>(760, 560));

	m_tilemap.loadLevel3();
}
	
void Game::loadLevel4()
{
	/* Loads the level
	*  Sets current level
	*  Initializes player position & set player's weapon status
	*  Clears enemy arrays (In case the game is reset)
	*  Instantiates new enemies
	*/

	m_currentLevel = 4;

	//Player position
	m_player.setPosition(680, 160);
	m_playerHasGun = true;

	//Clear enemy arrays 
	m_batArray.clear();
	m_critterArray.clear();

	//Instantiates enemies 
	m_batArray.emplace_back(std::make_unique<Bat>(360, 160));
	m_batArray.emplace_back(std::make_unique<Bat>(440, 160));

	m_critterArray.emplace_back(std::make_unique<Critter>(120, 160));
	m_critterArray.emplace_back(std::make_unique<Critter>(40, 320));
	m_critterArray.emplace_back(std::make_unique<Critter>(80, 320));
	m_critterArray.emplace_back(std::make_unique<Critter>(680, 360));
	m_critterArray.emplace_back(std::make_unique<Critter>(360, 440));
	m_critterArray.emplace_back(std::make_unique<Critter>(680, 520));
	m_critterArray.emplace_back(std::make_unique<Critter>(720, 520));
	m_critterArray.emplace_back(std::make_unique<Critter>(80, 560));
	m_critterArray.emplace_back(std::make_unique<Critter>(160, 560));

	m_tilemap.loadLevel4();
}

void Game::loadLevel5()
{
	/* Loads the level
	*  Sets current level
	*  Initializes player position & set player's weapon status
	*  Clears enemy arrays (In case the game is reset)
	*  Instantiates new enemies
	*/

	m_currentLevel = 5;

	//Player position
	m_player.setPosition(720, 120);
	m_playerHasGun = true;

	//Clear enemy arrays 
	m_batArray.clear();
	m_critterArray.clear();

	//Instantiates enemies 
	m_batArray.emplace_back(std::make_unique<Bat>(80, 160));
	m_batArray.emplace_back(std::make_unique<Bat>(160, 160));
	m_batArray.emplace_back(std::make_unique<Bat>(680, 360));
	m_batArray.emplace_back(std::make_unique<Bat>(720, 360));

	m_critterArray.emplace_back(std::make_unique<Critter>(160, 400));
	m_critterArray.emplace_back(std::make_unique<Critter>(40, 520));
	m_critterArray.emplace_back(std::make_unique<Critter>(440, 400));
	m_critterArray.emplace_back(std::make_unique<Critter>(720, 560));
	m_critterArray.emplace_back(std::make_unique<Critter>(680, 560));

	m_tilemap.loadLevel5();
}

void Game::loadLevel6()
{
	/* Loads the level
	*  Sets current level
	*  Initializes player position & set player's weapon status
	*  Clears enemy arrays (In case the game is reset)
	*  Instantiates new enemies
	*/	
	m_currentLevel = 6;

	//Player position
	m_player.setPosition(120, 120);
	m_playerHasGun = true;

	//Clear enemy arrays 
	m_batArray.clear();
	m_critterArray.clear();

	//Instantiates enemies 
	m_batArray.emplace_back(std::make_unique<Bat>(480, 160));
	m_batArray.emplace_back(std::make_unique<Bat>(560, 160));

	m_critterArray.emplace_back(std::make_unique<Critter>(600, 400));
	m_critterArray.emplace_back(std::make_unique<Critter>(680, 120));
	m_critterArray.emplace_back(std::make_unique<Critter>(680, 280));
	m_critterArray.emplace_back(std::make_unique<Critter>(760, 280));
	m_critterArray.emplace_back(std::make_unique<Critter>(80, 360));
	m_critterArray.emplace_back(std::make_unique<Critter>(80, 360));
	m_critterArray.emplace_back(std::make_unique<Critter>(120, 360));
	m_critterArray.emplace_back(std::make_unique<Critter>(160, 560));
	m_critterArray.emplace_back(std::make_unique<Critter>(200, 560));
	m_critterArray.emplace_back(std::make_unique<Critter>(240, 560));
	m_critterArray.emplace_back(std::make_unique<Critter>(320, 560));

	m_tilemap.loadLevel6();
}

void Game::loadSavedProgress()
{
	/* Loads previously saved progress 
	*  Loads level 1 if no previously saved progress is found
	*/

	std::ifstream stream("Levels/SavedProgress.txt");

	if (stream.peek() == std::ifstream::traits_type::eof())
	{
		loadLevel1();
		stream.close();
		return;
	}

	stream >> m_currentLevel;
	switch (m_currentLevel)
	{
	case 1:
		loadLevel1();
		break;
	case 2:
		loadLevel2();
		break;
	case 3:
		loadLevel3();
		break;
	case 4:
		loadLevel4();
		break;
	case 5:
		loadLevel5();
		break;
	case 6:
		loadLevel6();
		break;
	}
	int playerCurrentHealth, playerMaxHealth;
	stream >> playerCurrentHealth >> playerMaxHealth;
	m_player.setHealth(playerCurrentHealth, playerMaxHealth);

	int gunLevelCurrentPoints;
	stream >> gunLevelCurrentPoints;
	m_gun.setGunLevelCurrentPoints(gunLevelCurrentPoints);
	stream.close();
}

//Constructor / Destructor
Game::Game()
{
	initWindow();
	initStartMenu();
	initPauseMenu();
	loadLevel1();
}

Game::~Game()
{
	delete m_window;
}

//Functions
void Game::run()
{
	/* While start menu is running render start menu*/
	while (!gameUpdateStartMenu())
	{
		gameRenderStartMenu();
	}

	/* Runs game loop if not in pause window mode */
	while (m_window->isOpen())
	{
		windowPollEvents();

		if (!m_pauseWindow)
		{
			gameUpdate();
			gameRender();
		}
		else
		{
			gameUpdatePauseMenu();
			gameRenderPauseMenu();
		}
	}
}

void Game::saveProgress()
{
	/* Saves level's progress */
	if (Tilemap::getSaveDiskTileBounds().intersects(m_player.getHitbox()))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			std::ofstream stream("Levels/SavedProgress.txt");
			stream << m_currentLevel << " ";
			stream << m_player.getHealth().first << " " << m_player.getHealth().second << " ";
			stream << m_gun.getGunLevelInfo().first;
			stream.close();
		}
	}
}

void Game::exitLevel()
{
	/* Exits current level 
	*  Initializes next level
	*/
	if (m_tilemap.getLevelExitTile().intersects(m_player.getHitbox()))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (m_currentLevel == 1)
				loadLevel2();
			else if (m_currentLevel == 2)
				loadLevel3();
			else if (m_currentLevel == 3)
				loadLevel4();
			else if (m_currentLevel == 4)
				loadLevel5();
			else if (m_currentLevel == 5)
				loadLevel6();
		}
	}
}

void Game::windowPollEvents()
{
	/* Closes the game
	*  Pauses the game
	*  Restarts pause menu timer  
	*/

	sf::Event ev;
	while (m_window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			m_window->close();

		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
		{
			m_pauseWindow = true;
			m_pauseWindowTimer.restart();
		}
	}
}

bool Game::gameUpdateStartMenu()
{
	/* Moves player's graphic against new game or load game text
	*  @return true is selection is made (Between new game and load game) */

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_window->close();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_startMenuSwitchTimer.getElapsedTime().asSeconds() > 0.2f)
	{
		m_newGame = !m_newGame;
		m_startMenuSwitchTimer.restart();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (m_newGame)
			return true;
		else
		{
			loadSavedProgress();
			return true;
		}
		
	}
	return false;
}

void Game::gameRenderStartMenu()
{
	/* Renders quote (protagonists) image against new game or load game section */

	m_window->clear();
	if (m_newGame)
		m_window->draw(m_startMenuNewGameSprite);
	else
		m_window->draw(m_startMenuLoadGameSprite);

	m_window->display();
}

void Game::gameUpdate()
{
	/* Updates movement, collision, death, and more events for all the characters of the game 
	*  Restarts the game from previous checkpoint if player health hits zero
	*  Saves the game's progress when player is on save disk tile
	*  Exits the current level and enters new level if prompted
	*/
	m_player.update();

	if (m_player.getHealth().first == 0)
	{
		loadSavedProgress();
		return;
	}

	for (auto& bat : m_batArray)
		bat->update(m_player);

	for (auto& critter : m_critterArray)
		critter->update(m_player);

	if (m_playerHasGun)
		m_gun.update(m_player, m_batArray, m_critterArray);

	m_hud.update(m_player, m_gun);

	saveProgress();

	exitLevel();
}

void Game::gameRender()
{
   /* Clears the window before next frame
	* Renders animation to the buffer
	* Displays the buffer */

	m_window->clear();

	m_tilemap.render(m_window, m_player);

	if (m_playerHasGun)
		m_gun.render(m_window);

	m_player.render(m_window);

	for (auto& bat : m_batArray)
		bat->render(m_window);

	for (auto& critter : m_critterArray)
		critter->render(m_window);

	m_hud.render(m_window);

	m_window->display();
}

void Game::gameUpdatePauseMenu()
{
	/* Resumes the game if F1 is pressed
	*  Restarts the game if F2 is pressed
	*  Exits the game if Escape key is held
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		m_pauseWindow = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		loadLevel1();
		m_pauseWindow = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (m_pauseWindowTimer.getElapsedTime().asSeconds() > 0.2f)
		{
			m_window->close();
		}
	}
}

void Game::gameRenderPauseMenu()
{
	/* Clears window 
	*  Renders pause menu sprite on window
	*/

	m_window->clear();
	m_window->draw(m_pauseMenuSprite);
	m_window->display();
}