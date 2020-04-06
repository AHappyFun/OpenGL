#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Shader * shader;
	unsigned int diffuse;
	unsigned int specular;
	unsigned int emission;
	glm::vec3 ambient;
	float shininess;

	Material(Shader * _shader,unsigned int diffuse, unsigned int specular,glm::vec3 ambient, unsigned int emission,float shininess);

};

