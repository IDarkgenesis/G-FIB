#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D explosion;
uniform float time;

void main()
{
    float slice= 1/30.;
    int actFrame= int(mod(time/slice, 48));
    int offT=5;
    
    int x= actFrame%8; //mod 8 per saber quina columna es  
    int y= 5-actFrame/8; //8 per saber quina 

    
    
    fragColor = texture(explosion, vec2(vtexCoord.s*1/8. + x/8., vtexCoord.t*1/6. + y/6.));
    fragColor *= fragColor.w;
}
