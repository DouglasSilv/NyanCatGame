
#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

class EnemyObject : public GameObject
{
public:

	GLboolean Stuck;

	EnemyObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
	void Move(GLfloat dt);
	void Reset(glm::vec2 position);
};

#endif