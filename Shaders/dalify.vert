#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform float t = 4.0; 
uniform float scale = 4.0; 

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    
    float c= mix(boundingBoxMin.y,boundingBoxMax.y,t);
    
    vec3 newVertex;
    if(vertex.y < c) newVertex= vec3(vertex.x,vertex.y*scale,vertex.z);
    else newVertex= vec3(vertex.x,vertex.y+(c*scale - c), vertex.z);
    
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}
