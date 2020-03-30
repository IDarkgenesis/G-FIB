#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D fbm; 
uniform float time; 

const float pi = 3.14159; 

const int A=1;
const float f=0.1;

void main()
{

    float r= texture(fbm,vtexCoord).x;
    
    float phi=2*pi*r;
    
    //Funcio Sinusoidal A * sin(w * t + phi) / w=2*pi*f
    float v= A * sin(2*pi*f * time + phi);
    
    vec3 col= vec3(0);
    
    //EN VERS DE SER SUBNORMAL MILLOR POSAR INTERVALS A COSES QUE SE ENTENEN MILLOR :D
    float t= (v+1)*3;
    
    if(t < 1)        	col= mix(vec3(1,0,0),vec3(1,1,0),fract(t));
    else if (t < 2)		col= mix(vec3(1,1,0),vec3(0,1,0),fract(t));
    else if (t < 3)		col= mix(vec3(0,1,0),vec3(0,1,1),fract(t));
    else if (t < 4)		col= mix(vec3(0,1,1),vec3(0,0,1),fract(t));
    else if (t < 5)		col= mix(vec3(0,0,1),vec3(1,0,1),fract(t));
    else 				col= mix(vec3(1,0,1),vec3(1,0,0),fract(t));
    
    fragColor = vec4(col,1); 
}
