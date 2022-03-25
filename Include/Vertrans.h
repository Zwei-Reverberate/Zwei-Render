#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include "Vertrans.h"


// VerTrans is the VertexShader's output datatype
// VerTrans is also the FragmentShader's input datatype

class Vertrans
{
public:
	glm::vec4 worldPos;
	glm::vec4 windowPos;
	glm::vec4 color;
	glm::vec2 textcoord;
	glm::vec3 normal;
	float zvalue;

	Vertrans();
	~Vertrans() = default;

	Vertrans
	(
		const glm::vec4& _worldPos,
		const glm::vec4& _windowPos,
		const glm::vec4& _color,
		const glm::vec2& _textcoord,
		const glm::vec3& _normal,
		const float& _zvalue
	);

	Vertrans(const Vertrans& _vertrans);
};