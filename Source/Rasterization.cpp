#include "Rasterization.h"
#include <iostream>

Rasterization::Rasterization(const Vertrans& _a, const Vertrans& _b, const Vertrans& _c):
A(_a), B(_b), C(_c)
{}

glm::vec3 Rasterization::baryCentric(Vertrans P)
{
	float alpha = (
					-(P.windowPos.x - B.windowPos.x) * (C.windowPos.y - B.windowPos.y)
					+(P.windowPos.y - B.windowPos.y) * (C.windowPos.x - B.windowPos.x)
				  ) /
				  (
					-(A.windowPos.x - B.windowPos.x)*(C.windowPos.y-B.windowPos.y)
					+(A.windowPos.y - B.windowPos.y)*(C.windowPos.x-B.windowPos.x)
				  );
	float beta = (
					-(P.windowPos.x - C.windowPos.x) * (A.windowPos.y - C.windowPos.y)
					+(P.windowPos.y - C.windowPos.y) * (A.windowPos.x - C.windowPos.x)
				 ) /
				 (
					-(B.windowPos.x - C.windowPos.x) * (A.windowPos.y - C.windowPos.y)
					+(B.windowPos.y - C.windowPos.y) * (A.windowPos.x - C.windowPos.x)
				 );
	float fi = 1.0f - alpha - beta;
	return glm::vec3(alpha, beta, fi);
}

// More efficient
glm::vec3 Rasterization::bary(Vertrans P)
{
	glm::vec2 AB = glm::vec2(B.windowPos.x - A.windowPos.x, B.windowPos.y - A.windowPos.y);
	glm::vec2 AC = glm::vec2(C.windowPos.x - A.windowPos.x, C.windowPos.y - A.windowPos.y);
	glm::vec2 AP = glm::vec2(P.windowPos.x - A.windowPos.x, P.windowPos.y - A.windowPos.y);

	float factor = 1 / (AB.x * AC.y - AB.y * AC.x);
	float s = (AC.y * AP.x - AC.x * AP.y) * factor;
	float t = (AB.x * AP.y - AB.y * AP.x) * factor;
	glm::vec3 weights = glm::vec3(1 - s - t, s, t);
	return weights;
}

Vertrans Rasterization::lerp(Vertrans vf, glm::vec3 weights)
{
	vf.worldPos = A.worldPos * weights.x + B.worldPos * weights.y + C.worldPos * weights.z;
	vf.windowPos.z = A.windowPos.z * weights.x + B.windowPos.z * weights.y + C.windowPos.z * weights.z;
	vf.color = A.color * weights.x + B.color * weights.y + C.color * weights.z;
	vf.textcoord = A.textcoord * weights.x + B.textcoord * weights.y + C.textcoord * weights.z;
	vf.normal = A.normal * weights.x + B.normal * weights.y + C.normal * weights.z;
	vf.zvalue = A.zvalue * weights.x + B.zvalue * weights.y + C.zvalue * weights.z;
	return vf;
}

void Rasterization::rasterTriangle(FrameBuffer& buffer, Shader& shader)
{
	// find bounding box
	float xMax = (std::max)({ A.windowPos.x, B.windowPos.x, C.windowPos.x });
	float xMin = (std::min)({ A.windowPos.x, B.windowPos.x, C.windowPos.x });
	float yMax = (std::max)({ A.windowPos.y, B.windowPos.y, C.windowPos.y });
	float yMin = (std::min)({ A.windowPos.y, B.windowPos.y, C.windowPos.y });

	int x;
	int y;
	
	for (x = xMin; x <= xMax; x++)
	{
		for (y = yMin; y <= yMax; y++)
		{
			Vertrans P;
			P.windowPos.x = (float)x;
			P.windowPos.y = (float)y;
			glm::vec3 weights = bary(P);

			//Draw P when it is in the triangle
			if (weights.x >= 0 && weights.y >= 0 && weights.z >= 0)
			{
				P = lerp(P, weights);
				float depth = buffer.getDepth(P.windowPos.x, P.windowPos.y);
				if (P.windowPos.z < depth)
				{
					float z = P.zvalue;
					P.worldPos /= z;
					P.textcoord /= z;
					P.normal /= z;
					P.color /= z;
					buffer.writePixel(P.windowPos.x, P.windowPos.y, shader.fragmentShader(P));
					buffer.writeDepth(P.windowPos.x, P.windowPos.y, P.windowPos.z);
				}
			}
		}
	}
}
