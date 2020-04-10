#version 330 core                           
layout(location = 0) in vec3 position;      
//layout(location = 1) in vec3 Color;   
layout(location = 1) in vec3 aNormal; 
layout(location = 2) in vec2 aTexCoord;

out VERT_OUT {
	//vec3 myColor; 
	vec2 TexCoord;
	vec3 Normal;
	//vec3 FragPos;
}vert_out;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main() {								
		gl_Position = projectionMat * viewMat * modelMat * vec4(position, 1.0f);  
	    vert_out.TexCoord=aTexCoord;
		mat3 normalMatrix = mat3(transpose(inverse(modelMat * modelMat)));
		vert_out.Normal = normalize(vec3(projectionMat * vec4(normalMatrix * aNormal, 0.0)));
		
		//vert_out.FragPos=(modelMat * vec4(position, 1.0f)).xyz;
      // vert_out.myColor=Color; 
}   