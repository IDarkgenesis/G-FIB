#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

const float speed= 0.5;
const float angSpeed = 8.0;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

    
void main( void )
{
    
    vec3 n= vec3(0);
    
    for( int j = 0; j < 3; ++j){
            n += vnormal[j]/3;
		}
    n *= speed * time;
	
	float alpha= angSpeed*time;
	
	mat3 Rz= mat3(
        vec3(cos(alpha), sin(alpha), 0), 
        vec3(-sin(alpha), cos(alpha), 0), 
        vec3(0,0,1));
        
    vec3 Trans0=(gl_in[0].gl_Position.xyz+
          gl_in[1].gl_Position.xyz+
          gl_in[2].gl_Position.xyz)/3;
	
	
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		
		vec3 newVertex= gl_in[i].gl_Position.xyz  - Trans0;
		
		newVertex= Rz * newVertex;
		newVertex += Trans0 + n;
		
		gl_Position = modelViewProjectionMatrix * vec4(newVertex,1); 
		EmitVertex();
	}
    EndPrimitive();
}
