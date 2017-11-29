#pragma once
#include<iostream>
#include<FreeImage.h>
#include<GL/glew.h> //dont switch these
#include<GLFW/glfw3.h>//dont switch these
#include<vector>
#include<glm/glm.hpp>

#include<string>
#include <fstream>
#include <ctime>
class timer
{
private:
	clock_t cur, prev;
public:
	float t;
	float dt;
	float fps;
	timer();
	~timer();
	void update();
};

