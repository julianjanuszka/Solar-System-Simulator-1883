#pragma once
#include<iostream>
#include<FreeImage.h>
#include<GL/glew.h> //dont switch these
#include<GLFW/glfw3.h>//dont switch these
#include<vector>
#include<glm/glm.hpp>
#include<string>
#include <fstream>
#include<glm/gtx/transform.hpp>
#include<glm/gtx/euler_angles.hpp>
#include<glm/gtc/constants.hpp>
#include <ctime>
#include<fstream>
#include <sstream>
#include "Texture.h"
#include<math.h>



class Model
{
private:
unsigned int vertCount;
	GLuint vertArr;
	

public:
	
	Model();
	~Model();
	bool Buffer(std::string objfile);
	void render();
	float maxx = 0;
	float maxy = 0;
	float maxz = 0;
	float minx = 0;
	float miny = 0;
	float minz = 0;
	float maxradius = 0;
};
struct Vertex {
	glm::vec3 locs;
	glm::vec2 uvs;
	glm::vec3 norms;
};
struct VertInd {
	unsigned int locInd, uvInd, normInd;
};

