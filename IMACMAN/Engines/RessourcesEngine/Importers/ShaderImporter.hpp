//
//  ShaderImporter.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef ShaderImporter_hpp
#define ShaderImporter_hpp

//Forward declaration
class Asset;

#include "Importer.hpp"

class ShaderImporter: public Importer
{
public:
	Asset * getAsset(std::string path);

private:

};

#endif /* ShaderImporter_hpp */
