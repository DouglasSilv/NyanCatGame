#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Game.h"

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class PlayerObject : public GameObject
{
public:
	// Ball state	
	float SpriteCount = 1;
	// Constructor(s)
	PlayerObject();
	PlayerObject(glm::vec2 pos, Texture2D sprite);
	PlayerObject(glm::vec2 pos, Texture2D sprite, glm::vec2 posTexture);
	// Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
	glm::vec2 Move(GLfloat dt, GameState gameState);
	// Resets the ball to original state with given position and velocity
	void Reset(glm::vec2 position);

	GLfloat TexturePosX = 1.0f / 3.0f;
};

#endif