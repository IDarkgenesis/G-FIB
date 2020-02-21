#version 330 core

in vec3 vertexC;
in vec3 N;
// in vec4 frontColor;
out vec4 fragColor;

//PER CALCULAR LA ILUMINACIÓ
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

void main()
{
    vec3 auxN = normalize(N);
    //OBTENIR VALORS 
    vec3 L = normalize(lightPosition.xyz - vertexC.xyz);
    vec3 V = normalize(vec3(0,0,0) - vertexC.xyz);
    vec3 R = normalize(2*max(0.0,dot(auxN,L))*auxN-L);
    
    
    
    fragColor = matAmbient*lightAmbient + matDiffuse*lightDiffuse*max(0.0,dot(auxN,L)) + matSpecular*lightSpecular*pow(max(0.0,dot(R,V)),matShininess);
}
