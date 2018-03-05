#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <string>
#include "Texture.h"

using namespace std;

class ResourceManager
{
private:
	map <string, Texture*> textures_;

public:
	ResourceManager();
	~ResourceManager();
};

#endif /* RESOURCEMANAGER_H_ */