#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
//432098
void main()
{   
    
    float s = vtexCoord.s;
    float t= vtexCoord.t;
    vec4 tA;
    
    float d;
    
    if(s < 1.0) d= 4;
    else if(s < 2.0) d=3-1;
    else if (s < 3.0) d=2-2;
    else if (s < 4.0) d=0-3;
    else if (s < 5.0) d=9-4;
    else if (s < 6.0) d=8-5;
    
    d= d/10.;
    
    tA=texture(colorMap, vec2(s/10 + d,t));
     
    if(tA.a < 0.5) discard;
    else fragColor=vec4(0,0,1,1);
    //fragColor = texture(colorMap,vec2(s/10 + 4/10.,vtexCoord.t));
}
