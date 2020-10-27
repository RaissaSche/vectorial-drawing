#include "Manager.h"



GLuint Manager::pointsToVBO()
{
	std::vector<float> vertex;

	for (int i = 0; i < points.size(); i++) {
		glm::vec2* v = points[i];
		vertex.push_back(v->x);
		vertex.push_back(v->y);
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
}

std::vector<glm::vec2*> Manager::getPoints()
{
	return points;
}

void Manager::setPoints(std::vector<glm::vec2*> points)
{
	this->points = points;
}

void Manager::addPoint(glm::vec2* point)
{
	points.push_back(point);
}
