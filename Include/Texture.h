#pragma once
#include <vector>
#include <string>
#include<glm/glm.hpp>

class Texture
{
public:
	int width;
	int height;
	int channels;
	std::vector<unsigned char> pixels;


	Texture() = default;
	Texture(const std::string & path);
	~Texture();

	glm::vec4 sample2D(float u, float v);
};