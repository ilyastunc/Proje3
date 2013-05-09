#version 120

uniform vec3 LightPos;
varying vec3 normal;
varying vec3 boyut;
varying vec3 Light;

void main()
{
    normal = normalize(gl_NormalMatrix*gl_Normal);
    boyut = gl_Vertex.xyz;
    
	Light = vec3(gl_ModelViewMatrix*(vec4(LightPos,1)-gl_Vertex));
    gl_Position = ftransform();
}