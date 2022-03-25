#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"
#include <iostream>


Texture::Texture(const std::string& Path)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(Path.c_str(), &width, &height, &channels, 0);

	for (int i = 0; i < width * height * channels; i++)
	{
		pixels.push_back(data[i]);
	}

	stbi_image_free(data);
}

Texture::~Texture()
{}

glm::vec4 Texture::sample2D(float u, float v)
{
	if (u > 1 || v > 1 || u < 0 || v < 0)
	{
		return glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	int x = u * (width - 1);
	int y = v * (height - 1);
	int index = (y * width + x) * channels;
	float r = pixels[index] / 255.0f;
	float g = pixels[index + 1] / 255.0f;
	float b = pixels[index + 2] / 255.0f;
	float a = pixels[index + 3] / 255.0f;
	return glm::vec4(r, g, b, a);
}

