#include "System.h"



System::System()
{
	lastX = 400;
	lastY = 300;
	firstMouse = true;
	editClick = false;
	mx = 0;
	my = 0;
	numPoints = 0;
}


System::~System()
{
}

int System::GLFWInit()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vectorial Drawing", nullptr, nullptr);

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed no init GLEW." << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	return EXIT_SUCCESS;

}

int System::OpenGLSetup()
{

	glEnable(GL_BLEND);	// Enables blending ( glBlendFunc )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glPointSize(10.0f);

	//glfwSetKeyCallback(window, keyCallback);

	return EXIT_SUCCESS;
}

int System::SystemSetup()
{

	coreShader = Shader("Shaders/Core/core.vert", "Shaders/Core/core.frag");
	coreShader.Use();

	return EXIT_SUCCESS;
}

void System::Run()
{
	glm::mat4 ortho = glm::mat4(1.0f);
	ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -0.1f, 100.0f);

	int orthoU = glGetUniformLocation(coreShader.program, "ortho");
	glUniformMatrix4fv(orthoU, 1, GL_FALSE, glm::value_ptr(ortho));
	int loc = glGetUniformLocation(coreShader.program, "model");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	coreShader.Use();

	manager = new Manager();
	manager->setWindowHeight(HEIGHT);
	manager->getCurveManager()->initializeVAOsVBOs();
	objManager = new ObjManager();
	GLuint VAO = 0;

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		bool isPressed = false;

#pragma region Input Handling

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			manager->setEdit(true);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			manager->setEdit(false);
		}

		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
			if (manager->getEdit() && editClick) {
				manager->editPoints(mx, my, numPoints);
				manager->addHeight();
				manager->createCurves();
				if (numPoints >= 4) {
					objManager->createObj(manager->getCurveManager());
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
			if (manager->getEdit() && editClick) {
				manager->editPoints(mx, my, numPoints);
				manager->subtractHeight();
				manager->createCurves();
				if (numPoints >= 4) {
					objManager->createObj(manager->getCurveManager());
				}
			}
		}

#pragma endregion	

		const int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

		if (state == GLFW_PRESS) {
			glfwGetCursorPos(window, &mx, &my);
			numPoints = manager->mouse(mx, my);

			if (manager->getEdit()) {
				editClick = true;
			}
			else {
				editClick = false;
				if (numPoints >= 4) {
					manager->createCurves();
					objManager->createObj(manager->getCurveManager());
					objManager->createBSplinePointsTxt(manager->getCurveManager());
				}
			}
		}

		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		coreShader.Use();

		VAO = manager->getCurveManager()->controlPointsToVBO();
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, numPoints);
		glDrawArrays(GL_POINTS, 0, numPoints);
		glBindVertexArray(0);

		if (numPoints >= 4) {

			int curveNumPoints = manager->getCurveManager()->getBSplineCurvePoints().size() / 3;

			//bspline
			VAO = manager->getCurveManager()->curvePointsToVBO();
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, curveNumPoints);
			glBindVertexArray(0);

			//internal curve
			VAO = manager->getCurveManager()->internalCurvePointsToVBO();
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, curveNumPoints);
			glBindVertexArray(0);

			//external curve
			VAO = manager->getCurveManager()->externalCurvePointsToVBO();
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, curveNumPoints);
			glBindVertexArray(0);

			objManager->createObj(manager->getCurveManager());
			objManager->createBSplinePointsTxt(manager->getCurveManager());
		}

		glfwSwapBuffers(window);
	}

}

void System::Finish()
{
	coreShader.Delete();

	glfwTerminate();
}
