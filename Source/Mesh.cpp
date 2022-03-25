#include "Mesh.h"

Mesh::Mesh()
{
	vertexBuffer.resize(0);
	vertexIndex.resize(0);
}

Mesh::Mesh(const int& _vNum, const int& _iNum)
{
	vertexBuffer.resize(_vNum);
	vertexIndex.resize(_iNum);
}

Mesh::Mesh(const Mesh& _mesh)
{
	vertexBuffer = _mesh.vertexBuffer;
	vertexIndex = _mesh.vertexIndex;
}

void Mesh::addMesh(const Mesh& _mesh)
{
	int incre = vertexBuffer.size();
	vertexBuffer.insert(vertexBuffer.end(), _mesh.vertexBuffer.begin(), _mesh.vertexBuffer.end());
	vertexIndex.resize(vertexIndex.size() + _mesh.vertexIndex.size());
	for (int i = 0; i < _mesh.vertexIndex.size(); i++)
	{
		vertexIndex.push_back(_mesh.vertexIndex[i] + incre);
	}
}

void Mesh::addTriangle(const Vertex& _A, const Vertex& _B, const Vertex& _C)
{
	int incre = vertexBuffer.size();
	vertexBuffer.push_back(_A);
	vertexBuffer.push_back(_B);
	vertexBuffer.push_back(_C);
	vertexIndex.push_back(incre);
	vertexIndex.push_back(incre + 1);
	vertexIndex.push_back(incre + 2);
}

Mesh& Mesh::operator=(const Mesh& _mesh)
{
	if (&_mesh == this) return *this;

	// Shadow copy
	vertexBuffer = _mesh.vertexBuffer;
	vertexIndex = _mesh.vertexIndex;
	return *this;
}

Mesh& Mesh::operator+=(const Mesh& _mesh)
{
	addMesh(_mesh);
	return *this;
}

Mesh Mesh::createPlane
(
	const glm::vec3& leftTop, 
	const glm::vec3& leftBottom, 
	const glm::vec3& rightBottom, 
	const glm::vec3& rightTop, 
	const glm::vec3& normal
)
{
	Mesh result(4, 6);
	result.vertexBuffer[0].position = glm::vec4(leftTop, 1.0f);
	result.vertexBuffer[0].normal = normal;
	result.vertexBuffer[0].color = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	result.vertexBuffer[0].textcoord = glm::vec2(0.0f, 1.0f);
	result.vertexBuffer[1].position = glm::vec4(rightTop, 1.0f);
	result.vertexBuffer[1].normal = normal;
	result.vertexBuffer[1].color = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	result.vertexBuffer[1].textcoord = glm::vec2(1.0f, 1.0f);
	result.vertexBuffer[2].position = glm::vec4(rightBottom, 1.0f);
	result.vertexBuffer[2].normal = normal;
	result.vertexBuffer[2].color = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	result.vertexBuffer[2].textcoord = glm::vec2(1.0f, 0.0f);
	result.vertexBuffer[3].position = glm::vec4(leftBottom, 1.0f);
	result.vertexBuffer[3].normal = normal;
	result.vertexBuffer[3].color = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
	result.vertexBuffer[3].textcoord = glm::vec2(0.0f, 0.0f);

	result.vertexIndex[0] = 0;
	result.vertexIndex[1] = 2;
	result.vertexIndex[2] = 1;
	result.vertexIndex[3] = 0;
	result.vertexIndex[4] = 3;
	result.vertexIndex[5] = 2;
	return result;
}

Mesh Mesh::createBox(const glm::vec3& center, float radius)
{
	Mesh result;
	Mesh front = createPlane
	(
		center + glm::vec3(-radius,  radius, radius),
		center + glm::vec3(-radius, -radius, radius),
		center + glm::vec3( radius, -radius, radius),
		center + glm::vec3( radius,  radius, radius),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	result.addMesh(front);

	Mesh left = createPlane
	(
		center + glm::vec3(-radius,  radius, -radius),
		center + glm::vec3(-radius, -radius, -radius),
		center + glm::vec3(-radius, -radius,  radius),
		center + glm::vec3(-radius,  radius,  radius),
		glm::vec3(-1.0f, 0.0f, 0.0f)
	);
	result.addMesh(left);

	Mesh right = createPlane
	(
		center + glm::vec3(radius,  radius,  radius),
		center + glm::vec3(radius, -radius,  radius),
		center + glm::vec3(radius, -radius, -radius),
		center + glm::vec3(radius,  radius, -radius),
		glm::vec3(1.0f, 0.0f, 0.0f)
	);
	result.addMesh(right);

	Mesh back = createPlane
	(
		center + glm::vec3( radius,  radius, -radius),
		center + glm::vec3( radius, -radius, -radius),
		center + glm::vec3(-radius, -radius, -radius),
		center + glm::vec3(-radius,  radius, -radius),
		glm::vec3(0.0f, 0.0f, -1.0f)
	);
	result.addMesh(back);

	Mesh up = createPlane
	(
		center + glm::vec3(-radius, radius, -radius),
		center + glm::vec3(-radius, radius,  radius),
		center + glm::vec3( radius, radius,  radius),
		center + glm::vec3( radius, radius, -radius),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	result.addMesh(up);

	Mesh down = createPlane
	(
		center + glm::vec3(-radius, -radius,  radius),
		center + glm::vec3(-radius, -radius, -radius),
		center + glm::vec3( radius, -radius, -radius),
		center + glm::vec3( radius, -radius,  radius),
		glm::vec3(0.0f, -1.0f, 0.0f)
	);
	result.addMesh(down);
	return result;
}

Mesh Mesh::loadObj(const char* path)
{
	Mesh result;

	std::ifstream in;
	in.open(path, std::ifstream::in);

	if (in.fail())
	{
		std::cout << "open obj error." << std::endl;
		exit(-1);
	}

	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;

	std::string line;

	while (!in.eof())
	{
		std::getline(in, line);
		if (!line.compare(0, 2, "v "))
		{
			line = line.substr(2);
			std::istringstream iss(line);
			glm::vec3 v;
			iss >> v.x;
			iss >> v.y;
			iss >> v.z;
			vertexs.push_back(v);
			continue;
		}
		if (!line.compare(0, 3, "vn "))
		{
			line = line.substr(3);
			std::istringstream iss(line);
			glm::vec3 vn;
			iss >> vn.x;
			iss >> vn.y;
			iss >> vn.z;
			normals.push_back(vn);
			continue;
		}
		if (!line.compare(0, 3, "vt "))
		{
			line = line.substr(3);
			std::istringstream iss(line);
			glm::vec3 vt;
			iss >> vt.x;
			iss >> vt.y;
			//vt.y = 1 - vt.y;
			texcoords.push_back(glm::vec2(vt.x, vt.y));
			continue;
		}

		if (!line.compare(0, 2, "f "))
		{
			line = line.substr(2);
			std::istringstream iss(line);
			char bar;

			int vIndex, vtIndex, vnIndex;
			int offset = result.vertexBuffer.size();
			for (int i = 0; i < 3; i++)
			{
				iss >> vIndex >> bar >> vtIndex >> bar >> vnIndex;
				if (vIndex > vertexs.size() || vtIndex > texcoords.size() || vnIndex > normals.size())
				{
					int sb = 2;
					sb++;
				}
				Vertex vertex(vertexs[vIndex - 1], glm::vec4(1, 1, 1, 1), texcoords[vtIndex - 1], normals[vnIndex - 1]);
				result.vertexBuffer.push_back(vertex);
				result.vertexIndex.push_back(offset + i);
			}
			continue;
		}
	}
	return result;
}
