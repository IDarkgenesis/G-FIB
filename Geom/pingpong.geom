#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float n=1;
const float a= -9.8;

void Emit(){
	gl_Position.z /= 2.0;
	EmitVertex();
}

mat4 projectOntoPlane()
{
	vec3 light = vec3(4,10,-4);
	float A = 0;
	float B = 1;
	float C = 0;
	float D = -0.5*a*n*n+0.9;
	float s = -dot(vec4(-A,-B,-C,-D), vec4(light,1));	
	mat4 trans0 = mat4(1.0);
	mat4 trans1 = mat4(1.0); 
	trans0[3].xyz = light;	
	mat4 aux = mat4(vec4(s, 0, 0, -A), vec4(0, s, 0, -B), vec4(0, 0, s, -C), vec4(0));
	trans1[3].xyz = -light;
	return  trans0 * aux * trans1;
}

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position =  modelViewProjectionMatrix * gl_in[i].gl_Position;
		Emit();
	}
    EndPrimitive();

	if (gl_PrimitiveIDIn == 0) {
		gfrontColor = vec4(vec3(0.5),1);
		float yPlane= 0.5*a*n*n-1;
		
		vec4 P1 = vec4(-5,yPlane,5,1);
		vec4 P2 = vec4(5,yPlane,5,1);
		vec4 P3 = vec4(-5,yPlane,-5,1);
		vec4 P4 = vec4(5,yPlane,-5,1);

		gl_Position= modelViewProjectionMatrix * P1; 
        Emit();
        
        gl_Position= modelViewProjectionMatrix * P2; 
        Emit();
        
        gl_Position= modelViewProjectionMatrix * P3; 
        Emit();
        
        gl_Position= modelViewProjectionMatrix * P4; 
        Emit();
        
        EndPrimitive();
	}

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(vec3(0),100);
		gl_Position = modelViewProjectionMatrix * projectOntoPlane() * gl_in[i].gl_Position;
		Emit();
	}

}
