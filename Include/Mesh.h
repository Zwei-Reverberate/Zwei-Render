#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Vertex.h"


// Use Mesh to restore models, including vertex datas and indexes

class Mesh
{
public:
	std::vector<Vertex> vertexBuffer;
	std::vector<unsigned int> vertexIndex;

	Mesh();
	Mesh(const int& _vNum, const int& _iNum);
	Mesh(const Mesh& _mesh);
	void addMesh(const Mesh& _mesh);
	void addTriangle(const Vertex& _A, const Vertex& _B, const Vertex& _C);
	Mesh& operator= (const Mesh& _mesh);
	Mesh& operator+= (const Mesh& _mesh);
	Mesh createPlane
	(
		const glm::vec3& leftTop, 
		const glm::vec3& leftBottom,
		const glm::vec3& rightBottom, 
		const glm::vec3& rightTop,
		const glm::vec3& normal
	);
	Mesh createBox(const glm::vec3& center, float radius);
	Mesh loadObj(const char* path);
};