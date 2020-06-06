#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform vec4 color;
uniform bool select_on;

void main()
{
    if(!select_on) fragColor = frontColor;
    else fragColor= color;
}
