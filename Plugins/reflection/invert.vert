#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 bbm;
uniform vec3 bbM;

mat4 inverse_obj() {
	vec3 vector1 = vec3(bbm.x,bbm.y,bbM.z) - bbm;
	vec3 vector2 = vec3(bbm.x,bbm.y,bbM.z) - vec3(bbM.x,bbm.y,bbM.z);
	vec3 normal = normalize(cross(vector1,vector2));
	float a = normal.x;
	float b = normal.y;
	float c = normal.z;
	float d = -a*bbm.x - b*bbm.y - c*bbm.z; 

	return mat4(vec4(1.-2.*a*a, -2.*b*a, 	-2.*c*a, 	0),
				vec4(-2.*b*a, 	1.-2.*b*b, 	-2.*c*b, 	0),
				vec4(-2.*c*a,	-2.*c*b, 	1.-2.*c*c, 	0),
				vec4(-2.*d*a,	-2.*d*b,	-2.*d*c,	1));

}
/* PER COLUMNES (COM TOCA)
vec4(1.-2.*a*a, -2.*b*a, -2.*c*a, 0),
vec4(-2.*b*a, 1.-2.*b*b, -2.*c*b, 0),
vec4(-2.*c*a,-2.*c*b, 1.-2.*c*c, 0),
vec4(-2.*d*a,-2.*d*b,-2.*d*c,1)
*/

/* PER FILES (ERROR)
vec4(	1.-2.*a*a, 	-2.*b*a, 	-2.*c*a, 	-2.*d*a),
vec4(	-2.*b*a, 	1.-2.*b*b, 	-2.*c*b, 	-2.*d*b),
vec4(	-2.*c*a, 	-2.*c*b, 	1.-2.*c*c, -2.*d*c),
vec4(	0,			0,			0,			1)
*/

void main()
{	
	frontColor = vec4(color,1);
    gl_Position = modelViewProjectionMatrix * inverse_obj() * vec4(vertex, 1.0);
}