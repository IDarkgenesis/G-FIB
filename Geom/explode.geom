#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

const float speed= 0.5;

uniform mat4 modelViewProjectionMatrix;
uniform float time;


void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		
		vec3 n= vec3(0);
		
		for( int j = 0; j < 3; ++j){
            n += vnormal[j]/3;
		}
		
		vec3 newVertex= gl_in[i].gl_Position.xyz + speed * time * n;
		
		gl_Position = modelViewProjectionMatrix * vec4(newVertex,1); 
		EmitVertex();
	}
    EndPrimitive();
}
