

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader& shader)
{
	this->shader = shader;
	this->posAnteriorX = 0.0f;
	this->posX = 1.0f;
	this->initRenderData();
}

SpriteRenderer::SpriteRenderer(Shader& shader, GLfloat posAnteriorX, GLfloat posX)
{
	this->shader = shader;
	this->posAnteriorX = posAnteriorX;
	this->posX = posX;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, GLfloat z, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	// Prepare transformations
	this->shader.Use();

	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, z)); //0.0f // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, z)); //0.0f // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, z)); //1.0f // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, z)); //0.0f // Move origin back

	model = glm::scale(model, glm::vec3(size, z)); //1.0f // Last scale

	this->shader.SetMatrix4("model", model);

	this->shader.SetFloat("offsetx", 0.0f);
	this->shader.SetFloat("offsety", 0.0f);

	// Render textured quad
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	//Ativando transparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SpriteRenderer::initRenderData()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, this->posAnteriorX, 1.0f,
		1.0f, 0.0f, this->posX, 0.0f,
		0.0f, 0.0f, this->posAnteriorX, 0.0f,

		0.0f, 1.0f, this->posAnteriorX, 1.0f,
		1.0f, 1.0f, this->posX, 1.0f,
		1.0f, 0.0f, this->posX, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Ativando transparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}