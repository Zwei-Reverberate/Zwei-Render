#include "Camera.h"

Camera::Camera(glm::vec3 _pos, glm::vec3 _up, glm::vec3 _lookat, float _fov, int _w, int _h)
	:Position(_pos), WorldUp(_up), Fov(glm::radians(_fov)), Aspect((float)_w / _h), Pitch(0.0f), Yaw(0.0f)
{
	Front = glm::normalize(_lookat - Position);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

	glm::vec3 WorldFront(0, 0, -1);
	glm::vec3 FrontXZ = glm::normalize(glm::vec3(Front.x, 0, Front.z));
	float yd = glm::dot(WorldFront, FrontXZ);
	float pd = glm::dot(Front, FrontXZ);

	if (yd > 1.0) yd = 1.0;
	if (yd < -1)yd = -1.0;
	if (pd > 1.0)pd = 1.0;
	if (pd < -1)pd = -1.0;

	Yaw = glm::degrees(acos(yd));
	Pitch = glm::degrees(acos(pd));
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 result = glm::mat4(1.0f);

	result[0][0] = Right.x;
	result[1][0] = Right.y;
	result[2][0] = Right.z;
	result[3][0] = -glm::dot(Right, Position);
	result[0][1] = Up.x;
	result[1][1] = Up.y;
	result[2][1] = Up.z;
	result[3][1] = -glm::dot(Up, Position);
	result[0][2] = -Front.x;
	result[1][2] = -Front.y;
	result[2][2] = -Front.z;
	result[3][2] = glm::dot(Front, Position);
	return result;
}

glm::mat4 Camera::GetProjectionMatrix(const float& n, const float& f)
{
	glm::mat4 result = glm::mat4(0.0f);
	const float tanHalfFov = tan(Fov * 0.5f);
	result[0][0] = 1.0f / (Aspect * tanHalfFov);
	result[1][1] = 1.0f / (tanHalfFov);
	result[2][2] = -(f + n) / (f - n);
	result[2][3] = -1.0f;
	result[3][2] = (-2.0f * n * f) / (f - n);
	return result;
}

glm::mat4 Camera::ViewMatrix()
{
	return GetViewMatrix();
}

glm::mat4 Camera::PerspectiveMatrix(const float& n, const float& f)
{
	return GetProjectionMatrix(n, f);
}

void Camera::UpdateFov(float _fov)
{
	Fov = glm::radians(_fov);
}

void Camera::UpdateAspect(int _w, int _h)
{
	Aspect = (float)_w / _h;
}

void Camera::MoveForward(float distance)
{
	Position += Front * distance;
}

void Camera::MoveRight(float distance)
{
	Position += Right * distance;
}

void Camera::MoveUp(float distance)
{
	Position += Up * distance;
}

void Camera::RotatePitch(float angle)
{
	Pitch += angle;
	if (Pitch > 89.0) Pitch = 89.0;
	if (Pitch < -89.0) Pitch = -89.0;
	UpdateCameraVectors();
}

void Camera::RotateYaw(float angle)
{
	Yaw += angle;
	if (Yaw > 360) Yaw = 0;
	if (Yaw < 0)Yaw = 360;
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = -sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = -cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
