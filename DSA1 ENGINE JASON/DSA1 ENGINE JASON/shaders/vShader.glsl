#version 430

layout (location = 0) in vec3 modelloc;
out float red;
layout (location=3)uniform float scale;
layout(location=15)uniform mat4 modelworldmat;
layout(location=6)uniform mat4 cameramat;
layout (location = 2) in vec3 modelnorms;

in vec2 modelUV;
out vec2 fragUV;
out vec3 fragloc;
out vec3 fragnorm;
void main()

{
fragUV=modelUV;
fragloc=vec3(modelworldmat*vec4(modelloc,1));
fragnorm=modelnorms;
gl_Position =cameramat*modelworldmat*vec4(modelloc,1);
red=(modelloc.x+1)/2;

}