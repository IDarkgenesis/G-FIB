#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform float time;
uniform float speed=0.1;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(normalize(normalMatrix*normal).z);
    vtexCoord = texCoord/20+tan(time)*speed;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}