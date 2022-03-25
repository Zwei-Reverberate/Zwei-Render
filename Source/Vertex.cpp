#include "Vertex.h"

Vertex::Vertex()
{
	position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	textcoord = glm::vec2(0.0f, 0.0f);
	normal = glm::vec3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex
(
	const glm::vec4& _position, 
	const glm::vec4& _color,
	const glm::vec2& _textcoord, 
	const glm::vec3& _normal
):
	position(_position),
	color(_color),
	textcoord(_textcoord),
	normal(_normal)
{}

Vertex::Vertex
(
	const glm::vec3 & _position, 
	const glm::vec4 & _color, 
	const glm::vec2 & _textcoord, 
	const glm::vec3 & _normal
):
	position(glm::vec4(_position, 1.0f)),
	color(_color),
	textcoord(_textcoord),
	normal(_normal)
{}

Vertex::Vertex(const glm::vec4 & _position, const glm::vec4& _color):
position(_position), color(_color)
{}

Vertex::Vertex(const Vertex & _vertex):
	position(_vertex.position),
	color(_vertex.color),
	textcoord(_vertex.textcoord),
	normal(_vertex.normal)
{}



