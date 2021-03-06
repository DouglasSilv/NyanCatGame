
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"


class SpriteRenderer
{
public:

	SpriteRenderer(Shader& shader);
	SpriteRenderer(Shader& shader, GLfloat posAnteriorX, GLfloat posX);

	~SpriteRenderer();

	void DrawSprite(Texture2D& texture, glm::vec2 position, GLfloat z, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:

	Shader shader;
	GLuint quadVAO;
	GLfloat posBeforeX;
	GLfloat posX;

	void initRenderData();
};

#endif
