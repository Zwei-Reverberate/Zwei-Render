#pragma once
#include "Vertex.h"
#include "Vertrans.h"
#include "Texture.h"
#include "Light.h"

// Environment Light
const glm::vec3 ambient = glm::vec3(0.5f, 0.5f, 0.5f);

class Shader
{
public:
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Texture texture;
	PointLight light;


	Shader();
	~Shader() = default;

	Vertrans vertexShader(const Vertex& vert);
	glm::vec4 fragmentShader(const Vertrans& vf);

	void setTexture(const Texture& _texture);
};