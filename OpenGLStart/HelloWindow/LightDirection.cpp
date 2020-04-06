#include "LightDirection.h"



LightDirection::LightDirection(glm::vec3 position,glm::vec3 angles,glm::vec3 color):
	position(position),
	angles(angles),
	color(color)
{
}


LightDirection::~LightDirection()
{
}

void LightDirection::UpdateDirection() {
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -direction;
}