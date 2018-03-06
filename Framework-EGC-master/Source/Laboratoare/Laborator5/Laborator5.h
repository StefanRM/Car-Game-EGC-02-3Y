#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"

class Laborator5 : public SimpleScene
{
	public:
		Laborator5();
		~Laborator5();

		void Init() override;

		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, glm::vec3 colourVec, glm::vec3 colourVec2);
		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		// check if a point is inside a rectangle
		bool isPointInRectangle(glm::vec2 point, glm::vec2 pointBackLeft, glm::vec2 pointFrontRight);

		// check if two rectangles collide
		bool isRectangleCollision(glm::vec2 point1FrontLeft, glm::vec2 point1FrontRight, glm::vec2 point1BackLeft, glm::vec2 point1BackRight, glm::vec2 point2BackLeft, glm::vec2 point2FrontRight);

	protected:
		GLenum polygonMode; // for wireframe
		Laborator::Camera *cameraTPS, *cameraFPS, *camera; // Third & First Person cameras, respectively the game camera
		glm::mat4 projectionMatrix;
		bool renderCameraTarget, reverseCar, turnLeft, turnRight; // indicators for rendering the car, moving backward and steering
		float initAngle = RADIANS(60), rightOrto = 8.0f, upOrto = -4.5f;
		float tx, ty, tz, angularStep, rotateAngle, speed, initialPosFPS, acceleration, deceleration, decelerationBreak, speedReverse, maxSpeed, initialSpeed, steeringAngle; // position of the car's center, wheel's angle while moving forward, initial position of FPS camera, acceleration, deceleration, deceleration while braking, speed on reverse moving, maximum speed, speed while starting, angle for wheels while steering

		glm::vec3 positionAuxTPS, positionAuxFPS; // cameras positions
		glm::vec3 upTPS, upFPS; // up vectors for cameras
		glm::vec3 centerTPS, centerFPS; // cameras' centers

		int speedCollision, oldSpeedCollision = 1; // value for collision speed indicators
		float clock; // measure elapsed time

		float carFrontLeftX, carFrontLeftZ, carFrontRightX, carFrontRightZ, carBackLeftX, carBackLeftZ, carBackRightX, carBackRightZ; // car's corners coordinates
		float initialCarFrontLeftX, initialCarFrontLeftZ, initialCarFrontRightX, initialCarFrontRightZ, initialCarBackLeftX, initialCarBackLeftZ, initialCarBackRightX, initialCarBackRightZ; // car's corners initial coordinates

		// obstacles coordinates
		float obstacle1LeftBotX, obstacle1LeftBotZ, obstacle1RighBotX, obstacle1RightBotZ, obstacle1LeftTopX, obstacle1LeftTopZ, translationObstacle1;
		float obstacle2LeftBotX, obstacle2LeftBotZ, obstacle2RighBotX, obstacle2RightBotZ, obstacle2LeftTopX, obstacle2LeftTopZ, translationObstacle2;
		float obstacle3LeftBotX, obstacle3LeftBotZ, obstacle3RighBotX, obstacle3RightBotZ, obstacle3LeftTopX, obstacle3LeftTopZ, translationObstacle3;
		float obstacle4LeftBotX, obstacle4LeftBotZ, obstacle4RighBotX, obstacle4RightBotZ, obstacle4LeftTopX, obstacle4LeftTopZ;
		float obstacle5LeftBotX, obstacle5LeftBotZ, obstacle5RighBotX, obstacle5RightBotZ, obstacle5LeftTopX, obstacle5LeftTopZ;
		float obstacle6LeftBotX, obstacle6LeftBotZ, obstacle6RighBotX, obstacle6RightBotZ, obstacle6LeftTopX, obstacle6LeftTopZ;
		float finishLeftBotX, finishLeftBotZ, finishRighBotX, finishRightBotZ, finishLeftTopX, finishLeftTopZ; // finish line
		int reverseTranslation1 = 1, reverseTranslation2 = 1, reverseTranslation3 = 1; // translation for dynamic obstacles
		bool collisionObstacle1 = false, collisionObstacle2 = false, collisionObstacle3 = false, collisionObstacle4 = false, collisionObstacle5 = false, collisionObstacle6 = false, finish = false; // collision detection for each obstacle

		int lifes = 3; // number of lifes
		float score = 0; // player's score
};
