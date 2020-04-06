#include "LightPoint.h"






LightPoint::LightPoint(glm::vec3 position, glm::vec3 angles, glm::vec3 color):
	position(position),
	angles(angles),
	color(color)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

LightPoint::~LightPoint()
{
}
