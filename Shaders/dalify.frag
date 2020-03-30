#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform float t = 4.0; 
uniform float scale = 4.0; 

void main()
{
    fragColor = frontColor;
}
