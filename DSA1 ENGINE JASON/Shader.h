#pragma once
#include<iostream>
#include<FreeImage.h>
#include<GL/glew.h> //dont switch these
#include<GLFW/glfw3.h>//dont switch these
#include<vector>
#include<glm/glm.hpp>

#include<string>
#include <fstream>
using std::string;
class Shader
{
public:
	
	GLuint program, vprogram, fprogram;
	string filenamev = "shaders/vShader.glsl";
	string filenamef = "shaders/fShader.glsl";
	Shader();
	virtual ~Shader();
	bool load();//load shaders
	char* readBinaryFile(std::string filename);
	bool compile(string filenname,GLenum shadertype);//helpermethod used by load
	void use();//use them
	void unload();//deletes them
};

