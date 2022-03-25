#pragma once
#include <glm/glm.hpp>
#include <algorithm>

class Light
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 specular;
	glm::vec3 direction;
	float intensity;

	Light
	(
		const glm::vec3& _pos = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& _color = glm::vec3(1.0f, 1.0f, 1.0f),
		const glm::vec3& _specular = glm::vec3(1.0f, 1.0f, 1.0f),
		const glm::vec3& _dir = glm::vec3(0.0f, -1.0f, 0.0f),
		const float& _intensity = 1.0f
	);

	virtual ~Light();
};

class PointLight : public Light 
{
public:
	float constant;
	float linear;
	float quadratic;

	PointLight
	(
		const glm::vec3& _pos = glm::vec3(0.0f, 0.0f, 10.0f),
		const glm::vec3& _color = glm::vec3(1.0f, 1.0f, 1.0f),
		const glm::vec3& _specular = glm::vec3(1.0f, 1.0f, 1.0f),
		const float& _intensity = 1.0f,
		const float& c = 1.0f,
		const float& l = 0.09f,
		const float& q = 0.032f
	);
	glm::vec3 calcPointLight
	(
		const glm::vec3& worldPos,
		const glm::vec3& worldNormal,
		const glm::vec3& worldViewDir,
		const glm::vec3& orign
	);
};