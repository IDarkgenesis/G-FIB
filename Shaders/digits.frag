#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;
uniform int aux;

void main()
{   
    
    float s = vtexCoord.s;
    int digitTime;
    
    
    if(s < 1) digitTime= int(time/100)%10;
    else if (s < 2) digitTime= int(time/10)%10-1;
    else digitTime= int(time)%10-2;
    
    
    
    
    
    
    vec4 auxTex= texture(colorMap,vec2(s/10 + digitTime/10.,vtexCoord.t));
    
    if(auxTex.a < 0.5) discard;
    
    fragColor = vec4(1,0,0,1);
}
