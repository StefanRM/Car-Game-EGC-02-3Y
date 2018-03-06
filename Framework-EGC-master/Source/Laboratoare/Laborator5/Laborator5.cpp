#include "Laborator5.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}

bool Laborator5::isPointInRectangle(glm::vec2 point, glm::vec2 pointBackLeft, glm::vec2 pointFrontRight)
{
	return (point.x >= pointBackLeft.x && point.x <= pointFrontRight.x && point.y >= pointBackLeft.y && point.y <= pointFrontRight.y);
}

bool Laborator5::isRectangleCollision(glm::vec2 point1FrontLeft, glm::vec2 point1FrontRight, glm::vec2 point1BackLeft, glm::vec2 point1BackRight, glm::vec2 point2BackLeft, glm::vec2 point2FrontRight)
{
	return (isPointInRectangle(point1FrontLeft, point2BackLeft, point2FrontRight) ||
		isPointInRectangle(point1FrontRight, point2BackLeft, point2FrontRight) ||
		isPointInRectangle(point1BackLeft, point2BackLeft, point2FrontRight) ||
		isPointInRectangle(point1BackRight, point2BackLeft, point2FrontRight));
}

void Laborator5::Init()
{
	printf("\nTema 2 - EGC - Racing Game\nAuthor: Maftei Stefan - Radu\nGrupa: 336CC\n\nWelcome to Racing Game! Your goal is to drive your car to the finish line. But beware: you have obstacles and solid borders... and only 3 lifes!\nControls:\n-> up key to accelerate;\n-> down key to brake or move backward;\n-> left/right key to steer;\n-> X key to switch between cameras.\n Drive safely!\n\n");

	// translation factors
	tx = 0;
	ty = 0;
	tz = 0;

	// initial values
	angularStep = 0;
	rotateAngle = 0;
	speed = 0;
	acceleration = 3;
	deceleration = 2.75f;
	decelerationBreak = 3;
	reverseCar = false;
	speedReverse = 1;
	maxSpeed = 10;
	initialSpeed = 1;
	steeringAngle = 0;
	turnLeft = false;
	turnRight = false;

	// initial car corners
	initialCarFrontLeftX = 0.58f;
	initialCarFrontLeftZ = 1.27f;
	initialCarFrontRightX = -0.58f;
	initialCarFrontRightZ = 1.27f;
	initialCarBackLeftX = 0.58f;
	initialCarBackLeftZ = -1.2f;
	initialCarBackRightX = -0.58f;
	initialCarBackRightZ = -1.2f;

	// car corners in real time
	carFrontLeftX = 0;
	carFrontLeftZ = 0;
	carFrontRightX = 0;
	carFrontRightZ = 0;
	carBackLeftX = 0;
	carBackLeftZ = 0;
	carBackRightX = 0;
	carBackRightZ = 0;

	// obstacle coordinates
	obstacle1LeftBotX = 3;
	obstacle1LeftBotZ = 13;
	obstacle1LeftTopX = 3;
	obstacle1LeftTopZ = 14;
	obstacle1RighBotX = 2;
	obstacle1RightBotZ = 13;
	translationObstacle1 = 0;

	obstacle2LeftBotX = 9;
	obstacle2LeftBotZ = -20;
	obstacle2LeftTopX = 9;
	obstacle2LeftTopZ = -19;
	obstacle2RighBotX = 8;
	obstacle2RightBotZ = -20;
	translationObstacle2 = 0;

	obstacle3LeftBotX = -8;
	obstacle3LeftBotZ = -24;
	obstacle3LeftTopX = -8;
	obstacle3LeftTopZ = -23;
	obstacle3RighBotX = -9;
	obstacle3RightBotZ = -24;
	translationObstacle3 = 0;

	obstacle4LeftBotX = 20;
	obstacle4LeftBotZ = 2;
	obstacle4LeftTopX = 20;
	obstacle4LeftTopZ = 3;
	obstacle4RighBotX = 19;
	obstacle4RightBotZ = 2;

	obstacle5LeftBotX = -2;
	obstacle5LeftBotZ = -10;
	obstacle5LeftTopX = -2;
	obstacle5LeftTopZ = -9;
	obstacle5RighBotX = -3;
	obstacle5RightBotZ = -10;

	obstacle6LeftBotX = -19;
	obstacle6LeftBotZ = -15;
	obstacle6LeftTopX = -19;
	obstacle6LeftTopZ = -14;
	obstacle6RighBotX = -20;
	obstacle6RightBotZ = -15;

	finishLeftBotX = 0.1f;
	finishLeftBotZ = -24;
	finishRighBotX = -0.1f;
	finishRightBotZ = -24;
	finishLeftTopX = 0.1f;
	finishLeftTopZ = -19;

	// camera TPS
	positionAuxTPS = glm::vec3(0, 2, -3);
	centerTPS = glm::vec3(0, 1, 0);
	upTPS = glm::vec3(0, 1, 0);

	// camera FPS
	initialPosFPS = 1.2f;
	positionAuxFPS = glm::vec3(0, 0.5f, initialPosFPS);
	centerFPS = glm::vec3(0, 0.25f, 3);
	upFPS = glm::vec3(0, 1, 0);

	polygonMode = GL_FILL;
	renderCameraTarget = true;

	cameraTPS = new Laborator::Camera();
	cameraTPS->Set(positionAuxTPS, centerTPS, upTPS);

	cameraFPS = new Laborator::Camera();
	cameraFPS->Set(positionAuxFPS, centerFPS, upFPS);

	camera = cameraTPS; // initially we set our camera to 'Third Person'

	// adding some meshes
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("car");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "car.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("wheel");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "wheel.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(initAngle, window->props.aspectRatio, 0.01f, 200.0f);

	// Create a simple cube
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube", vertices, indices);

		// simple square
		vector<VertexFormat> vertices_square =
		{
			VertexFormat(glm::vec3(0.5f, 0, 0.5f), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(0.5f, 0, -0.5f), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-0.5f, 0, -0.5f), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-0.5f, 0, 0.5f), glm::vec3(0, 0, 0)),
		};

		vector<unsigned short> indices_square =
		{
			0, 1, 3,
			1, 2, 3,
		};

		CreateMesh("square", vertices_square, indices_square);

		// road 1 rectangle
		vector<VertexFormat> vertices_road1 =
		{
			VertexFormat(glm::vec3(2.5f, 0, 24), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(2.5f, 0, -24), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-2.5f, 0, -24), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-2.5f, 0, 24), glm::vec3(0, 0, 0)),
		};

		vector<unsigned short> indices_road1 =
		{
			0, 1, 3,
			1, 2, 3,
		};

		CreateMesh("road1", vertices_road1, indices_road1);

		// road 2 rectangle
		vector<VertexFormat> vertices_road2 =
		{
			VertexFormat(glm::vec3(2.5f, 0, 19), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(2.5f, 0, -19), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-2.5f, 0, -19), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-2.5f, 0, 19), glm::vec3(0, 0, 0)),
		};

		vector<unsigned short> indices_road2 =
		{
			0, 1, 3,
			1, 2, 3,
		};

		CreateMesh("road2", vertices_road2, indices_road2);

		// road 3 rectangle
		vector<VertexFormat> vertices_road3 =
		{
			VertexFormat(glm::vec3(3, 0, 19), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(3, 0, -4), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-3, 0, -4), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-3, 0, 19), glm::vec3(0, 0, 0)),
		};

		vector<unsigned short> indices_road3 =
		{
			0, 1, 3,
			1, 2, 3,
		};

		CreateMesh("road3", vertices_road3, indices_road3);

		// road 3 rectangle
		vector<VertexFormat> vertices_road_car_rect =
		{
			VertexFormat(glm::vec3(0.58f, 0, 1.27f), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(0.58f, 0, -1.2f), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-0.58f, 0, -1.2f), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-0.58f, 0, 1.27f), glm::vec3(0, 0, 0)),
		};

		vector<unsigned short> indices_road_car_rect =
		{
			0, 1, 3,
			1, 2, 3,
		};

		CreateMesh("carRect", vertices_road_car_rect, indices_road_car_rect);
	}

	// shader program for drawing day-night cycle
	{
		Shader *shader = new Shader("DayTransitionShader");
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

// creating a mesh
Mesh* Laborator5::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec2)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator5::Update(float deltaTimeSeconds)
{
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode); // for wireframe

	// add time for color transition
	clock = (float) (Engine::GetElapsedTime());

	// front-wheels get Angle
	if (!reverseCar) { // front wheels' angle if the car moves forward
		if (turnLeft) {
			steeringAngle = RADIANS(25.0f);
		}
		else if (turnRight) {
			steeringAngle = RADIANS(-25.0f);
		}
		else {
			steeringAngle = 0;
		}
	}
	else { // front wheels' angle if the car moves backward
		if (turnLeft) {
			steeringAngle = RADIANS(-25.0f);
		}
		else if (turnRight) {
			steeringAngle = RADIANS(25.0f);
		}
		else {
			steeringAngle = 0;
		}
	}

	// daytime transition skybox
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 24, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(100));

		// color based by time for the skybox
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.686f, 0.933f, 0.933f), glm::vec3(0.529f, 0.808f, 0.922f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.529f, 0.808f, 0.922f), glm::vec3(0.914f, 0.588f, 0.478f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.914f, 0.588f, 0.478f), glm::vec3(0.098f, 0.098f, 0.439f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.098f, 0.098f, 0.439f), glm::vec3(0.686f, 0.933f, 0.933f));
		}
	}

	// ground
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(200));

		// color based by time
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["square"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.565f, 0.933f, 0.565f), glm::vec3(0.235f, 0.702f, 0.443f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["square"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.235f, 0.702f, 0.443f), glm::vec3(0.133f, 0.545f, 0.13f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["square"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.133f, 0.545f, 0.13f), glm::vec3(0.000f, 0.392f, 0.000f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["square"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.000f, 0.392f, 0.000f), glm::vec3(0.565f, 0.933f, 0.565f));
		}
	}

	// Render the camera target. Useful for understanding where is the rotation point in Third-person camera movement
	if (renderCameraTarget)
	{
		// car
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
			RenderMesh(meshes["car"], shaders["VertexNormal"], modelMatrix);
		}

		//wheel right-back
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
			modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.51f, 0.17f, -0.64f)); // put in place on the car
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07f));
			modelMatrix = glm::rotate(modelMatrix, angularStep, glm::vec3(1, 0, 0)); // moving
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1)); // allign on the y axis
			RenderMesh(meshes["wheel"], shaders["VertexNormal"], modelMatrix);
		}

		// wheel right-front
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
			modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.51f, 0.17f, 0.65f)); // put in place on the car
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07f));
			modelMatrix = glm::rotate(modelMatrix, steeringAngle, glm::vec3(0, 1, 0)); // steering
			modelMatrix = glm::rotate(modelMatrix, angularStep, glm::vec3(1, 0, 0)); // moving
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1)); // allign on the y axis
			RenderMesh(meshes["wheel"], shaders["VertexNormal"], modelMatrix);
		}

		//wheel left-back
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
			modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.51f, 0.17f, -0.64f)); // put in place on the car
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07f));
			modelMatrix = glm::rotate(modelMatrix, angularStep, glm::vec3(1, 0, 0)); // moving
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 0, 1)); // allign on the y axis
			RenderMesh(meshes["wheel"], shaders["VertexNormal"], modelMatrix);
		}

		// wheel left-front
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
			modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.51f, 0.17f, 0.65f)); // put in place on the car
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07f));
			modelMatrix = glm::rotate(modelMatrix, steeringAngle, glm::vec3(0, 1, 0)); // steering
			modelMatrix = glm::rotate(modelMatrix, angularStep, glm::vec3(1, 0, 0)); // moving
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 0, 1)); // allign on the y axis
			RenderMesh(meshes["wheel"], shaders["VertexNormal"], modelMatrix);
		}
	}

	// calculate car corners (disclaimer: we use the same idea as we have done for the car wheels)
	// front left
	glm::mat4 modelMatrix = glm::mat4(1);
	glm::vec3 result;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
	modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
	result = modelMatrix * glm::vec4(initialCarFrontLeftX, 0, initialCarFrontLeftZ, 1); // put in place on the car
	carFrontLeftX = result.x;
	carFrontLeftZ = result.z;

	// front right
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
	modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
	result = modelMatrix * glm::vec4(initialCarFrontRightX, 0, initialCarFrontRightZ, 1); // put in place on the car
	carFrontRightX = result.x;
	carFrontRightZ = result.z;

	// back left
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
	modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
	result = modelMatrix * glm::vec4(initialCarBackLeftX, 0, initialCarBackLeftZ, 1); // put in place on the car
	carBackLeftX = result.x;
	carBackLeftZ = result.z;

	// back right
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, ty, tz)); // translate with the car
	modelMatrix = glm::rotate(modelMatrix, rotateAngle, glm::vec3(0, 1, 0)); // rotation
	result = modelMatrix * glm::vec4(initialCarBackRightX, 0, initialCarBackRightZ, 1); // put in place on the car
	carBackRightX = result.x;
	carBackRightZ = result.z;

	// check collision
	// upper border
	speedCollision = 1;
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(-24, 24), glm::vec2(24, 25))) {
		speedCollision = 0;
	}

	// left border
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(24, -24), glm::vec2(25, 24))) {
		speedCollision = 0;
	}

	// bottom border
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(-24, -25), glm::vec2(24, -24))) {
		speedCollision = 0;
	}

	// right border
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(-25, -24), glm::vec2(-24, 24))) {
		speedCollision = 0;
	}

	// low rectangle
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(-19, -19), glm::vec2(19, -10))) {
		speedCollision = 0;
	}

	// left rectangle
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(3, -4), glm::vec2(19, 19))) {
		speedCollision = 0;
	}

	// right rectangle
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(-19, -4), glm::vec2(-3, 19))) {
		speedCollision = 0;
	}

	// mid rectangle
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(-19, -5), glm::vec2(19, -4))) {
		speedCollision = 0;
	}

	// render borders
	// upper border
	for (int i = -25; i <= 24; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + i, 0.5f, 0.5f + 24));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// left border
	for (int i = -25; i <= 24; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + 24, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		
		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// bottom border
	for (int i = -24; i <= 25; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - i, 0.5f, 0.5f - 25));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		
		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// right border
	for (int i = -25; i <= 24; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - 25, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		
		if (abs(i) % 2 == 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// render roads
	// road1 left
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(21.5f, 0, 0));

		// color based by time
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.827f, 0.827f, 0.827f), glm::vec3(0.663f, 0.663f, 0.663f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.663f, 0.663f, 0.663f), glm::vec3(0.412f, 0.412f, 0.412f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.412f, 0.412f, 0.412f), glm::vec3(0.184f, 0.310f, 0.310f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.184f, 0.310f, 0.310f), glm::vec3(0.827f, 0.827f, 0.827f));
		}
	}

	// road1 right
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-21.5f, 0, 0));
		
		// color based by time
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.827f, 0.827f, 0.827f), glm::vec3(0.663f, 0.663f, 0.663f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.663f, 0.663f, 0.663f), glm::vec3(0.412f, 0.412f, 0.412f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.412f, 0.412f, 0.412f), glm::vec3(0.184f, 0.310f, 0.310f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["road1"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.184f, 0.310f, 0.310f), glm::vec3(0.827f, 0.827f, 0.827f));
		}
	}

	// road2 up
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 21.5f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
		
		// color based by time
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.827f, 0.827f, 0.827f), glm::vec3(0.663f, 0.663f, 0.663f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.663f, 0.663f, 0.663f), glm::vec3(0.412f, 0.412f, 0.412f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.412f, 0.412f, 0.412f), glm::vec3(0.184f, 0.310f, 0.310f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.184f, 0.310f, 0.310f), glm::vec3(0.827f, 0.827f, 0.827f));
		}
	}

	// road2 mid
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -7.5f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
		
		// color based by time
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.827f, 0.827f, 0.827f), glm::vec3(0.663f, 0.663f, 0.663f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.663f, 0.663f, 0.663f), glm::vec3(0.412f, 0.412f, 0.412f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.412f, 0.412f, 0.412f), glm::vec3(0.184f, 0.310f, 0.310f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.184f, 0.310f, 0.310f), glm::vec3(0.827f, 0.827f, 0.827f));
		}
	}

	// road2 down
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -21.5f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
		
		// color based by time
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.827f, 0.827f, 0.827f), glm::vec3(0.663f, 0.663f, 0.663f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.663f, 0.663f, 0.663f), glm::vec3(0.412f, 0.412f, 0.412f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.412f, 0.412f, 0.412f), glm::vec3(0.184f, 0.310f, 0.310f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["road2"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.184f, 0.310f, 0.310f), glm::vec3(0.827f, 0.827f, 0.827f));
		}
	}

	// road3
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		
		// color based by time
		if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
			RenderSimpleMesh(meshes["road3"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.827f, 0.827f, 0.827f), glm::vec3(0.663f, 0.663f, 0.663f));
		}
		else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
			RenderSimpleMesh(meshes["road3"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.663f, 0.663f, 0.663f), glm::vec3(0.412f, 0.412f, 0.412f));
		}
		else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
			RenderSimpleMesh(meshes["road3"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.412f, 0.412f, 0.412f), glm::vec3(0.184f, 0.310f, 0.310f));
		}
		else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
			RenderSimpleMesh(meshes["road3"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.184f, 0.310f, 0.310f), glm::vec3(0.827f, 0.827f, 0.827f));
		}
	}

	// low gap of ground
	// upper border for low gap
	for (int i = -18; i <= 19; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - i, 0.5f, 0.5f - 11));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// bottom border for low gap
	for (int i = -18; i <= 19; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - i, 0.5f, 0.5f - 19));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// left border for low gap
	for (int i = -18; i <= -12; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + 18, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// right border for low gap
	for (int i = -18; i <= -12; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - 19, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// up gap
	// bottom border for up gap
	for (int i = -18; i <= 19; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - i, 0.5f, 0.5f - 5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// left border for up gap
	for (int i = -4; i <= 18; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + 18, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// left mid border for up gap
	for (int i = -4; i <= 18; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + 3, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// right mid border for up gap
	for (int i = -4; i <= 18; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - 4, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 1) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// right border for up gap
	for (int i = -4; i <= 18; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f - 19, 0.5f, 0.5f + i));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// upper border left for up gap
	for (int i = 4; i <= 17; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + i, 0.5f, 0.5f + 18));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// upper border right for up gap
	for (int i = -18; i <= -5; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f + i, 0.5f, 0.5f + 18));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		if (abs(i) % 2 == 0) {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		}
		else {
			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0.894f, 0.372f, 0.321f), glm::vec3(0.894f, 0.372f, 0.321f));
		}
	}

	// finish line
	for (int i = 0; i < 5; i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, -19.5f - i));
		RenderSimpleMesh(meshes["square"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	}

	// obstacles (first three are dynamic -> they translate, the last three are static)
	if (!collisionObstacle1)
	{
		// collision top one
		if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(obstacle1RighBotX - translationObstacle1, obstacle1RightBotZ), glm::vec2(obstacle1LeftTopX - translationObstacle1, obstacle1LeftTopZ))) {
			speedCollision = 0;
			collisionObstacle1 = true;
		}

		// top one
		{
			if (translationObstacle1 > 5 || translationObstacle1 < 0) {
				reverseTranslation1 *= -1;
			}

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(obstacle1LeftBotX - 0.5f - translationObstacle1, 0.5f, obstacle1LeftBotZ + 0.5f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			translationObstacle1 += reverseTranslation1 * deltaTimeSeconds;

			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		}
	}

	if (!collisionObstacle2)
	{
		// collision bottom one
		if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(obstacle2RighBotX, obstacle2RightBotZ - translationObstacle2), glm::vec2(obstacle2LeftTopX, obstacle2LeftTopZ - translationObstacle2))) {
			speedCollision = 0;
			collisionObstacle2 = true;
		}

		// bottom one
		{
			if (translationObstacle2 > 4 || translationObstacle2 < 0) {
				reverseTranslation2 *= -1;
			}

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(obstacle2LeftBotX - 0.5f, 0.5f, obstacle2LeftBotZ + 0.5f - translationObstacle2));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			translationObstacle2 += reverseTranslation2 * deltaTimeSeconds;

			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		}
	}

	if (!collisionObstacle3)
	{
		// collision bottom two
		if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(obstacle3RighBotX, obstacle3RightBotZ + translationObstacle3), glm::vec2(obstacle3LeftTopX, obstacle3LeftTopZ + translationObstacle3))) {
			speedCollision = 0;
			collisionObstacle3 = true;
		}

		// bottom two
		{
			if (translationObstacle3 > 4 || translationObstacle3 < 0) {
				reverseTranslation3 *= -1;
			}

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(obstacle3LeftBotX - 0.5f, 0.5f, obstacle3LeftBotZ + 0.5f + translationObstacle3));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			translationObstacle3 += reverseTranslation3 * deltaTimeSeconds;

			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		}
	}

	if (!collisionObstacle4)
	{
		// collision top static
		if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(obstacle4RighBotX, obstacle4RightBotZ), glm::vec2(obstacle4LeftTopX, obstacle4LeftTopZ))) {
			speedCollision = 0;
			collisionObstacle4 = true;
		}

		// top static
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(obstacle4LeftBotX - 0.5f, 0.5f, obstacle4LeftBotZ + 0.5f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		}
	}

	if (!collisionObstacle5)
	{
		// collision mid static
		if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(obstacle5RighBotX, obstacle5RightBotZ), glm::vec2(obstacle5LeftTopX, obstacle5LeftTopZ))) {
			speedCollision = 0;
			collisionObstacle5 = true;
		}

		// mid static
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(obstacle5LeftBotX - 0.5f, 0.5f, obstacle5LeftBotZ + 0.5f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		}
	}

	if (!collisionObstacle6)
	{
		// collision bottom static
		if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(obstacle6RighBotX, obstacle6RightBotZ), glm::vec2(obstacle6LeftTopX, obstacle6LeftTopZ))) {
			speedCollision = 0;
			collisionObstacle6 = true;
		}

		// bottom static
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(obstacle6LeftBotX - 0.5f, 0.5f, obstacle6LeftBotZ + 0.5f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

			RenderSimpleMesh(meshes["cube"], shaders["DayTransitionShader"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		}
	}

	// check if arrived on the finish line
	if (isRectangleCollision(glm::vec2(carFrontLeftX, carFrontLeftZ), glm::vec2(carFrontRightX, carFrontRightZ), glm::vec2(carBackLeftX, carBackLeftZ), glm::vec2(carBackRightX, carBackRightZ), glm::vec2(finishRighBotX, finishRightBotZ), glm::vec2(finishLeftTopX, finishLeftTopZ))) {
		speedCollision = 0;
		finish = true;
	}

	// check for collision and calculate the score if the game is over
	if ((oldSpeedCollision == 1 && speedCollision == 0)) {
		if (finish) {
			float finalTime = (float)(Engine::GetElapsedTime());
			printf("Congrats! YOU WON with %d life(s) remaining!\n", lifes);
			printf("Your Time: %f seconds\n", finalTime);
			printf("Yor final score: %f points\n", (score + 42) + pow(0.9, roundf(finalTime * 10) - 100) * 100000 + 4321); // bonus score for your finish
			printf("You can now close the game app...\n");
		}
		else {
			lifes--;
			score -= 1000;
			printf("Oops! You collided! -1000 points for that :P\n");
			printf(" %d life(s) remaining...\n\n", lifes);
			if (lifes == 0) {
				printf("GAME OVER!\n");
				printf("You played for: %f seconds\n", (float)(Engine::GetElapsedTime()));
				printf("Yor final score: %f points\n", score + 42);
				printf("You can now close the game app...\n");
			}
		}
	}

	oldSpeedCollision = speedCollision; // keep count of the last speed collision at each frame
}

void Laborator5::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix); // drawing the coordinate system
}

void Laborator5::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 colourVec, glm::vec3 colourVec2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location_model = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	int location_view = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	int location_projection = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrixSet = projectionMatrix;
	glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrixSet));

	// clock value transmitting for day-night cycle
	int location_clock = glGetUniformLocation(shader->program, "Clock");
	if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= 0 && sinf(clock / 8.0) < 1) {
		glUniform1f(location_clock, abs(sinf(clock / 8.0)));
	}
	else if (cosf(clock / 8.0) > -1 && cosf(clock / 8.0) <= 0 && sinf(clock / 8.0) > 0 && sinf(clock / 8.0) <= 1) {
		glUniform1f(location_clock, abs(cosf(clock / 8.0)));
	}
	else if (cosf(clock / 8.0) >= -1 && cosf(clock / 8.0) < 0 && sinf(clock / 8.0) > -1 && sinf(clock / 8.0) <= 0) {
		glUniform1f(location_clock, abs(sinf(clock / 8.0)));
	}
	else if (cosf(clock / 8.0) >= 0 && cosf(clock / 8.0) < 1 && sinf(clock / 8.0) >= -1 && sinf(clock / 8.0) < 0) {
		glUniform1f(location_clock, abs(cosf(clock / 8.0)));
	}

	// initial and final colors for the object (between transition)
	int location_color_vec = glGetUniformLocation(shader->program, "ColourVec");
	glUniform3fv(location_color_vec, 1, glm::value_ptr(colourVec));
	int location_color_vec2 = glGetUniformLocation(shader->program, "ColourVec2");
	glUniform3fv(location_color_vec2, 1, glm::value_ptr(colourVec2));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_V)) {
			// TODO : translate the camera up
			initAngle += deltaTime;
			projectionMatrix = glm::perspective(initAngle, window->props.aspectRatio, 0.01f, 200.0f);
		}

		if (window->KeyHold(GLFW_KEY_B)) {
			// TODO : translate the camera up
			initAngle -= deltaTime;
			projectionMatrix = glm::perspective(initAngle, window->props.aspectRatio, 0.01f, 200.0f);
		}
	}
	
	if (!finish && lifes > 0) // game is not over
	{
		speed *= speedCollision; // in case of collision

		if (window->KeyHold(GLFW_KEY_UP)) { // moving forward
			if (speed >= maxSpeed) { // speed limit
				tz += speed * cosf(rotateAngle) * deltaTime; // based on rotation
				tx += speed * sinf(rotateAngle) * deltaTime; // based on rotation
				cameraTPS->MoveForward(speed * deltaTime);
				cameraFPS->MoveForward(speed * deltaTime);
				angularStep += deltaTime;
			}
			else if (speed > 0) { // accelerate
				tz += speed * cosf(rotateAngle) * deltaTime; // based on rotation
				tx += speed * sinf(rotateAngle) * deltaTime; // based on rotation
				cameraTPS->MoveForward(speed * deltaTime);
				cameraFPS->MoveForward(speed * deltaTime);
				angularStep += deltaTime;
				speed += acceleration * deltaTime;
			}
			else { // start to move
				speed = initialSpeed;
			}
		}

		if (window->KeyHold(GLFW_KEY_DOWN)) { // braking or moving backward
			if (speed > 0 && !reverseCar) { // not going backward
				tz += speed * cosf(rotateAngle) * deltaTime;
				tx += speed * sinf(rotateAngle) * deltaTime;
				cameraTPS->MoveForward(speed * deltaTime);
				cameraFPS->MoveForward(speed * deltaTime);
				angularStep += deltaTime;
				speed -= decelerationBreak * deltaTime; // braking
			}
			else {
				reverseCar = true;
			}

			if (reverseCar) {
				// moving backward at constant speed
				tz -= speedReverse * cosf(rotateAngle) * deltaTime;
				tx -= speedReverse * sinf(rotateAngle) * deltaTime;
				cameraTPS->MoveForward(-speedReverse * deltaTime);
				cameraFPS->MoveForward(-speedReverse * deltaTime);
				angularStep -= deltaTime;
			}
		}
		else {
			reverseCar = false;
		}

		// car inertia when not accelerating or braking
		if (speed > 0 && !window->KeyHold(GLFW_KEY_UP) && !window->KeyHold(GLFW_KEY_DOWN)) {
			tz += speed * cosf(rotateAngle) * deltaTime;
			tx += speed * sinf(rotateAngle) * deltaTime;
			cameraTPS->MoveForward(speed * deltaTime);
			cameraFPS->MoveForward(speed * deltaTime);
			angularStep += deltaTime;
			speed -= deceleration * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_LEFT)) { // steering left
			turnLeft = true; // wheels are steered
			rotateAngle += deltaTime;
			// update cameras
			if (renderCameraTarget) {
				cameraTPS->RotateThirdPerson_OY(deltaTime);
				cameraFPS->MoveForward(-initialPosFPS);
				cameraFPS->RotateFirstPerson_OY(deltaTime);
				cameraFPS->MoveForward(initialPosFPS);
			}
			else {
				cameraFPS->MoveForward(-initialPosFPS);
				cameraFPS->RotateFirstPerson_OY(deltaTime);
				cameraFPS->MoveForward(initialPosFPS);
				cameraTPS->RotateThirdPerson_OY(deltaTime);
			}

		}
		else {
			turnLeft = false;
		}

		if (window->KeyHold(GLFW_KEY_RIGHT)) { // steering right
			turnRight = true; // wheels are steered
			rotateAngle -= deltaTime;
			// update cameras
			if (renderCameraTarget) {
				cameraFPS->MoveForward(-initialPosFPS);
				cameraFPS->RotateFirstPerson_OY(-deltaTime);
				cameraFPS->MoveForward(initialPosFPS);
				cameraTPS->RotateThirdPerson_OY(-deltaTime);
			}
			else {
				cameraFPS->MoveForward(-initialPosFPS);
				cameraFPS->RotateFirstPerson_OY(-deltaTime);
				cameraFPS->MoveForward(initialPosFPS);
				cameraTPS->RotateThirdPerson_OY(-deltaTime);
			}
		}
		else {
			turnRight = false;
		}
	}
}

void Laborator5::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_O)
	{
		projectionMatrix = glm::ortho(-rightOrto, rightOrto, upOrto, -upOrto, 0.0f, 200.0f);
	}

	if (key == GLFW_KEY_P)
	{
		projectionMatrix = glm::perspective(initAngle, window->props.aspectRatio, 0.01f, 200.0f);
	}

	if (key == GLFW_KEY_SPACE) // wireframe mode switching
	{
		switch (polygonMode)
		{
		case GL_LINE:
			polygonMode = GL_FILL;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}

	if (key == GLFW_KEY_X) // switch cameras
	{
		renderCameraTarget = !renderCameraTarget;
		if (renderCameraTarget) {
			camera = cameraTPS;
		}
		else {
			camera = cameraFPS;
		}
	}

	if (key == GLFW_KEY_L) // rerender obstacles
	{
		collisionObstacle1 = false;
		collisionObstacle2 = false;
		collisionObstacle3 = false;
		collisionObstacle4 = false;
		collisionObstacle5 = false;
		collisionObstacle6 = false;
	}
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * deltaX);
		}

	}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height)
{
}
