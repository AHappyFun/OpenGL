#version 330 core   
layout(location = 0) in vec3 position;      

out vec3 TexCoords;

uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
    TexCoords = position;
	gl_Position = projectionMat * viewMat  * vec4(position, 1.0f);  
}