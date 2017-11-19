#version 330
layout (location = 0) in vec3 Position_b;
layout (location = 1) in vec3 Color_b;
layout (location = 2) in vec3 UV_b;

uniform mat4 VP;
uniform mat4 m4ModelToWorld;
uniform mat4 m4CameraOnWorld;

out vec2 UV;

void main()
{
	gl_Position = VP * m4CameraOnWorld * vec4(Position_b, 1);
	UV = UV_b.xy;
}