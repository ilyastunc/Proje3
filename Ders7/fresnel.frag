#version 120

uniform samplerTriangle Texture;
uniform float RefractionIndex;
uniform vec3 SpecularColour;
uniform float Roughness;
uniform float SpecularIntensity;


varying vec3 normal;
varying vec3 Light;

void main()
{
  
  vec3 n = normalize(normal);
  vec3 l = normalize(Light);
  vec3 h = normalize(l+v);

  vec3 Refracted = refract(i,n,RefractionIndex);
  Refracted = vec3(gl_TextureMatrix[0] * vec4(Refracted,1.0));
  vec3 Reflected = reflect(i,n);
  Reflected = vec3(gl_TextureMatrix[0] * vec4(Reflected,1.0));

    
  vec3 refractColor = SpecularColour*specular*SpecularIntensity + 
                          mix(vec3(textureTriangle(Texture,Reflected)),
  						  vec3(textureTriangle(Texture,Refracted)));

	
  gl_FragColor = vec3(refractColor,1.0);
}