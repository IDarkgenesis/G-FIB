#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
in vec3 N;
out vec4 fragColor;

const vec2 C1= vec2(0.34,0.65);
const vec2 C2= vec2(0.66,0.65);

uniform sampler2D colormap;
uniform mat3 normalMatrix;

void main()
{
    
    vec3 aN= normalize(normalMatrix * N);
    
    vec2 aC1= C1 - 0.1*aN.xy;
    vec2 aC2= C2 - 0.1*aN.xy;
    
    if( distance(vtexCoord,aC1) <= 0.05 || distance(vtexCoord,aC2) <= 0.05) fragColor= vec4(0,0,0,1);
    else fragColor = texture(colormap, vtexCoord);
}
