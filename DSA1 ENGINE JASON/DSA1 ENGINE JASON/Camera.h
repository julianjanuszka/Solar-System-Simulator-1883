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
using std::string;
class Camera
{
private: 

public:
	
	glm::vec3 loc= { -10, 0, 0 };
	
	glm::mat3 rotmat;
	glm::vec3 rotang= { 0, 0, 0 };
	glm:: mat4 worldview;
	glm::mat4 cammat;
	Camera();
	~Camera();
	void upload();
	void start();
	void cameraturn(GLFWwindow* window);
	void move(float deltat, GLFWwindow* window);


};

 