#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

//out vec4 frontColor;
out vec2 vtexCoord;
out vec3 N;
out vec3 vertexC;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform mat4 modelViewMatrix;

void main()
{
    N = normalMatrix * normal;
    //frontColor = vec4(color,1.0) * N.z;
    vertexC= (modelViewMatrix * vec4(vertex,1.0)).xyz;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
