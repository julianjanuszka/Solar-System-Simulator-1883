#version 330

in vec3 Color;

uniform vec3 wire = vec3(-1,-1,-1);

out vec4 Fragment;

void main()
{
	Fragment = vec4(Color,1);
	
	if(wire.r != -1.0 && wire.g != -1.0 && wire.b != -1.0)
		Fragment = vec4(wire, 1);

	return;
}