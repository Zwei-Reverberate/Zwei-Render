#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Fov;
	float Aspect;
	float Pitch;
	float Yaw;

	Camera
	(
		glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3 _lookat = glm::vec3(0.0f, 0.0f, 0.0f),
		float _fov = 60.0f, int _w = 1000, int _h = 600
	);

	// View Matrix
	glm::mat4 GetViewMatrix();

	// Projection Matrix
	glm::mat4 GetProjectionMatrix(const float& n, const float& f);

	glm::mat4 ViewMatrix();

	glm::mat4 PerspectiveMatrix(const float& n, const float& f);

	void UpdateFov(float _fov = 60.0f);
	void UpdateAspect(int _w, int _h);
	void MoveForward(float distance);
	void MoveRight(float distance);
	void MoveUp(float distance);
	void RotatePitch(float angle);
	void RotateYaw(float angle);

private:
	void UpdateCameraVectors();
};
