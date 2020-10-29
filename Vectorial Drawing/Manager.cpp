#include "Manager.h"



void Manager::createBSpline()
{
	float inc = 1.0f / 100.0f;
	float x, y, z;
	int size = controlPoints.size() /*!!!!!!!!!!!*/;

	for (int i = 0; i < size; i++) {
		for (int t = 0; t <= 1; t += inc) {
			x = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints[i]->x +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints[(i + 1) % size]->x +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints[(i + 2) % size]->x +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints[(i + 3) % size]->x) / 6);

			y = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints[i]->y +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints[(i + 1) % size]->y +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints[(i + 2) % size]->y +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints[(i + 3) % size]->y) / 6);

			z = (((-1 * pow(t, 3) + 3 * pow(t, 2) - 3 * t + 1) * controlPoints[i]->z +
				(3 * pow(t, 3) - 6 * pow(t, 2) + 0 * t + 4) * controlPoints[(i + 1) % size]->z +
				(-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) * controlPoints[(i + 2) % size]->z +
				(1 * pow(t, 3) + 0 * pow(t, 2) + 0 * t + 0) * controlPoints[(i + 3) % size]->z) / 6);

			curvePoints.push_back(x);
			curvePoints.push_back(y);
			curvePoints.push_back(z);
		}
	}
}

void Manager::initializeVAOsVBOs()
{
	/*glGenVertexArrays(1, &VAOcontrol);
	glGenBuffers(1, &VBOcontrol);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAOcontrol);

	glBindBuffer(GL_ARRAY_BUFFER, VBOcontrol);*/
}

GLuint Manager::controlPointsToVBO()
{
	std::vector<float> vertex;

	for (int i = 0; i < controlPoints.size(); i++) {
		glm::vec3* v = controlPoints[i];
		vertex.push_back(v->x);
		vertex.push_back(v->y);
		//vertex.push_back(v->z);
	}

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat),
		vertex.data(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	return VAO;
	//return VAOcontrol;
}

GLuint Manager::curvePointsToVBO()
{
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, curvePoints.size() * sizeof(GLfloat),
		curvePoints.data(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	return VAO;
}

std::vector<glm::vec3*> Manager::getControlPoints()
{
	return controlPoints;
}

void Manager::addControlPoint(glm::vec3* point)
{
	controlPoints.push_back(point);
}
