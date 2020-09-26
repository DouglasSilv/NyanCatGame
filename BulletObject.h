/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
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
	// Ball state	
	GLboolean Stuck;

	glm::vec2 Angle;
	// Constructor(s)
	BulletObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
	// Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
	void Move(GLfloat dt, glm::vec2 fromPosition);

	void Move(GLfloat dt);
	// Resets the ball to original state with given position and velocity
	void Reset(glm::vec2 position);
};

#endif