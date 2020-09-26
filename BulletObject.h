#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

class BulletObject : public GameObject
{
public:
	GLboolean Stuck;
	glm::vec2 Angle;

	BulletObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
	void Move(GLfloat dt, glm::vec2 fromPosition);
	void Move(GLfloat dt);
	void Reset(glm::vec2 position);
};

#endif