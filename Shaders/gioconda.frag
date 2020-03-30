#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D sampler;

const vec2 ull  = vec2(0.393,0.652);
const vec2 offS = vec2(0.057,-0.172);
const float r = 0.025;

void main()
{   
    vec4 auxCol=vec4(0,0,0,1);
    
    if(fract(time) > 0.5){
        if (distance(ull,vtexCoord) <= 0.025) auxCol= texture(sampler,vtexCoord+offS);
        else auxCol= texture(sampler,vtexCoord);
    }
    else auxCol= texture(sampler,vtexCoord);
    
    fragColor = auxCol;
}
