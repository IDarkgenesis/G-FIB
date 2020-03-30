#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int nstripes = 16;
uniform vec2 origin=vec2(0,0);

void main()
{
    vec2 elem = vtexCoord - origin;
    
    //Medir amplitud i multiplicar per saber en quina secció es troba
    float dist = int(length(elem)*nstripes);
    
    //Si es troba en pos parell es vermella
    if(mod(dist,2) == 0)fragColor=vec4(1,0,0,1);
    
    else fragColor = vec4(1,1,0,1);
}
