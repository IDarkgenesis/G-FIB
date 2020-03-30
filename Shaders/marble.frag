#version 330 core

//in vec4 frontColor;

in vec4 objectCoord;
//in vec2 vtexCoord;
in vec3 N;

out vec4 fragColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform sampler2D noise;

const vec4 auxS = vec4(0,1,-1,0)*0.3;
const vec4 auxT = vec4(-2,-1,1,0)*0.3;

const vec4 white= vec4(1);
const vec4 redish= vec4(0.5,0.2,0.2,1);

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
    vec3 lightPos = vec3(0.0,0.0,2.0);
    vec3 L = normalize( lightPos - Pos );
    vec3 V = normalize( -Pos);
    vec3 R = reflect(-L,N);
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Ispec = pow( RdotV, 20.0 );
    return diffuse * NdotL + Ispec;
}

void main()
{
    
    float s= dot(objectCoord, auxS);
    float t= dot(objectCoord, auxT);
    
    float v= texture(noise, vec2(s,t)).x;
   
    
    vec4 diffuse;
    if(v == 1 || v == 0) diffuse= white;
    else if (v == 0.5) diffuse= redish;
    else diffuse= mix(white,redish,v);
    
    vec4 pos= modelViewProjectionMatrix * objectCoord;
    
    fragColor = shading(normalize(normalMatrix*N),normalize(pos.xyz),diffuse);
}
