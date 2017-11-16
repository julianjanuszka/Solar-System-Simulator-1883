#pragma once
#include<iostream>
#include<FreeImage.h>
#include<GL/glew.h> //dont switch these
#include<GLFW/glfw3.h>//dont switch these
#include<vector>
#include<glm/glm.hpp>

#include<string>
#include <fstream>
class Object
{
public:
	std::string tag;
	Object();
	virtual ~Object();
	virtual  void update();
	void render();
};

