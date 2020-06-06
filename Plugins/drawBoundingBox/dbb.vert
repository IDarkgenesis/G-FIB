#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform vec3 bbm;
uniform vec3 bbM;

mat4 scale(vec3 size){
    return mat4(
        vec4(size.x,0,0,0),
        vec4(0,size.y,0,0),
        vec4(0,0,size.z,0),
        vec4(0,0,0,     1));
}

mat4 translate(vec3 center){
    return mat4(
        vec4(1,0,0,center.x),
        vec4(0,1,0,center.y),
        vec4(0,0,1,center.z),
        vec4(0,0,0,       1));
}

void main()
{
    frontColor = vec4(color,1.0);
    
    vec3 size= bbM - bbm;
    vec3 center = (bbM + bbm)/2;

    vec4 newVertex;

    newVertex = vec4(vertex, 1.0) - vec4(vec3(0.5),0); // Moure a centre
    newVertex *= scale(size);
    newVertex *= translate(center);

    gl_Position= modelViewProjectionMatrix * newVertex;
}
