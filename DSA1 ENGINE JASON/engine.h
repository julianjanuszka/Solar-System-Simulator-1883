#pragma once
#include<iostream>
#include<FreeImage.h>
#include<GL/glew.h> //dont switch these
#include<GLFW/glfw3.h>//dont switch these
#include<vector>
#include<glm/glm.hpp>

#include<string>
#include <fstream>
#include "timer.h"
class engine
{
public:
	timer t;
	void start();
	void stop();
	void update();
private:
	engine();
	~engine();
};

