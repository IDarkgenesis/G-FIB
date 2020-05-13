#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform float step=0.2;

const vec4 COLOR= vec4(0.8,0.8,0.8,1);

void enviaVertexCub(bool x, bool y, bool z, vec3 centre, vec3 N){
    gfrontColor= COLOR*N.z;
    vec3 newVertex= vec3(x?0.5:-0.5,y?0.5:-0.5,z?0.5:-0.5)*step;
    gl_Position= modelViewProjectionMatrix * vec4(newVertex+centre,1);
    EmitVertex();
}

void main( void )
{   
    vec3 baricentre= (
        gl_in[0].gl_Position.xyz+
        gl_in[1].gl_Position.xyz+
        gl_in[2].gl_Position.xyz)/3;
        
        baricentre /= step;
        baricentre.x=int(baricentre.x);
        baricentre.y=int(baricentre.y);
        baricentre.z=int(baricentre.z);
        baricentre*=step;
        
        
        
        //Front
        vec3 N=normalMatrix*vec3(0, 0, 1);
        enviaVertexCub(false,false,true,baricentre,N);
        enviaVertexCub(true,false,true,baricentre,N);
        enviaVertexCub(false,true,true,baricentre,N);
        enviaVertexCub(true,true,true,baricentre,N);
        EndPrimitive();
        
        //Right
        N=normalMatrix*vec3(1, 0, 0);
        enviaVertexCub(true,false,true,baricentre,N);
        enviaVertexCub(true,false,false,baricentre,N);
        enviaVertexCub(true,true,true,baricentre,N);
        enviaVertexCub(true,true,false,baricentre,N);
        EndPrimitive();
        
        //Left
        N=normalMatrix*vec3(-1, 0, 0);
        enviaVertexCub(false,false,true,baricentre,N);
        enviaVertexCub(false,false,false,baricentre,N);
        enviaVertexCub(false,true,true,baricentre,N);
        enviaVertexCub(false,true,false,baricentre,N);
        EndPrimitive();
        
        //Back
        N=normalMatrix*vec3(0, 0, -1);
        enviaVertexCub(false,false,false,baricentre,N);
        enviaVertexCub(true,false,false,baricentre,N);
        enviaVertexCub(false,true,false,baricentre,N);
        enviaVertexCub(true,true,false,baricentre,N);
        EndPrimitive();
        
        //Top
        N=normalMatrix*vec3(0, 1, 0);
        enviaVertexCub(false,true,true,baricentre,N);
        enviaVertexCub(true,true,true,baricentre,N);
        enviaVertexCub(false,true,false,baricentre,N);
        enviaVertexCub(true,true,false,baricentre,N);
        EndPrimitive();
        
        //Bottom
        N=normalMatrix*vec3(0, -1, 0);
        enviaVertexCub(false,false,true,baricentre,N);
        enviaVertexCub(true,false,true,baricentre,N);
        enviaVertexCub(false,false,false,baricentre,N);
        enviaVertexCub(true,false,false,baricentre,N);
        EndPrimitive();
}
