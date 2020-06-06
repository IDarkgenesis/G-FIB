#version 330 core

out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;
uniform float SIZE;

void main()
{   
    vec2 st = gl_FragCoord.xy / SIZE;
    vec2 newCoord = st + 0.01*sin(10.0*time+30.0*st.x);
    fragColor = texture2D(colorMap,newCoord);
}

