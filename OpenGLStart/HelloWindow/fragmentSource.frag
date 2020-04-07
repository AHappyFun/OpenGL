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
	float shininess;   //反光度
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

//非线性深度转到线性
float Linear01Depth(float depth)
{
	float near = 0.1;
	float far = 100.0;
	float z = depth * 2.0 - 1.0;   //转换到NDC
	return (2 * near * far) / (far + near - depth * (far - near));
}

void main() 
{			
		float dist=length(lightPos-FragPos);
		float attenuation=1.0/(lightP.constant+lightP.linear*dist+lightP.quadratic*(dist*dist));
		
		vec3 lightDir=normalize(lightPos-FragPos);
		
		vec3 reflectVec=reflect(-lightDir,Normal);
		vec3 cameraVec=normalize( cameraPos-FragPos);

		//vec3 speclar=material.specular* pow( max(dot(reflectVec,cameraVec),0.0f),material.shininess)*lightColor;
		vec3 specular=texture(material.specular,TexCoord).rgb*pow( max(dot(reflectVec,cameraVec),0.0f),material.shininess)*lightColor;

		vec3 diffuse=texture(material.diffuse,TexCoord).rgb*max(dot(lightDir,Normal),0)*lightColor;

		vec3 ambient=texture(material.diffuse,TexCoord).rgb* ambientColor;

		vec3 emission=texture(material.emission,TexCoord).rgb;

		float cosTheta=dot( normalize(FragPos-lightPos), -1 * lightDirectionUniform);

		float spotRatio;
		if(cosTheta > lightS.cosPhyInner){    
			spotRatio=1.0f;
		}
		else if(cosTheta>lightS.cosPhyOutter){
			spotRatio=clamp(1.0f-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOutter-lightS.cosPhyInner),0,1.0f);
		}
		else{
			spotRatio=0.0f;
		}

		color=vec4((ambient+(diffuse+specular))*objColor,1.0);

		float depth = Linear01Depth(gl_FragCoord.z) / 100.0;
		color = vec4(vec3(depth),1);
		
}	

