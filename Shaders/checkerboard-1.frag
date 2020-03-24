#version 330 core

//in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    int valS= int(mod((vtexCoord.s/0.125),2));
    int valT= int(mod((vtexCoord.t/0.125),2));
    
    /*
    if(valS == 1 && valT == 1) fragColor = vec4(0.8);         // 1 1
    else if (valS == 1 && valT == 0)  fragColor = vec4(0);    // 1 0
    else if(valS == 0 && valT == 1)   fragColor = vec4(0);    // 0 1
    else fragColor = vec4(0.8);                               // 0 0
    */
    if(valS == valT) fragColor = vec4(0.8);
    else fragColor = vec4(0);
}
