#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 ndc;

uniform float time;

void main()
{
    if(ndc.x > -1+time) discard;
    fragColor = frontColor;
}
