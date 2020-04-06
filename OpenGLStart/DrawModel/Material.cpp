#include "Material.h"





Material::Material(Shader * _shader, unsigned int  diffuse, unsigned int specular, glm::vec3 ambient, unsigned int emission, float shininess):
	shader(_shader),
	diffuse(diffuse),
	specular(specular),
	ambient(ambient),
	emission(emission),
	shininess(shininess)
{
}



