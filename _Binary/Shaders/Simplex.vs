#version 330
layout (location = 0) in vec3 Position_b;
layout (location = 1) in vec3 Color_b;
layout (location = 2) in vec3 UV_b;
layout (location = 3) in vec3 Normal_b;
layout (location = 4) in vec3 Binormal_b;
layout (location = 5) in vec3 Tangent_b;

uniform mat4 VP;
uniform mat4 m4ToWorld[250];

out vec3 Normal_W;
out vec3 Tangent_W;
out vec3 Binormal_W;
out vec3 Position_W;
out vec3 Eye_W;
out vec2 UV;
out vec3 Color;

void main()
{
	//gl_InstanceID
	gl_Position = (VP * m4ToWorld[gl_InstanceID]) * vec4(Position_b, 1);
	
	UV = UV_b.xy;
	Color = Color_b;

	Position_W =	(m4ToWorld[gl_InstanceID] * vec4(Position_b,1)).xyz;
	Normal_W =		(m4ToWorld[gl_InstanceID] * vec4(Normal_b,0)).xyz;
	Tangent_W =		(m4ToWorld[gl_InstanceID] * vec4(Tangent_b, 0.0)).xyz;
	Binormal_W =	(m4ToWorld[gl_InstanceID] * vec4(Binormal_b, 0.0)).xyz;
}