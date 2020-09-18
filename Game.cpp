/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "BackgroundObject.h"

// Game-related State data
SpriteRenderer* Renderer;
SpriteRenderer* RendererPlayer;

BackgroundObject* Background;


Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	ResourceManager::LoadTexture("textures/Background.jpg", GL_TRUE, "background");

	glm::vec2 background1Pos = glm::vec2(0, 0);
	Background = new BackgroundObject(background1Pos, glm::vec2(1280, this->Height), ResourceManager::GetTexture("background"));
}

void Game::Update(GLfloat dt)
{
	Background->Move(Background);

	// Check for collisions
	this->DoCollisions();
}

void Game::ProcessInput(GLfloat dt)
{
	// Input
}

void Game::Render()
{
	Background->Draw(*Renderer, 0.1f);
}


void Game::DoCollisions()
{

	// Check all

}

GLboolean Game::CheckCollision(GameObject& one, GameObject& two)
{
	// Collision x-axis?
	GLboolean collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	GLboolean collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}
