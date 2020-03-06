#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;

void main()
{
    
    
    
    vec2 actFrme= vec2(vtexCoord.s+(mod(time, 48)*0.5), vtexCoord.t+(mod(time,48)*0.5));
    fragColor = texture(colorMap, actFrme);
}
