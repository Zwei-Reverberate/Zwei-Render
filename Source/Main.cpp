#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Render.h"
#include "Mesh.h"

const int SCR_WIDTH = 1000;
const int SCR_HEIGHT = 600;
const glm::vec4 WHITE_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec4 BLACK_COLOR = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 BG_COLOR = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
const glm::vec3 CAMERA_POS = glm::vec3(0, 0, 3);
const glm::vec3 CAMERA_UP = glm::vec3(0, 1, 0);
const glm::vec3 CAMERA_LOOKAT = glm::vec3(0, 0, 0);
const float CAMERA_FOV = 60.0f;
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 100.0f;



int main()
{
	//Mesh Box = Box.createBox(glm::vec3(0.0f, 0.0f, 0.0f), 0.5f);
	Mesh Shana = Shana.loadObj("Model/Shanana.obj");
	//Mesh Miku = Miku.loadObj("Model/Miku2.obj");
	Render render(SCR_WIDTH, SCR_HEIGHT);
	render.Init();
	render.cameraInit(CAMERA_POS, CAMERA_UP, CAMERA_LOOKAT, CAMERA_FOV, SCR_WIDTH, SCR_HEIGHT);

	glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(0.0f, -2.0f, 0.0f));
	//trans = glm::translate(trans, glm::vec3(0.0f, -3.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(0.03f, 0.03f, 0.03f));
	//render.setModelMatrix(trans);

	//render.setTexture("Picture/texture.png");
	render.setTexture("Model/Shanana.png");
	//render.setTexture("Model/Miku2.png");
	//float angle = 0.0f;

	int key = 0;
	//trans = glm::rotate(trans, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

	while (key!=27)
	{
		trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));
		render.setModelMatrix(trans);
		render.clearBuffer(BG_COLOR);
		render.setCamera(NEAR_PLANE, FAR_PLANE);
		//render.renderOutMesh(Miku);
		render.renderOutMesh(Shana);
		// render.renderOutMesh(Box);
		//angle += 1.0f;

		cv::Mat Zwei = cv::Mat(SCR_HEIGHT, SCR_WIDTH, CV_32FC4, render.buffer->colorBuffer.data());
		cv::imshow("Zwei", Zwei);

		key = cv::waitKey(1);
		if (key == 'a')
		{
			render.camera.MoveRight(-0.05f);
		}
		if (key == 'd')
		{
			render.camera.MoveRight(0.05f);
		}
		if (key == 'w')
		{
			render.camera.MoveUp(0.05f);
		}
		if (key == 's')
		{
			render.camera.MoveUp(-0.05f);
		}
		if (key == 'j')
		{
			render.camera.MoveForward(-0.05f);
		}
		if (key == 'k')
		{
			render.camera.MoveForward(0.05f);
		}
		if (key == 'u')
		{
			render.camera.RotatePitch(1.0f);
		}
		if (key == 'i')
		{
			render.camera.RotatePitch(-1.0f);
		}
		if (key == 'o')
		{
			render.camera.RotateYaw(1.0f);
		}
		if (key == 'p')
		{
			render.camera.RotateYaw(-1.0f);
		}
	}
	return 0;
}

