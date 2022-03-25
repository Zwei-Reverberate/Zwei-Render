#pragma once
#include <glm/glm.hpp>

// Vertex is the input datatype
// Include position, color, normal and textcoord
class Vertex
{
public:
	glm::vec4 position;
	glm::vec4 color;
	glm::vec2 textcoord;
	glm::vec3 normal;

	Vertex();
	~Vertex() = default;

	Vertex
	(
		const glm::vec4& _position,
		const glm::vec4& _color,
		const glm::vec2& _textcoord,
		const glm::vec3& _normal
	);

	Vertex
	(
		const glm::vec3& _position,
		const glm::vec4& _color,
		const glm::vec2& _textcoord,
		const glm::vec3& _normal
	);

	Vertex(const glm::vec4& _position, const glm::vec4& _color);
	Vertex(const Vertex& _vertex);

};