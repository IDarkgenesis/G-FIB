#version 330 core

in vec3 N;
in vec3 vertexE;
out vec4 fragColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;

uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat4 modelViewMatrix;

vec4 light(vec3 N, vec3 V, vec3 L)
{
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec=pow( RdotV, matShininess );
    return 
        (matDiffuse * lightDiffuse * Idiff)/2 + matSpecular * lightSpecular * Ispec;
}

void main()
{   
    vec3 Min = boundingBoxMin;
    vec3 Max = boundingBoxMax;
    
    vec3 p[8];
    
    p[0] = (modelViewMatrix * vec4(Max.x, Max.y, Max.z, 1)).xyz;
    p[1] = (modelViewMatrix * vec4(Max.x, Max.y, Min.z, 1)).xyz;
    p[2] = (modelViewMatrix * vec4(Max.x, Min.y, Max.z, 1)).xyz;
    p[3] = (modelViewMatrix * vec4(Max.x, Min.y, Min.z, 1)).xyz;
    p[4] = (modelViewMatrix * vec4(Min.x, Max.y, Max.z, 1)).xyz;
    p[5] = (modelViewMatrix * vec4(Min.x, Max.y, Min.z, 1)).xyz;
    p[6] = (modelViewMatrix * vec4(Min.x, Min.y, Max.z, 1)).xyz;
    p[7] = (modelViewMatrix * vec4(Min.x, Min.y, Min.z, 1)).xyz;
    
    vec3 V = normalize(-vertexE);
    
    fragColor = vec4(0);
    
    for(int i=0; i < 8; ++i){
        vec3 L= normalize(p[i] - vertexE);
        fragColor += light(N,V,L);
    }
}
