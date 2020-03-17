#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main() {
    
    
    float val= texture(noise0,vtexCoord).z;
    vec4 aux= texture(grass2,vtexCoord);
    if(val < 1) aux=mix(texture(rock1,vtexCoord),aux,val);
    fragColor=aux;
}
