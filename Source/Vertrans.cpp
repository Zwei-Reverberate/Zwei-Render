#include "Vertrans.h"
#pragma once

Vertrans::Vertrans()
{
	worldPos = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	windowPos = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	textcoord = glm::vec2(0.0f, 0.0f);
	normal = glm::vec3(0.0f, 0.0f, 0.0f);
	zvalue = 0.0f;
}

Vertrans::Vertrans
(
	const glm::vec4& _worldPos, 
	const glm::vec4& _windowPos, 
	const glm::vec4& _color, 
	const glm::vec2& _textcoord, 
	const glm::vec3& _normal,
	const float& _zvalue
):
worldPos(_worldPos),
windowPos(_windowPos),
color(_color),
textcoord(_textcoord),
normal(_normal),
zvalue(_zvalue)
{}

Vertrans::Vertrans(const Vertrans & _vertrans):
worldPos(_vertrans.worldPos),
windowPos(_vertrans.windowPos),
color(_vertrans.color),
textcoord(_vertrans.textcoord),
normal(_vertrans.normal),
zvalue(_vertrans.zvalue)
{}
