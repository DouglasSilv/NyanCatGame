
#ifndef GAME_H

#define GAME_H
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameObject.h"

enum GameState {
	GAME_ACTIVE,
	GAME_OVER,
};

const GLfloat PLAYER_VELOCITY(500.0f);

class Game
{
public:

	GameState              State;
	GLboolean              Keys[1024];
	GLuint                 Width, Height;

	Game(GLuint width, GLuint height);
	~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();
	GLboolean CheckCollision(GameObject& one, GameObject& two);
	GLboolean OnScreen(GameObject& object);
};

#endif