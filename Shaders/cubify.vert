#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    
    float x= abs(vertex.x);
    float y= abs(vertex.y);
    float z= abs(vertex.z);
    
    float div=  max(max(x,y),z);
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex/div, 1.0);
}
