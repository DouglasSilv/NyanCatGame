#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


const GLuint SCREEN_WIDTH = 1280;

const GLuint SCREEN_HEIGHT = 720;

Game NyanCatGame(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NyanCat Game", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();
	glGetError();

	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	NyanCatGame.Init();

	NyanCatGame.State = GAME_ACTIVE;

	double previousTime = glfwGetTime();

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - previousTime;
		if (deltaTime > 0.0) {
			previousTime = currentTime;
		}
		glfwPollEvents();

		NyanCatGame.ProcessInput(deltaTime);

		NyanCatGame.Update(deltaTime);

		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		NyanCatGame.Render();

		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			NyanCatGame.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			NyanCatGame.Keys[key] = GL_FALSE;
	}
}

#pragma once