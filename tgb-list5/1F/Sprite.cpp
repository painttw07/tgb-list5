#include "Sprite.h"

void Sprite::setSpritesheet(GLuint texID, int nAnimations, int nFrames)
{
	this->texID = texID;
	this->nAnimations = nAnimations;
	this->nFrames = nFrames;

	iFrame = 0;
	iAnimation = 0;

	dx = 1.0 / (float)nFrames;
	dy = 1.0 / (float)nAnimations;
	float vertices[] = {
		
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   dx, dy, 
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   dx, 0.0f, 
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, dy  
	};

	unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3 
	};

	GLuint VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	transform = glm::mat4(1);
	position = glm::vec3(0.0, 0.0, 0.0);
	scale = glm::vec3(1.0, 1.0, 1.0);
	angle = 0.0;
	shader = NULL;

}

void Sprite::update()
{
	shader->Use();

	setTranslation(position, true);
	setRotation(angle, glm::vec3(0.0, 0.0, 1.0));
	setScale(scale);

	shader->setMat4("model", glm::value_ptr(transform));

	GLint offsetLoc = glGetUniformLocation(shader->Program, "offset");
	glUniform2f(offsetLoc, iFrame * dx, iAnimation * dy);

	iFrame = (iFrame + 1) % nFrames;
}

glm::vec4 Sprite::getRectangle()
{
	return glm::vec4();
}
