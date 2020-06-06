#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(vec3(0),1);
		vec4 newVertex =  gl_in[i].gl_Position;
		newVertex.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * newVertex;
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(vec3(0),1);
		vec4 newVertex =  gl_in[i].gl_Position;
		newVertex.x = boundingBoxMin.x;
		gl_Position = modelViewProjectionMatrix * newVertex;
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(vec3(0),1);
		vec4 newVertex =  gl_in[i].gl_Position;
		newVertex.z = boundingBoxMin.z;
		gl_Position = modelViewProjectionMatrix * newVertex;
		EmitVertex();
	}
    EndPrimitive();

}
