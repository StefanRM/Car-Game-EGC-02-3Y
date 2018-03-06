#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

int changeColor = 0;
int changeForm = 0;
int goUp = 0;
int goDown = 0;
int goRight = 0;
int goLeft = 0;
float distX = -1;
float distY = 0;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	// change color
	if (changeColor == 0) {
		glClearColor(0, 0, 0, 1);
	}
	else if (changeColor == 1) {
		glClearColor(1, 1, 0, 1);
	}
	else {
		glClearColor(0, 0, 1, 1);
	}

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	if (changeForm == 0) {
		RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
	}
	else {
		RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(1.5f));
	}

	// render the object again but with different properties
	if (goUp == 1) {
		distY += 0.1;
	}

	if (goDown == 1) {
		distY -= 0.1;
	}

	if (goRight == 1) {
		distX += 0.1;
	}

	if (goLeft == 1) {
		distX -= 0.1;
	}

	RenderMesh(meshes["box"], glm::vec3(distX, distY, 0));

	

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window->KeyHold(GLFW_KEY_W)) {
		goUp = 1;
	}
	else {
		goUp = 0;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		goDown = 1;
	}
	else {
		goDown = 0;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		goRight = 1;
	}
	else {
		goRight = 0;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		goLeft = 1;
	}
	else {
		goLeft = 0;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		//change color
		switch (changeColor) {
			case 0 : changeColor = 1;
					break;
			case 1 : changeColor = 2;
					break;
			default: changeColor = 0;
		}
	}

	if (key == GLFW_KEY_O) {
		changeForm = (changeForm + 1) % 2;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
