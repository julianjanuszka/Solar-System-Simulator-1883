#version 430
out vec4 fragColor;
in float red;
layout (location = 8) uniform vec3 camloc;
layout (location = 9)uniform vec3 lightloc;
uniform sampler2D myTexture;
in vec2 fragUV;
in vec3 fragloc;
in vec3 fragnorm;
layout(location=4)uniform float time;
void main()

{
//calc color
float green=(sin(time)+1)/2;
float blue=(cos(time*2)+2)/2;

//calc lighting
vec3 L= normalize(lightloc-fragloc);
vec3 V= normalize(camloc-fragloc);
vec3 H= normalize((L+V));
vec3 N= normalize(fragnorm);

float ambient=.5f;

float diffuse=.5f;
diffuse=(max(dot(L,N),0));

float specular=1.0f;
specular= max(dot(H,N),0);

float brightness= ambient+(.5*diffuse)+(.5*pow(specular,16));
//fragColor = brightness*vec4(0.5f, 0.1f, 0.5f, 1.0f);
fragColor= texture(myTexture,fragUV)*brightness;


}