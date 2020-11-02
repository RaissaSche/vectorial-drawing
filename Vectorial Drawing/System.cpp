#include "System.h"



System::System()
{
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
	manager->initializeVAOsVBOs();
	GLuint VAO = 0;
	int numPoints = 0;

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

#pragma region Input Handling

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

#pragma endregion	
		int colorInU = glGetUniformLocation(coreShader.program, "colorIn");

		glm::vec4 colorIn = glm::vec4(0.7f, 0.8f, 0.9f, 1.0f); //light blue
		glUniform4fv(colorInU, 1, glm::value_ptr(colorIn));

		const int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

		if (state == GLFW_PRESS) {
			double mx, my;
			glfwGetCursorPos(window, &mx, &my);
			numPoints = mouse(mx, my);

			if (numPoints >= 4) {
				manager->createBSpline();
				manager->createInternalCurve(10);
				manager->createExternalCurve(10);
			}
		}

		glClearColor(0.2f, 0.1f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		coreShader.Use();

		VAO = manager->controlPointsToVBO();
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, numPoints);
		glDrawArrays(GL_POINTS, 0, numPoints);
		glBindVertexArray(0);

		if (numPoints >= 4) {

			int curveNumPoints = manager->getCurvePoints().size() / 3;

			//bspline
			colorIn = glm::vec4(0.7f, 0.1f, 0.98f, 1.0f); //purple
			glUniform4fv(colorInU, 1, glm::value_ptr(colorIn));

			VAO = manager->curvePointsToVBO();
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, curveNumPoints);
			glBindVertexArray(0);

			//internal curve
			colorIn = glm::vec4(0.9f, 0.2f, 0.9f, 1.0f); //magenta
			glUniform4fv(colorInU, 1, glm::value_ptr(colorIn));

			VAO = manager->internalCurvePointsToVBO();
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, curveNumPoints);
			glBindVertexArray(0);

			//external curve
			colorIn = glm::vec4(0.3f, 0.3f, 1.0f, 1.0f); //blue
			glUniform4fv(colorInU, 1, glm::value_ptr(colorIn));

			VAO = manager->externalCurvePointsToVBO();
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, curveNumPoints);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
	}

}

void System::Finish()
{
	coreShader.Delete();

	glfwTerminate();
}

int System::mouse(double mx, double my)
{
	glm::vec3* mousePos = new glm::vec3(mx, HEIGHT - my, 0.0f);

	if (manager->getControlPoints().empty() || arePointsDifferent(mousePos)) {
		manager->addControlPoint(mousePos);
	}

	return manager->getControlPoints().size();
}

bool System::arePointsDifferent(glm::vec3* point) {

	glm::vec3* point2 = manager->getControlPoints().back();

	return point->x != point2->x && point->y != point2->y;
}
