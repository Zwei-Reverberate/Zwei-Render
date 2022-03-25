#include "Light.h"

Light::Light
(
	const glm::vec3& _pos, 
	const glm::vec3& _color, 
	const glm::vec3& _specular, 
	const glm::vec3& _dir, 
	const float& _intensity
):
	position(_pos), 
	color(_color), 
	specular(_specular), 
	direction(_dir), 
	intensity(_intensity)
	{}

Light::~Light(){}

PointLight::PointLight
(
	const glm::vec3& _pos,
	const glm::vec3& _color,
	const glm::vec3& _specular,
	const float& _intensity,
	const float& c,
	const float& l,
	const float& q
) : constant(c), linear(l), quadratic(q)
{
	position = _pos;
	color = _color;
	specular = _specular;
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	intensity = _intensity;
}

glm::vec3 PointLight::calcPointLight
(
	const glm::vec3& worldPos,
	const glm::vec3& worldNormal,
	const glm::vec3& worldViewDir,
	const glm::vec3& orign
)
{
	float distance = glm::distance(worldPos, position);
	float attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));


	glm::vec3 lightDir = glm::normalize(worldPos - position);
	float diff = std::max(glm::dot(worldNormal, -lightDir), 0.0f);
	glm::vec3 reflectDir = glm::normalize(reflect(lightDir, worldNormal));
	float spec = pow(std::max(glm::dot(worldViewDir, reflectDir), 0.0f), 32);

	glm::vec3 diffuse = color * diff * orign;
	glm::vec3 specular = specular * spec;

	diffuse *= attenuation;
	specular *= attenuation;

	return  (diffuse + specular) * intensity;
}
