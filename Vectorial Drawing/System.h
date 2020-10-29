#ifndef SYSTEM_H
#define SYSTEM_H
#define GLEW_STATIC

// Internal
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>

// Headers
#include "Shader.h"
#include "Time.h"
#include "Manager.h"

class System
{
private:
	// Screen
	const GLint WIDTH = 800, HEIGHT = 600;
	int screenWidth, screenHeight;
	float lastX = 400, lastY = 300;
	bool firstMouse = true;
	Manager* manager;

public:
	GLFWwindow* window;
	Shader coreShader;

public:
	System();
	~System();

	int GLFWInit();
	int OpenGLSetup();
	int SystemSetup();

	void Run();

	void Finish();

	int mouse(double mx, double my);
	bool arePointsDifferent(glm::vec3* point);
};

#endif
