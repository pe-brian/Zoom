varying vec3 vertex;
uniform float z_pos;

void main()
{
    vertex = gl_Vertex.xyz;
	vertex.y *= 2.0;
	vertex.z = z_pos;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
}
