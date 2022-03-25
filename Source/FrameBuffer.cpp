#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const int& _width, const int& _height)
{
	width = _width;
	height = _height;
	colorBuffer.resize(width * height);
	zBuffer.resize(width * height, 1.0f);
}

void FrameBuffer::clearColorBuffer(const glm::vec4& color)
{
	int bufferLen = height * width;
	for (int i = 0; i < bufferLen; i++)
	{
		colorBuffer[i].b = color.r;
		colorBuffer[i].g = color.g;
		colorBuffer[i].r = color.b;
		colorBuffer[i].a = color.a;
	}
}

void FrameBuffer::writePixel(const int& x, const int& y, const glm::vec4& color)
{
	if (x < 0 || x >= width || y < 0 || y >= height) return;

	int pos = (height - 1 - y) * width + x;
	colorBuffer[pos].b = color.r;
	colorBuffer[pos].g = color.g;
	colorBuffer[pos].r = color.b;
	colorBuffer[pos].a = color.a;
}

float FrameBuffer::getDepth(const int& x, const int& y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height) return 1.0f;

	int pos = (height - 1 - y) * width + x;
	return zBuffer[pos];
}

void FrameBuffer::writeDepth(const int& x, const int& y, const float& depth)
{
	if (x < 0 || x >= width || y < 0 || y >= height) return;
	int pos = (height - 1 - y) * width + x;
	zBuffer[pos] = depth;
}

void FrameBuffer::clearZBuffer(const float& depth)
{
	int bufferLen = height * width;
	for (int i = 0; i < bufferLen; i++)
	{
		zBuffer[i] = 1.0f;
	}
}
