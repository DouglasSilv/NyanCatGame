
#ifndef BACKGROUNDOBJECT_H
#define BACKGROUND_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

class BackgroundObject : public GameObject
{
public:
	GLboolean Stuck;

	BackgroundObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
	void Move(BackgroundObject* background);
	void Reset(glm::vec2 position);
};

#endif