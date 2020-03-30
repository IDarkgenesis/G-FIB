#version 330 core


in vec3 N;
in vec3 vertexC;
//in vec4 frontColor;
out vec4 fragColor;

uniform int n=4;
const float pi=3.141592;

//PER CALCULAR LA ILUMINACIÓ
//uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
//uniform vec4 lightPosition;

//uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

void main()
{
    
    vec3 auxN = normalize(N);
    vec4 fragAux;
    
    float alphStep= 2*pi/n; 
    
    for(float alpha = 0; alpha < 2*pi; alpha+= alphStep){
    
        vec3 lightPosition= vec3(10*cos(alpha),10*sin(alpha),0);
        
        vec3 L = normalize(lightPosition - vertexC);
        vec3 V = normalize(vec3(0,0,0) - vertexC);
        vec3 R = normalize(2*max(0.0,dot(auxN,L))*auxN-L);
        
        fragAux += (matDiffuse*lightDiffuse*max(0.0,dot(auxN,L)))/sqrt(n) + matSpecular*lightSpecular*pow(max(0.0,dot(R,V)),matShininess);
    }
    
    fragColor = fragAux;//frontColor;
}
