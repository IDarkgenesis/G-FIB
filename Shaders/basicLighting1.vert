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
    vec3 N = normalize(normalMatrix * normal); //ES CREA UNA VAR N PER A OBTENIR EL VALOR NORMALITZAT DE LES COORD 
    frontColor = vec4(color,1.0) * N.z; //ES MULTIPLICA EL VALOR DE LA Z PER A OBTENIR EL COLOR DEJITJAT
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
