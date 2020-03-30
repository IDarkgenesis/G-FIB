#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main()
{
    float prop= 1/10.;
    
    float num= 1./n;
    float s= fract(vtexCoord.s/num);
    float t= fract(vtexCoord.t/num);
    
    if(s > prop && t > prop) discard;
    else fragColor = vec4(1,0,0,1 );
}
