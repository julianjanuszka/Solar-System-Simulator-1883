#include<iostream>
#include<FreeImage.h>
#include<GL/glew.h> //dont switch these
#include<GLFW/glfw3.h>//dont switch these
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtx/euler_angles.hpp>
#include<glm/gtc/constants.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include <vector>
#include <random>

//include with <> to get external library
//include wtih "" to use things in our project/we made
/*
SO notes
controls:
wasd, space, and left shift move the camera

arrow keys, numpad0, and right shift move the sun

mouse to look around

R resets and randomizes the locations of everything.

*/
struct collision {
	float radius;
	float lx;
	float ly;
	float lz;
	float sx;
	float sy;
	float sz;
	float lxc;
	float lyc;
	float lzc;
	float sxc;
	float syc;
	float szc;
};
struct rigidbody {
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
};
struct Transform
{

	glm::vec3 location, rotation, size;
	glm::mat4 objworldtransmat;
	rigidbody stuff;
};

struct object {
	Transform trans;
	collision collider;
	std::string texturefileneme;
	std::string modelfilename;
	Texture tex;
	Model mod;
	bool isgrav;
	bool isorbit;
	bool issun;
	bool cancollide;
	bool iscolliding =false;
	std::string name;
	bool isself;
	bool issphere;
	bool isbox;

};


int main() {
	if (glfwInit() == GL_FALSE) 
	{
		return -1;
	}
	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(1000,800, "Jason BauerDSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)
	{
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else 
	{
		glfwTerminate();
		return-1;
	}
	if (glewInit() != GLEW_OK) 
	{
		glfwTerminate();
		return -1;
	}
	
	Shader firstshader = Shader();
	bool loaded = firstshader.load();
	if (loaded) 
	{
		firstshader.use();
	}
	else 
	{
		glfwTerminate();
		std::cin.get();
	}
	glUniform1f(3, (0.4f));

	Camera cam = Camera();
	
	
	//collection of objects
	std::vector<object> objs;

		object newobj1;

		newobj1.trans.location = glm::vec3(-9, 0, -9);
		newobj1.trans.rotation = glm::vec3(5, 0, 0);
		newobj1.trans.size = glm::vec3(.5,.5,.5);
		newobj1.texturefileneme = "Textures/planet2.jpg";
		newobj1.mod = Model();
		newobj1.tex = Texture();
		newobj1.trans.stuff.velocity= glm::vec3(0, 0, 0);
		newobj1.trans.stuff.mass = 2.0f;
		newobj1.trans.stuff.force = glm::vec3(0, 0, 0);
		newobj1.modelfilename = "models/sphere.obj";
		newobj1.mod.Buffer(newobj1.modelfilename);
		newobj1.tex.load(newobj1.texturefileneme);
		newobj1.isgrav = false;
		newobj1.isorbit = true;
		newobj1.issun = false;
		newobj1.cancollide = true;
		newobj1.name = "lava world";
		newobj1.collider.radius = newobj1.mod.maxradius*newobj1.trans.size.x;
		newobj1.collider.lxc = newobj1.mod.maxx*newobj1.trans.size.x;
		newobj1.collider.lyc = newobj1.mod.maxy*newobj1.trans.size.y;
		newobj1.collider.lzc = newobj1.mod.maxz*newobj1.trans.size.z;
		newobj1.collider.sxc = newobj1.mod.minx*newobj1.trans.size.x;
		newobj1.collider.syc = newobj1.mod.miny*newobj1.trans.size.y;
		newobj1.collider.szc = newobj1.mod.minz*newobj1.trans.size.z;
		newobj1.issphere = true;
		newobj1.isbox = false;
		objs.push_back(newobj1);
	
		object newobj2;
		newobj2.trans.location = glm::vec3(0, 0, 0);
		newobj2.trans.rotation = glm::vec3(0, 0, 0);
		newobj2.trans.size = glm::vec3(1.5,1.5, 1.5);
		newobj2.texturefileneme = "Textures/sun.jpg";
		newobj2.mod = Model();
		newobj2.tex = Texture();
		newobj2.trans.stuff.velocity = glm::vec3(0, 0, 0);
		newobj2.trans.stuff.mass = 5.0f;
		newobj2.trans.stuff.force = glm::vec3(0, 0, 0);
		newobj2.modelfilename = "models/sphere.obj";
		newobj2.mod.Buffer(newobj2.modelfilename);
		newobj2.tex.load(newobj2.texturefileneme);
		newobj2.isgrav = false;
		newobj2.isorbit = false;
		newobj2.issun = true;
		newobj2.cancollide = false;
		newobj2.collider.radius = newobj2.mod.maxradius*newobj2.trans.size.x;
		newobj2.collider.lxc = newobj2.mod.maxx*newobj2.trans.size.x;
		newobj2.collider.lyc = newobj2.mod.maxy*newobj2.trans.size.y;
		newobj2.collider.lzc = newobj2.mod.maxz*newobj2.trans.size.z;
		newobj2.collider.sxc = newobj2.mod.minx*newobj2.trans.size.x;
		newobj2.collider.syc = newobj2.mod.miny*newobj2.trans.size.y;
		newobj2.collider.szc = newobj2.mod.minz*newobj2.trans.size.z;
		newobj2.name = "sun";
		newobj2.issphere = true;
		newobj2.isbox =false;
		objs.push_back(newobj2);

		object newobj3;
		newobj3.trans.location = glm::vec3(-5, 0, 7);
		newobj3.trans.rotation = glm::vec3(0, 0, 0);
		newobj3.trans.size = glm::vec3(.3,.3,.3);
		newobj3.texturefileneme = "Textures/planet1.png";
		newobj3.mod = Model();
		newobj3.tex = Texture();
		newobj3.trans.stuff.velocity = glm::vec3(0, 0, 0);
		newobj3.trans.stuff.mass = 3.0f;
		newobj3.trans.stuff.force = glm::vec3(0, 0, 0);
		newobj3.modelfilename = "models/sphere.obj";
		newobj3.mod.Buffer(newobj3.modelfilename);
		newobj3.tex.load(newobj3.texturefileneme);
		newobj3.isgrav = false;
		newobj3.isorbit = true;
		newobj3.issun = false;
		newobj3.cancollide = true;
		newobj3.collider.radius = newobj3.mod.maxradius*newobj3.trans.size.x;
		newobj3.collider.lxc = newobj3.mod.maxx*newobj3.trans.size.x;
		newobj3.collider.lyc = newobj3.mod.maxy*newobj3.trans.size.y;
		newobj3.collider.lzc = newobj3.mod.maxz*newobj3.trans.size.z;
		newobj3.collider.sxc = newobj3.mod.minx*newobj3.trans.size.x;
		newobj3.collider.syc = newobj3.mod.miny*newobj3.trans.size.y;
		newobj3.collider.szc = newobj3.mod.minz*newobj3.trans.size.z;
		newobj3.name = "earth";
		newobj3.issphere = true;
		newobj3.isbox = false;
		objs.push_back(newobj3);

		object newobj4;
		newobj4.trans.location = glm::vec3(10, 0, 0);
		newobj4.trans.rotation = glm::vec3(0, 0, 0);
		newobj4.trans.size = glm::vec3(.75,.75,.75);
		newobj4.texturefileneme = "Textures/Planet3.png";
		newobj4.mod = Model();
		newobj4.tex = Texture();
		newobj4.trans.stuff.velocity = glm::vec3(0, 0, 0);
		newobj4.trans.stuff.mass = 4.0f;
		newobj4.trans.stuff.force = glm::vec3(0, 0, 0);
		newobj4.modelfilename = "models/sphere.obj";
		newobj4.mod.Buffer(newobj4.modelfilename);
		newobj4.tex.load(newobj4.texturefileneme);
		newobj4.isgrav = false;
		newobj4.isorbit = true;
		newobj4.issun = false;
		newobj4.cancollide = true;
		newobj4.collider.radius = newobj4.mod.maxradius*newobj4.trans.size.x;
		newobj4.collider.lxc = newobj4.mod.maxx*newobj4.trans.size.x;
		newobj4.collider.lyc = newobj4.mod.maxy*newobj4.trans.size.y;
		newobj4.collider.lzc = newobj4.mod.maxz*newobj4.trans.size.z;
		newobj4.collider.sxc = newobj4.mod.minx*newobj4.trans.size.x;
		newobj4.collider.syc = newobj4.mod.miny*newobj4.trans.size.y;
		newobj4.collider.szc = newobj4.mod.minz*newobj4.trans.size.z;
		newobj4.name = "metal land";
		newobj4.issphere = true;
		newobj4.isbox = false;
		objs.push_back(newobj4);

		object newobj5;
		newobj5.trans.location = glm::vec3(-10, 0, 5);
		newobj5.trans.rotation = glm::vec3(0, 0, 0);
		newobj5.trans.size = glm::vec3(.75, .75, .75);
		newobj5.texturefileneme = "Textures/planet1.png";
		newobj5.mod = Model();
		newobj5.tex = Texture();
		newobj5.trans.stuff.velocity = glm::vec3(0, 0, 0);
		newobj5.trans.stuff.mass = 4.5f;
		newobj5.trans.stuff.force = glm::vec3(0, 0, 0);
		newobj5.modelfilename = "models/box.obj";
		newobj5.mod.Buffer(newobj5.modelfilename);
		newobj5.tex.load(newobj5.texturefileneme);
		newobj5.isgrav = false;
		newobj5.isorbit = true;
		newobj5.issun = false;
		newobj5.cancollide = true;
		newobj5.collider.radius = newobj5.mod.maxradius*newobj5.trans.size.x;
		newobj5.collider.lxc = newobj5.mod.maxx*newobj5.trans.size.x;
		newobj5.collider.lyc = newobj5.mod.maxy*newobj5.trans.size.y;
		newobj5.collider.lzc = newobj5.mod.maxz*newobj5.trans.size.z;
		newobj5.collider.sxc = newobj5.mod.minx*newobj5.trans.size.x;
		newobj5.collider.syc = newobj5.mod.miny*newobj5.trans.size.y;
		newobj5.collider.szc = newobj5.mod.minz*newobj5.trans.size.z;
		newobj5.name = "box earth";
		newobj5.issphere = false;
		newobj5.isbox = true;
		objs.push_back(newobj5);




	float t0 = 0;	// Prev time
	float t = 0;	// Cur time
	float dt = t - t0;	// Delta time
	

	glEnable(GL_CULL_FACE);
	//set background to purple
	glClearColor(0.0f,0.0f,0.0f, 0.0f);
	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//glEnable(GL_DEPTH_TEXT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::cout << " \n " <<  std::endl;
	glEnable(GL_DEPTH_TEST);
	bool infiloop = false;
	for (object& var : objs)
	{
		
		std::cout << " radius: " << var.collider.radius << std::endl;
	}
	//game loop
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		//update min and maxes
		for (object& var : objs)
		{//mins
			var.collider.sx = var.trans.location.x - var.collider.sxc;
			var.collider.sy = var.trans.location.y - var.collider.syc;
			var.collider.sz = var.trans.location.z - var.collider.szc;
		//maxes
			var.collider.lx = var.trans.location.x + var.collider.lxc;
			var.collider.ly = var.trans.location.y + var.collider.lyc;
			var.collider.lz = var.trans.location.z + var.collider.lzc;
		}
		
		//checkcollisons
		for (object& var : objs)
		{
			var.isself = true;
			//if they are a sphere
			if (var.issphere) 
			{	
				for (object& varinside : objs)
				{
					if (!varinside.isself)
					{
						if (varinside.issphere)
						{
							//sphere collision
							float distbtw = pow((pow(var.trans.location.z - varinside.trans.location.z, 2)) + (pow(var.trans.location.y - varinside.trans.location.y, 2)) + (pow(var.trans.location.x - varinside.trans.location.x, 2)), .5);
							//std::cout << pow(var.trans.location.z - varinside.trans.location.z, 2) + pow(var.trans.location.y - varinside.trans.location.y, 2) + pow(var.trans.location.x - varinside.trans.location.x, 2) << std::endl;
							float raddist = var.collider.radius + varinside.collider.radius;
							if (distbtw < raddist) 
							{
								//std::cout <<var.name<< " collided with " << varinside.name <<" at distance: "<< distbtw<< std::endl;
								if (var.trans.stuff.mass < varinside.trans.stuff.mass && var.cancollide) {
									std::cout << var.name << " collided with " << varinside.name << " at distance: " << distbtw << std::endl;
									var.iscolliding = true;
									var.cancollide = false;
								}
								if (varinside.cancollide && var.trans.stuff.mass > varinside.trans.stuff.mass) {
									std::cout << varinside.name << " collided with " << var.name << " at distance: " << distbtw << std::endl;
									varinside.iscolliding = true;
									varinside.cancollide = false;
								}
							}
						}
						if (varinside.isbox)
						{
							bool colliding = false;
							//sphere to box goes here
							//compute distance^2  from sphere center to nearest point on box
							float distance=0;
							//x
							if (var.trans.location.x < varinside.collider.sx) {
								distance += pow(varinside.collider.sx - var.trans.location.x, 2);
							}
							else if (var.trans.location.x > varinside.collider.lx) {
								distance += pow(var.trans.location.x-varinside.collider.lx, 2);
							}
							else if (var.trans.location.x > varinside.collider.sx &&var.trans.location.x < varinside.collider.lx) {
								distance += 0;
							}
							//y
							if (var.trans.location.y < varinside.collider.sy) {
								distance += pow(varinside.collider.sy - var.trans.location.y, 2);
							}
							else if (var.trans.location.y > varinside.collider.ly) {
								distance += pow(var.trans.location.y - varinside.collider.ly, 2);
							}
							else if (var.trans.location.y > varinside.collider.sy &&var.trans.location.y < varinside.collider.ly) {
								distance += 0;
							}
							//z
							if (var.trans.location.z < varinside.collider.sz) {
								distance += pow(varinside.collider.sz - var.trans.location.z, 2);
							}
							else if (var.trans.location.z > varinside.collider.lz) {
								distance += pow(var.trans.location.z - varinside.collider.lz, 2);
							}
							else if (var.trans.location.z > varinside.collider.sz &&var.trans.location.z < varinside.collider.lz) {
								distance += 0;
							}


							float sphererad2 = pow(var.collider.radius, 2);

							if (pow(distance, 2) < sphererad2) 
							{
								colliding = true;
							}

							if (colliding) 
							{
								if (var.trans.stuff.mass < varinside.trans.stuff.mass && var.cancollide) {
									std::cout << var.name << " collided with " << varinside.name << " at distance: " << distance << std::endl;
									var.iscolliding = true;
									var.cancollide = false;
								}
								if (varinside.cancollide && var.trans.stuff.mass > varinside.trans.stuff.mass) {
									std::cout << varinside.name << " collided with " << var.name << " at distance: " << distance << std::endl;
									varinside.iscolliding = true;
									varinside.cancollide = false;
								}
							}
						}
					}
				}

			}
			//if they are a box
		if (var.isbox)
		{
			for (object& varinside : objs)
			{
				if (!varinside.isself)
				{
					if (varinside.issphere)
					{
						bool colliding = false;
						//box to sphere goes here
						//compute distance^2  from sphere center to nearest point on box
						float distance=0;
						if (varinside.trans.location.x < var.collider.sx) {
							distance += pow(var.collider.sx - varinside.trans.location.x, 2);
						}
						else if (varinside.trans.location.x > var.collider.lx) {
							distance += pow(varinside.trans.location.x - var.collider.lx, 2);
						}
						else if (varinside.trans.location.x > var.collider.sx &&varinside.trans.location.x < var.collider.lx) {
							distance += 0;
						}
						//y
						if (varinside.trans.location.y < var.collider.sy) {
							distance += pow(var.collider.sy - varinside.trans.location.y, 2);
						}
						else if (varinside.trans.location.y > var.collider.ly) {
							distance += pow(varinside.trans.location.y - var.collider.ly, 2);
						}
						else if (varinside.trans.location.y > var.collider.sy &&varinside.trans.location.y < var.collider.ly) {
							distance += 0;
						}
						//z
						if (varinside.trans.location.z < var.collider.sz) {
							distance += pow(var.collider.sz - varinside.trans.location.z, 2);
						}
						else if (varinside.trans.location.z > var.collider.lz) {
							distance += pow(varinside.trans.location.z - var.collider.lz, 2);
						}
						else if (varinside.trans.location.z > var.collider.sz &&varinside.trans.location.z < var.collider.lz) {
							distance += 0;
						}

						float sphererad2 = pow(varinside.collider.radius, 2);
						if (pow(distance, 2) < sphererad2)
						{
							colliding = true;
						}
						if (colliding)
						{
							if (var.trans.stuff.mass < varinside.trans.stuff.mass && var.cancollide) {
								std::cout << var.name << " collided with " << varinside.name << " at distance: " << distance << std::endl;
								var.iscolliding = true;
								var.cancollide = false;
							}
							if (varinside.cancollide && var.trans.stuff.mass > varinside.trans.stuff.mass) {
								std::cout << varinside.name << " collided with " << var.name << " at distance: " << distance << std::endl;
								varinside.iscolliding = true;
								varinside.cancollide = false;
							}
						}
						
					}
					//box to box doesn't seem to work but working on it
					if (varinside.isbox)
					{
						bool colliding=false;
						//box to box would go here
						if (varinside.collider.sx<var.collider.lx &&
							varinside.collider.lx>var.collider.sx &&
							varinside.collider.sy<var.collider.ly &&
							varinside.collider.ly>var.collider.sy &&
							varinside.collider.sz<var.collider.lz &&
							varinside.collider.lz>var.collider.sz) 
						{
							colliding = true;
						}
						if (colliding)
						{
							if (var.trans.stuff.mass < varinside.trans.stuff.mass && var.cancollide) {
								std::cout << var.name << " collided with " << varinside.name  << std::endl;
								var.iscolliding = true;
								var.cancollide = false;
							}
							if (varinside.cancollide && var.trans.stuff.mass > varinside.trans.stuff.mass) {
								std::cout << varinside.name << " collided with " << var.name << std::endl;
								varinside.iscolliding = true;
								varinside.cancollide = false;
							}
						}

					}

				}
			}

		}
			var.isself = false;
		}

		//put the light inside the sun
		float lightpos[3] = { objs[1].trans.location.x,objs[1].trans.location.y,objs[1].trans.location.z };
		glUniform3fv(9, 1, lightpos);

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		t0 = t;
		t = (float)glfwGetTime();
		dt = t - t0;
		glUniform1f(4, t);
	
		//universal gravitation
		//f=g*(m1m2/r2)
		for (object& var : objs)
		{
			if (var.isorbit=true) {
				if (objs[1].trans.location.x != var.trans.location.x) {
					var.trans.stuff.force.x += .0006*((var.trans.stuff.mass*objs[1].trans.stuff.mass) / (objs[1].trans.location.x - var.trans.location.x));
					//objs[0].trans.stuff.force.x -= .006*((objs[0].trans.stuff.mass*objs[1].trans.stuff.mass) / (objs[0].trans.location.x + objs[1].trans.location.x));
					if (var.trans.stuff.force.x > 2) {
						var.trans.stuff.force.x = 2;
					}
					else if (var.trans.stuff.force.x < -2) {
						var.trans.stuff.force.x = -2;
					}
				}
				if (objs[1].trans.location.z != var.trans.location.z) {
					var.trans.stuff.force.z += .0006*((var.trans.stuff.mass*objs[1].trans.stuff.mass) / (objs[1].trans.location.z - var.trans.location.z));
					//objs[0].trans.stuff.force.z -= .006*((objs[0].trans.stuff.mass*objs[1].trans.stuff.mass) / (objs[0].trans.location.z + objs[1].trans.location.z));
					if (var.trans.stuff.force.z > 2) {
						var.trans.stuff.force.z = 2;
					}
					else if (var.trans.stuff.force.z < -2) {
						var.trans.stuff.force.z = -2;
					}
				}
			
			}
		}
		//sun movement left and right
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_LEFT))
		{
			objs[1].trans.stuff.force += glm::vec3(-.025, 0, 0);
		}
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_RIGHT))
		{
			objs[1].trans.stuff.force += glm::vec3(.025, 0, 0);
		}
		
		//sun movement foward and back
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_UP))
		{
			objs[1].trans.stuff.force += glm::vec3(0, 0, -.025);
		}
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_DOWN))
		{
			objs[1].trans.stuff.force += glm::vec3(0, 0, .025);
		}

		//limiting your movement
		if (objs[1].trans.stuff.force.y > 15) {
			objs[1].trans.stuff.force.y = 15;
		}
		else if (objs[1].trans.stuff.force.y < -15) {
			objs[1].trans.stuff.force.y = -15;
		}
		if (objs[1].trans.stuff.force.x > 15) {
			objs[1].trans.stuff.force.x = 15;
		}
		else if (objs[1].trans.stuff.force.x < -15) {
			objs[1].trans.stuff.force.x = -15;
		}
		if (objs[1].trans.stuff.force.z > 15) {
			objs[1].trans.stuff.force.z = 15;
		}
		else if (objs[1].trans.stuff.force.z < -15) {
			objs[1].trans.stuff.force.z = -15;
		}
	
		//std::cout << objs[1].trans.stuff.force.x <<" , "<< objs[1].trans.stuff.force.y<<" , "<< objs[1].trans.stuff.force.z<< std::endl;
		//apply forces
		for(object& var : objs)
		{	
			var.trans.stuff.velocity = glm::vec3(0, 0, 0);	
			var.trans.stuff.velocity += var.trans.stuff.force / var.trans.stuff.mass;
			var.trans.location += var.trans.stuff.velocity*dt;

			//rotate all the things
			if (!var.isbox) 
			{
				var.trans.rotation.y += 2 * dt;
			}

			//if gravity
			if (var.isgrav==true) {
				var.trans.stuff.force -= var.trans.stuff.mass*var.trans.stuff.velocity*dt;
				//made gravity a touch smaller so they don't go flying off
				glm::vec3 grav = { 0,-3,0 };
				var.trans.stuff.force += grav*var.trans.stuff.mass*dt;
				//std::cout << "Y: " << var.trans.stuff.force.y << std::endl;
			}
		
			//scale
			glm::mat4 sizing =glm::scale(var.trans.size);
			//rotation
			glm::mat4 rotmat= glm::yawPitchRoll(var.trans.rotation.y, var.trans.rotation.x, var.trans.rotation.z);
			//translation
			glm::mat4 translation = glm::translate(var.trans.location);
			//combine them
			var.trans.objworldtransmat = translation*rotmat*sizing;
		
			glUniformMatrix4fv(15, 1, GL_FALSE, &var.trans.objworldtransmat[0][0]);
			var.tex.use();
			if (!var.iscolliding) {
				var.mod.render();
			}
				
		}

		cam.upload();
		cam.cameraturn(GLFWwindowPtr);
		cam.move(dt, GLFWwindowPtr);
		
	//	glBindVertexArray(0);
		glfwSwapBuffers(GLFWwindowPtr);
		glfwPollEvents();

		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_ESCAPE))
		{
			glfwWindowShouldClose(GLFWwindowPtr);
			return 0;
		}
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_R))
		{
			for (object& var : objs)
			{
				float x,  z;
				float leftx = rand() % 1;
				if (leftx == 0) {
					x = rand() % 30 - 30;
				}
				else {
					x = rand() % 30;
				}
			
				
				float leftz = rand() % 1;
				if (leftz == 0) {
					z = rand() % 30 - 30;
				}
				else {
					z = rand() % 30;
				}
				var.trans.location = glm::vec3(x, 0, z);
				var.trans.stuff.force = glm::vec3(0, 0, 0);
				var.iscolliding = false;
				var.cancollide = true;
			}

		}
	}
	glfwTerminate();
	return 0;
}


