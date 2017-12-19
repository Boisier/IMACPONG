//
//  ImageImporter.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "../../../main.hpp"

Asset * ImageImporter::getAsset(std::string path)
{
	//Load image
	SDL_Surface * imageSurface = IMG_Load(path.c_str());

	//Is image loaded ?
	if(!imageSurface)
		throw std::runtime_error("Could not load " + path + " : " + std::string(IMG_GetError()));


	//Image is ok, let's extract informations
	uint i_height = imageSurface->w;
	uint i_width = imageSurface->h;

	GLenum imageMode;
	//

	return nullptr;
}

ImageImporter::~ImageImporter()
{

}
