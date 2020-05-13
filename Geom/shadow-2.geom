#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    gfrontColor = vec4(0);
    for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 P = gl_in[i].gl_Position;
		P.y *= 0.01;
		P.xz *= 1 ;
		P.y += boundingBoxMin.y;
		
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();
    
    if (gl_PrimitiveIDIn == 0) {
        
        gfrontColor = vec4(0,1,1,0);
        
        float R = distance(boundingBoxMax,boundingBoxMin)/2;
        
        vec3 centre= (boundingBoxMax+boundingBoxMin)/2;
        centre.y= boundingBoxMin.y-0.01;
        
        vec4 P1= vec4(centre,1) + vec4(-R,0,R,0);
        vec4 P2= vec4(centre,1) + vec4(R,0,R,0);
        vec4 P3= vec4(centre,1) + vec4(-R,0,-R,0);
        vec4 P4= vec4(centre,1) + vec4(R,0,-R,0);
        
        gl_Position= modelViewProjectionMatrix * P1; 
        EmitVertex();
        
        gl_Position= modelViewProjectionMatrix * P2; 
        EmitVertex();
        
        gl_Position= modelViewProjectionMatrix * P3; 
        EmitVertex();
        
        gl_Position= modelViewProjectionMatrix * P4; 
        EmitVertex();
        
        EndPrimitive();
     }
}
