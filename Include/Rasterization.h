#pragma once
#include "Vertrans.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include <algorithm>

class Rasterization
{
private:
	Vertrans A;
	Vertrans B;
	Vertrans C;

public:
	Rasterization() = default;
	~Rasterization() = default;

	Rasterization(const Vertrans& _a, const Vertrans& _b, const Vertrans& _c);
	glm::vec3 baryCentric(Vertrans P);
	glm::vec3 bary(Vertrans P);
	Vertrans lerp(Vertrans vf, glm::vec3 weights);
	void rasterTriangle(FrameBuffer& buffer, Shader& shader);
};