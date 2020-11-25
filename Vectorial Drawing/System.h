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
#include "ObjManager.h"

class System
{
private:
	// Screen
	const GLint WIDTH = 800, HEIGHT = 600;
	int screenWidth, screenHeight;
	float lastX, lastY;
	bool firstMouse;
	bool editClick;
	double mx, my, numPoints;
	Manager* manager;
	ObjManager* objManager;

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
};

#endif
