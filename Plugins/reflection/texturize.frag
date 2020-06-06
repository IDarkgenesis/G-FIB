#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float SIZE;

void main()
{
    vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
    vec4 tex = texture(colorMap,st);
    fragColor = tex + vec4(-vec3(0.2),0);
    //if(tex.x == 0 && tex.y == 0 && tex.z == 0) fragColor = vec4(1);
}
