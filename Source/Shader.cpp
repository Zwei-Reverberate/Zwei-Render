#include "Shader.h"

Shader::Shader()
{
	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::mat4(1.0f);
}

Vertrans Shader::vertexShader(const Vertex& vert)
{
	Vertrans vf;

	vf.worldPos = modelMatrix * vert.position;
	vf.windowPos = projectionMatrix * viewMatrix * vf.worldPos;

	vf.zvalue = 1.0f / vf.windowPos.w;

	vf.worldPos *= vf.zvalue;
	vf.color = vert.color*vf.zvalue;
	vf.normal = vert.normal*vf.zvalue;
	vf.textcoord =vert.textcoord*vf.zvalue;

	return vf;
}

glm::vec4 Shader::fragmentShader(const Vertrans& vf)
{
	float u = vf.textcoord.x;
	float v = vf.textcoord.y;
	glm::vec4 color = texture.sample2D(u, v);

	glm::vec3 worldNormal = glm::normalize(vf.normal);
	glm::vec3 worldViewDir = glm::normalize(glm::vec3(0, 0, 3) - glm::vec3(vf.worldPos));
	glm::vec3 result = ambient * glm::vec3(color);
	result += light.calcPointLight(glm::vec3(vf.worldPos), worldNormal, worldViewDir, glm::vec3(color));

	return glm::vec4(result, 1.0f);
}

void Shader::setTexture(const Texture& _texture)
{
	texture = _texture;
}
