#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;

uniform float slice=0.1;
uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;

void main()
{   
    
    int frame= int(mod(time/slice,4));
    switch(frame){
        case 0:
            fragColor = texture(sampler0,vtexCoord);
            break;
        case 1:
            fragColor = texture(sampler1,vtexCoord);
            break;
        case 2:
            fragColor = texture(sampler2,vtexCoord);
            break;
        case 3:
            fragColor = texture(sampler3,vtexCoord);
            break;
        
    }
}
