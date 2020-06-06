#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const vec2 center= vec2(1,0.5);
void main()
{   
    if(distance(center,vec2(vtexCoord.s*2,vtexCoord.t)) <= 0.35) fragColor=vec4(1,0,0,1);
    else if(vtexCoord.t > 0.66) fragColor=vec4(0,0.7,0,1);
    else if(vtexCoord.t < 0.66 && vtexCoord.t > 0.33) fragColor=vec4(1,1,0,1);
    else fragColor=vec4(0,0,0.8,1);
}
