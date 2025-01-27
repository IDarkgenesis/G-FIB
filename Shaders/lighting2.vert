#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

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
    
    vec4 vertexCAM= modelViewMatrix * vec4(vertex,1.0);
    vec3 N = normalize(normalMatrix * normal);
    //OBTENIR VALORS 
    vec3 L = normalize(lightPosition.xyz - vertexCAM.xyz);
    vec3 V = normalize(vec3(0,0,0) - vertexCAM.xyz);
    vec3 R = normalize(2*max(0.0,dot(N,L))*N-L);
    
    
    
    frontColor = matAmbient*lightAmbient + matDiffuse*lightDiffuse*max(0.0,dot(N,L)) + matSpecular*lightSpecular*pow(max(0.0,dot(R,V)),matShininess);
    
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
