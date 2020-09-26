#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Game.h"

class PlayerObject : public GameObject
{
public:
	float SpriteCount = 1;
	PlayerObject();
	PlayerObject(glm::vec2 pos, Texture2D sprite);
	PlayerObject(glm::vec2 pos, Texture2D sprite, glm::vec2 posTexture);
	glm::vec2 Move(GLfloat dt, GameState gameState);
	void Reset(glm::vec2 position);

	GLfloat TexturePosX = 1.0f / 3.0f;
};

#endif