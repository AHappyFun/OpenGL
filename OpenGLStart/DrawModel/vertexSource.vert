#version 330 core                           
layout(location = 0) in vec3 position;      
//layout(location = 1) in vec3 Color;   
layout(location = 1) in vec3 aNormal; 
layout(location = 2) in vec2 aTexCoord;
out vec3 myColor;   
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main() {								
		gl_Position = projectionMat * viewMat * modelMat * vec4(position, 1.0f);  
		Normal=mat3(transpose(inverse(modelMat))) * aNormal;
		FragPos=(modelMat * vec4(position, 1.0f)).xyz;
      // myColor=Color; 
	    TexCoord=aTexCoord;
}   