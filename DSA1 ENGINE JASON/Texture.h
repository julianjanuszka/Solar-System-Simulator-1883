#pragma once
#include<iostream>

#include<GL/glew.h> //dont switch these
#include<GLFW/glfw3.h>//dont switch these
#include<vector>
#include<glm/glm.hpp>

#include<string>
#include <fstream>
#include<FreeImage.h>
class Texture
{
public:
	unsigned int textureID;
	char* filename;
	Texture();
	~Texture();
	void use();
	void load(std::string textureloc);

};

