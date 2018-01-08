//
//  sceneTest001.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 28/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "sceneTest002.hpp"

void sceneTest002::load()
{
	Scene * scene = new sceneTest002();
	scene->init();

	GameObj->addScene(scene);
}

void sceneTest002::init()
{
	//Load and compile shader
	ShaderProgram * prog = new ShaderProgram("triangle.vs.glsl", "triangle.fs.glsl");

	m_sceneID = 1; // ??????

	//Load level
	rId levelID = GameObj->ressourcesEngine->loadAsset("level01.txt", LEVEL);
	m_level = *GameObj->ressourcesEngine->getAsset(levelID);

	//Generate Sphere
	m_sphere = GameObj->ressourcesEngine->genSphere(1, 32, 32);
	m_sphere->generate(PACMAN_M);
	m_sphere->setProgram(prog);
	m_sphere->getCursor()->scale(.5f, .5f, .5f)->rotate(25, 1, 1, 1);

	std::cout << "loaded" << std::endl;
}

void sceneTest002::execute()
{
	//std::cout << "executed" << std::endl;
}

void sceneTest002::render()
{
	m_sphere->getCursor()->rotate(.01, 0, 0, 1);
	GameObj->renderEngine->render(m_sphere, m_sphere->getCursor());
	check_gl_error();

	//std::cout << "rendered" << std::endl;
}
