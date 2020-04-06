#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightDirection
{
public:
	
	LightDirection(glm::vec3 position, glm::vec3 angles, glm::vec3 color=glm::vec3(1.0f,1.0f,1.0f));
	~LightDirection();
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	void UpdateDirection();
	
};


