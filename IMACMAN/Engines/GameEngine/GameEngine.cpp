//
//  GameEngine.cpp
//  IMACMAN
//
//  Created by Laurie Greinert on 22/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "GameEngine.hpp"

bool GameEngine::m_instanciated = false;

void GameEngine::instanciate()
{
	if(m_instanciated)
		return;
	
	GameObj->gameEngine = new GameEngine();
	
	m_instanciated = true;
}

void GameEngine::reset() {
	if (!m_instanciated) {
		delete GameObj->gameEngine;
		m_instanciated = false;
	}
}

void GameEngine::executeScenes()
{
	//Update events
	parseEvents();

	//get all scenes
	std::vector<Scene *> scenes = GameObj->getScenes();

	//Execute all scenes
	for(std::vector<Scene *>::iterator it = scenes.begin(); it != scenes.end(); ++it)
	{
		if((*it)->isEnabled()) {
			(*it)->execute();
		}
	}
}

void GameEngine::renderScenes()
{
	/*Clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//get all scenes
	std::vector<Scene *> scenes = GameObj->getScenes();
	
	//Render all scenes
	for(std::vector<Scene *>::iterator it = scenes.begin(); it != scenes.end(); ++it)
	{
		if((*it)->isEnabled()) {
			(*it)->render();
		}
	}

	//Swap buffers
	SDL_GL_SwapWindow(GameObj->mainWindow);
}

void GameEngine::parseEvents()
{
	SDL_Event event;
	bool newVal;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			return GameObj->endGame();

		if(event.type != SDL_KEYUP && event.type != SDL_KEYDOWN)
			continue;

		if(event.type == SDL_KEYUP)
			newVal = false;
		else
			newVal = true;

		switch(event.key.keysym.sym)
		{
			case     SDLK_a:     m_keys.A = newVal; break;
			case     SDLK_b:     m_keys.B = newVal; break;
			case     SDLK_c:     m_keys.C = newVal; break;
			case     SDLK_d:     m_keys.RIGHT = newVal; break;
			case     SDLK_e:     m_keys.E = newVal; break;
			case     SDLK_f:     m_keys.F = newVal; break;
			case     SDLK_g:     m_keys.G = newVal; break;
			case     SDLK_h:     m_keys.H = newVal; break;
			case     SDLK_i:     m_keys.I = newVal; break;
			case     SDLK_j:     m_keys.J = newVal; break;
			case     SDLK_k:     m_keys.K = newVal; break;
			case     SDLK_l:     m_keys.L = newVal; break;
			case     SDLK_m:     m_keys.M = newVal; break;
			case     SDLK_n:     m_keys.N = newVal; break;
			case     SDLK_o:     m_keys.O = newVal; break;
			case     SDLK_p:     m_keys.P = newVal; break;
			case     SDLK_q:     m_keys.LEFT = newVal; break;
			case     SDLK_r:     m_keys.R = newVal; break;
			case     SDLK_s:     m_keys.DOWN = newVal; break;
			case     SDLK_t:     m_keys.T = newVal; break;
			case     SDLK_u:     m_keys.U = newVal; break;
			case     SDLK_v:     m_keys.V = newVal; break;
			case     SDLK_w:     m_keys.W = newVal; break;
			case     SDLK_x:     m_keys.X = newVal; break;
			case     SDLK_y:     m_keys.Y = newVal; break;
			case     SDLK_z:     m_keys.UP = newVal; break;
			case    SDLK_UP:    m_keys.UP = newVal; break;
			case  SDLK_DOWN:  m_keys.DOWN = newVal; break;
			case  SDLK_LEFT:  m_keys.LEFT = newVal; break;
			case SDLK_RIGHT: m_keys.RIGHT = newVal; break;
			case SDLK_ESCAPE:  m_keys.ESC = newVal; break;
			case SDLK_BACKSPACE: m_keys.BACKSPACE = newVal; break;
			case SDLK_RETURN: m_keys.ENTER = newVal; break;

		}
	}
}

void GameEngine::loadLevel(Level * level){
	m_level = new Grid(
		level->getWidth(),
		level->getHeight(),
		level->getLevelGrid()
	);
	
	m_pacman = reinterpret_cast<Pacman *>(m_level->getItem(ITEM_SYNTAX::PACMAN));

	m_Blinky = reinterpret_cast<Ghost *>(m_level->getItem(ITEM_SYNTAX::BLINKY));
	m_Pinky = reinterpret_cast<Ghost *>(m_level->getItem(ITEM_SYNTAX::PINKY));
	m_Inky = reinterpret_cast<Ghost *>(m_level->getItem(ITEM_SYNTAX::INKY));
	m_Clyde = reinterpret_cast<Ghost *>(m_level->getItem(ITEM_SYNTAX::CLYDE));
	m_fruit = reinterpret_cast<Fruit *>(m_level->getItem(ITEM_SYNTAX::FRUIT));
}

Grid * GameEngine::getGrid()
{
	return m_level;
}

void GameEngine::displayLevel()
{
	m_level->displayGrid();
}

void GameEngine::displayInfo()
{
	std::cout
		<< "LIVES: " << m_pacman->getLives()
		<< "\tSCORE: " << m_pacman->getRealScore()
		<< "\tSUPER-TIME: " << m_pacman->getSuperCounter();

	std::cout << std::endl;
}

void GameEngine::manageSpecialMode() {
	m_pacman->updateSuperCounter(-1);
	m_Blinky->updateDeathCounter(-1);
	m_Pinky->updateDeathCounter(-1);
	m_Inky->updateDeathCounter(-1);
	m_Clyde->updateDeathCounter(-1);
	m_fruit->updatePopCounter(-1);
}

void GameEngine::inGameChecks()
{
	//Update all counters
	manageSpecialMode();

	//Check VICTORY / DEFEAT conditions
	if (m_pacman->getLives() <= 0)
	{
		//TODO change Scene to GameOver
		//std::cout << "gameOver" << std::endl;

		std::vector<Scene *> scenes = GameObj->getScenes();
		for(Scene * scene : scenes)
			GameObj->removeScene(scene);

		gameOverScene::load();
		return;
	}

	//Check wether there is still one pack gum or not
	if (!m_level->checkItemsExist({ITEM_SYNTAX::PAC_GUM, ITEM_SYNTAX::SUPER_PAC_GUM}))
	{
		//TODO change Scene to Victory
		//std::cout << "Victory" << std::endl;

		std::vector<Scene *> scenes = GameObj->getScenes();
		for(Scene * scene : scenes)
			GameObj->removeScene(scene);

		victoryScene::load();
		return;
	}
}
