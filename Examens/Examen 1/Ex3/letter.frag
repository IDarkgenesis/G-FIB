#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const float slice=1/8.;
const float range= 0.1;

void main()
{
	float s=vtexCoord.s;
	float t=vtexCoord.t;
	
    //RECTA INFERIOR
    if(s <= 0.8 && distance(vec2(s,0),vtexCoord) <= slice) 		fragColor=vec4(0,0,0,1);
    //RECTA SUPERIOR 
    else if(s <= 0.8 && distance(vec2(s,1),vtexCoord) <= slice) 	fragColor=vec4(0,0,0,1);
    //RECTA VERTICAL ESQ
    else if(s < 0.2 && distance(vec2(0,t),vtexCoord) <= slice) 	fragColor=vec4(0,0,0,1);
    //RECTA CENTRAL
    else if(s <= 0.8 && distance(vec2(s,0.5),vtexCoord) <= slice/2) fragColor=vec4(0,0,0,1);
    //VERTICAL DRETA INF
    else if(s > 0.8 && t > 0.1 && t < 0.45 && distance(vec2(.8,t),vtexCoord) <= slice) fragColor=vec4(0,0,0,1);
    else if(s > 0.8 && t > 0.55 && t <= 0.9 && distance(vec2(.8,t),vtexCoord) <= slice) fragColor=vec4(0,0,0,1);
    
    else fragColor = vec4(1);
}
