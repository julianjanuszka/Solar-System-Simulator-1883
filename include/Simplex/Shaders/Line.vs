#version 330
layout (location = 0) in vec3 Position_b;
layout (location = 1) in vec3 Color_b;

uniform mat4 VP;
uniform mat4 m4ToWorld[250];

out vec3 Color;

void main()
{
	//gl_InstanceID
	gl_Position = (VP * m4ToWorld[gl_InstanceID]) * vec4(Position_b, 1);
	
	Color = Color_b;
}