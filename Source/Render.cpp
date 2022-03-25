#include "Render.h"

Render::Render(const int& _width, const int& _height)
{
	width = _width;
	height = _height;
	shader = nullptr;
	buffer = nullptr;
}

Render::~Render()
{
	if (shader) delete shader;
	if (buffer)delete buffer;
	shader = nullptr;
	buffer = nullptr;
}

glm::mat4 Render::getViewPortMatrix()
{
	glm::mat4 result = glm::mat4(1.0f);
	result[0][0] = width / 2.0f;
	result[3][0] = 0 + (width / 2.0f);
	result[1][1] = height / 2.0f;
	result[3][1] = 0 + (height / 2.0f);
	return result;
}

void Render::Init()
{
	if (shader) delete shader;
	if (buffer) delete buffer;
	viewPortMatrix = getViewPortMatrix();
	shader = new Shader();
	buffer = new FrameBuffer(width, height);
}

void Render::setModelMatrix(const glm::mat4& _model)
{
	shader->modelMatrix = _model;
}

void Render::setViewMatrix(const glm::mat4& _view)
{
	shader->viewMatrix = _view;
}

void Render::setProjectMatrix(const glm::mat4& _projection)
{
	shader->projectionMatrix = _projection;
}

void Render::setTexture(const std::string& _path)
{
	shader->setTexture(Texture(_path));
}

void Render::clearBuffer(const glm::vec4& _color)
{
	buffer->clearColorBuffer(_color);
	buffer->clearZBuffer(1.0f);
}

void Render::renderOutTri(const Vertex& _A, const Vertex& _B, const Vertex& _C)
{
	Vertrans A = shader->vertexShader(_A);
	Vertrans B = shader->vertexShader(_B);
	Vertrans C = shader->vertexShader(_C);

	A.windowPos = viewPortMatrix * A.windowPos;
	B.windowPos = viewPortMatrix * B.windowPos;
	C.windowPos = viewPortMatrix * C.windowPos;

	Rasterization raster = Rasterization(A, B, C);
	raster.rasterTriangle(*buffer, *shader);
}

void Render::renderOutMesh(const Mesh& _mesh)
{
	if (_mesh.vertexIndex.empty()) return;

	for (int i = 0; i < _mesh.vertexIndex.size(); i += 3)
	{
		Vertex p1, p2, p3;
		p1 = _mesh.vertexBuffer[_mesh.vertexIndex[i]];
		p2 = _mesh.vertexBuffer[_mesh.vertexIndex[i+1]];
		p3 = _mesh.vertexBuffer[_mesh.vertexIndex[i+2]];

		Vertrans vf1, vf2, vf3;
		vf1 = shader->vertexShader(p1);
		vf2 = shader->vertexShader(p2);
		vf3 = shader->vertexShader(p3);

		perspectiveDivision(vf1);
		perspectiveDivision(vf2);
		perspectiveDivision(vf3);

		if (!faceCulling(vf1.windowPos, vf2.windowPos, vf3.windowPos))
		{
			continue;
		}

		vf1.windowPos = viewPortMatrix * vf1.windowPos;
		vf2.windowPos = viewPortMatrix * vf2.windowPos;
		vf3.windowPos = viewPortMatrix * vf3.windowPos;

		Rasterization triAn = Rasterization(vf1, vf2, vf3);
		triAn.rasterTriangle(*buffer, *shader);
	}
}

void Render::perspectiveDivision(Vertrans& vf)
{
	vf.windowPos = vf.windowPos / vf.windowPos.w;
	vf.windowPos.w = 1.0f;
	vf.windowPos.z = (vf.windowPos.z + 1.0f) * 0.5f;
}

bool Render::faceCulling(const glm::vec4& v1, const glm::vec4& v2, const glm::vec4& v3)
{
	glm::vec3 tmp1 = glm::vec3(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	glm::vec3 tmp2 = glm::vec3(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);

	glm::vec3 normal = glm::normalize(glm::cross(tmp1, tmp2));
	glm::vec3 view = glm::vec3(0, 0, 1);
	return glm::dot(normal, view) > 0;
}

void Render::cameraInit(glm::vec3 _pos, glm::vec3 _up, glm::vec3 _lookat, float _fov, int _w, int _h)
{
	camera = Camera(_pos, _up, _lookat, _fov, _w, _h);
}

void Render::setCamera(const float& n, const float& f)
{
	setViewMatrix(camera.ViewMatrix());
	setProjectMatrix(camera.PerspectiveMatrix(n, f));
}
