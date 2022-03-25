#pragma once
#include<glm/glm.hpp>
#include<vector>
#include <limits>

class FrameBuffer
{
public:
	int height;
	int width;
	std::vector<glm::vec4> colorBuffer;
	std::vector<float> zBuffer;

	FrameBuffer(const int& _width, const int& _height);
	~FrameBuffer() = default;
	void clearColorBuffer(const glm::vec4& color);
	void writePixel(const int& x, const int& y, const glm::vec4& color);
	float getDepth(const int& x, const int& y) const;
	void writeDepth(const int& x, const int& y, const float& depth);
	void clearZBuffer(const float& depth);
};
