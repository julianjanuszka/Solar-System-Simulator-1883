#version 330
uniform sampler2D TextureID;
in vec2 UV;
out vec4 Fragment;

void main()
{
	Fragment = texture( TextureID, UV );
	
	return;
}