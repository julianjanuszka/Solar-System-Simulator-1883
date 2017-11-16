#include "Object.h"



Object::Object()
{
	tag = "myObjTag";
}


Object::~Object()
{
}

void Object::update()
{
}

void Object::render()
{
	std::cout << "Rendering : " << tag << std::endl;
}
