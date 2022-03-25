#pragma once
#include "Rasterization.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Camera.h"
#include <opencv2/opencv.hpp>


class Render
{
public:
	int width;
	int height;
	glm::mat4 viewPortMatrix;
	Shader* shader;
	FrameBuffer* buffer;
	Camera camera;


	Render(const int& _width, const int& _height);
	~Render();

	glm::mat4 getViewPortMatrix();
	void Init();

	void setModelMatrix(const glm::mat4& _model);
	void setViewMatrix(const glm::mat4& _view);
	void setProjectMatrix(const glm::mat4& _projection);

	void setTexture(const std::string& _path);

	// Both colorbuffer and zbuffer
	void clearBuffer(const glm::vec4& _color);

	void renderOutTri(const Vertex& _A, const Vertex& _B, const Vertex& _C);
	void renderOutMesh(const Mesh& _mesh);

	void perspectiveDivision(Vertrans& vf);
	bool faceCulling(const glm::vec4& v1, const glm::vec4& v2, const glm::vec4& v3);

	void cameraInit(glm::vec3 _pos, glm::vec3 _up, glm::vec3 _lookat, float _fov, int _w, int _h);
	void setCamera(const float& n, const float& f);
};

