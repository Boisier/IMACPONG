//
//  GameObject.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 21/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

//Forward declarations
class GameEngine;
class RessourcesEngine;
class RenderEngine;
class Scene;
class ShaderProgram;

#include "libraries.hpp"
#include "Utils/ShaderProgram.hpp"

class GameObject
{
public:
	//Singleton
	static void instanciate(std::string appPath);

	//Engines
	GameEngine * gameEngine;
	RessourcesEngine * ressourcesEngine;
	RenderEngine * renderEngine;

	//The window, managed by SDL
	SDL_Window * mainWindow;
	float screenWidth;
	float screenHeight;

	inline std::string getAppPath() const { return m_appPath; };

	//Game Object State
	inline bool isRunning() const { return m_running; };
	inline void endGame() { m_running = false; };

	//Scenes Methods
	inline void addScene(Scene * scene) { m_scenes.push_back(scene); };
	std::vector<Scene *> getScenes() const { return m_scenes; };
	void removeScene(Scene * scene);

	//Return a newly generated UUID
	inline boost::uuids::uuid getUUID() { return m_uuidGenerator(); };

	/**
	 Return the default shader program

	 @return A ShaderProgram Object
	 */
	inline ShaderProgram * getDefaultProgram() { return m_defaultProgram; };

	/**
	 Set default shader program

	 @param prog A ShaderProgram
	 */
	inline void setDefaultProgram(ShaderProgram * prog) { m_defaultProgram = prog; };

private:
	//Singleton
	GameObject(std::string appPath):
		m_appPath(appPath) {};
	bool static m_instanciated;

	//Game states
	std::string m_appPath;
	bool m_running = true;

	//Scenes
	std::vector<Scene *> m_scenes;

	//UUID
	boost::uuids::random_generator m_uuidGenerator;

	//default shader
	ShaderProgram * m_defaultProgram;
};

extern GameObject * GameObj;

#endif /* GameObject_hpp */
