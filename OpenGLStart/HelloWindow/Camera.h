#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldUp);
	Camera(glm::vec3 position,float pitch,float yaw,glm::vec3 wordlUp);
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float SpeedZ=1.0f;
	float SpeedX = 1.0f;
	float SpeedY = 1.0f;

	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float deltaX,float deltaY);
	void MoveZ();
	void MoveX();
	void MoveY();
private:
	void UpdateCameraVectors();
};

