#version 330 core                            
//uniform vec4 myColor;                     
//in vec3 myColor;        
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;   //·´¹â¶È
};

struct LightPoint{
	float constant;
	float linear;
	float quadratic;
};
struct LightSpot{
	float cosPhyInner;
	float cosPhyOutter;
};

uniform sampler2D myTexture;
uniform sampler2D myFaceTex;
uniform vec3 ambientColor;
uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform vec3 lightDirectionUniform;

uniform Material material;
uniform LightPoint lightP;
uniform LightSpot lightS;

out vec4 color;  

void main() 
{			

	color = vec4(1,1,0,1);
		
}		