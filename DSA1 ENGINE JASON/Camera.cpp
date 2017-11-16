#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::upload()
{
	glUniformMatrix4fv(6, 1, GL_FALSE, &cammat[0][0]);
	float camloc[3] = { loc.x,loc.y,loc.z };
	glUniform3fv(8, 1, camloc);
}

void Camera::start()
{
	worldview = glm::mat4();
}

void Camera::cameraturn(GLFWwindow* window)
{
	float sens = .005;
	int w = 800, h = 600;
	glfwGetWindowSize(window, &w, &h);
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	//rotmat
	rotang.y -= sens * (x - w * .5f); // Yaw
	rotang.x -= sens * (y - h * .5f); // Pitch
	rotang.x = glm::clamp(rotang.x, -.5f * 3.14f, .5f * 3.14f);
	glfwSetCursorPos(window, w * .5f, h * .5f);
	rotmat = (glm::mat3)glm::yawPitchRoll(rotang.y, rotang.x, rotang.z);

	
	//look at matrix
	glm::vec3 eye = loc;
	glm::vec3 center = eye + rotmat * glm::vec3(0, 0, -1);
	glm::vec3 up = rotmat * glm::vec3(0, 1, 0);
	glm::mat4 lookAtMat = glm::lookAt(eye, center, up);

	//perspective mat
	float zoom = 1.f;
	float fovy = 3.14159f * .4f / zoom;
	float aspect = (float)w / (float)h;
	float zNear = .01f;
	float zFar = 1000.f;
	glm::mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	//end camera mat
	cammat = perspectiveMat*lookAtMat;

}

void Camera::move(float deltat, GLFWwindow* window)
{
	glm::vec3 dir;
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(rotang.y,rotang.x,rotang.z);
	//camera left and right
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		dir += R*glm::vec3(-1, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		dir += R*glm::vec3(1, 0, 0);
	}
	//camera up and down
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
	{
		dir += R*glm::vec3(0, -10, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE)) 
	{
		dir += R*glm::vec3(0, 1, 0);
	}
	//camera foward and back
	if (glfwGetKey(window, GLFW_KEY_W)) 
	{
		dir += R*glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(window, GLFW_KEY_S)) 
	{
		dir += R*glm::vec3(0, 0, 1);
	}

	if (dir != (glm::vec3()))
	{
		dir = glm::normalize(dir);
	}
	
	loc += dir*deltat*5.0f;
}

