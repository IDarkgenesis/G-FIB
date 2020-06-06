#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
out vec4 vfrontColor;

uniform mat3 normalMatrix;
uniform float time;
uniform float n=1;

const float a= -9.8;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vfrontColor = vec4(color,1.0) * N.z;
    float t= mod(time,2*n);

    vec3 newVertex= vertex;

    if(t < n){
        newVertex.y += 0.5*a*t*t;
    }
    else{
        newVertex.y += (0.5*a*n*n) + (-a*n)*(t-n) + (0.5*a*(t*t-2*t*n+n*n));
    }

    gl_Position = vec4(newVertex, 1.0);
}
