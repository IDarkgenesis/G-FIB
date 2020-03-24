#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform bool classic=true;

void main()
{   
    vec2 center= vec2(0.5,0.5);
    float phi= 3.14/16.;
    
    float dist = distance(center,vtexCoord);
    
    vec2 u= center - vtexCoord;
    float ang= atan(u.t,u.s); 
    float red= mod(ang/phi +0.5, 2);
    
    
    if(dist <= 0.2) fragColor= vec4(1,0,0,1);
    else if ( ! classic && red < 1) fragColor= vec4(1,0,0,1);
    else fragColor= vec4(1);
}
