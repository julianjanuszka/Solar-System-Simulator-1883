#version 330
out vec4 Fragment;
uniform vec3 vWireframe;
void main()
{
	Fragment = vec4(vWireframe, 1);
	return;
}