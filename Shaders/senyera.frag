#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const float a= 1/9.0;

void main()
{
    float f= fract(vtexCoord.s);

    if(f>=0 && f<a) fragColor = vec4(1,1,0,1);
    else if (f>=2*a && f<3*a) fragColor = vec4(1,1,0,1); 
    else if (f>=4*a && f<5*a) fragColor = vec4(1,1,0,1);
    else if (f>=6*a && f<7*a) fragColor = vec4(1,1,0,1);
    else if (f>=8*a && f<9*a) fragColor = vec4(1,1,0,1);
    else fragColor = vec4(1,0,0,1);
}
