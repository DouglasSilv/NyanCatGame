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
#include "PlayerObject.h"
#include "EnemyObject.h"

// Game-related State data
SpriteRenderer* Renderer;
SpriteRenderer* RendererPlayer;

BackgroundObject* Background;
BackgroundObject* Background2;

PlayerObject* Player;

EnemyObject* Enemy1;
EnemyObject* Enemy2;
EnemyObject* Enemy3;
EnemyObject* Enemy4;
EnemyObject* Enemy5;
EnemyObject* Enemy6;
EnemyObject* Enemy7;


Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");

	ResourceManager::LoadTexture("textures/nyancat.png", GL_TRUE, "nyancat");

	ResourceManager::LoadTexture("textures/dogenemy.png", GL_TRUE, "dogenemy");
	ResourceManager::LoadTexture("textures/hemanenemy.png", GL_TRUE, "hemanenemy");
	ResourceManager::LoadTexture("textures/pikachuenemy.png", GL_TRUE, "pikachuenemy");
	ResourceManager::LoadTexture("textures/bobenemy.png", GL_TRUE, "bobenemy");
	ResourceManager::LoadTexture("textures/feelsbadenemy.png", GL_TRUE, "feelsbadenemy");
	ResourceManager::LoadTexture("textures/iluminatienemy.png", GL_TRUE, "iluminatienemy");
	ResourceManager::LoadTexture("textures/patoenemy.png", GL_TRUE, "patoenemy");

	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);

	glm::vec2 backgroundPosition = glm::vec2(0, 0);
	Background = new BackgroundObject(backgroundPosition, glm::vec2(1280, this->Height), ResourceManager::GetTexture("background"));

	glm::vec2 background2Position = glm::vec2(1280, 0);
	Background2 = new BackgroundObject(background2Position, glm::vec2((this->Width), (this->Height)), ResourceManager::GetTexture("background"));

	glm::vec2 playerPosition = glm::vec2(200, 300);
	Player = new PlayerObject(playerPosition, ResourceManager::GetTexture("nyancat"));

	glm::vec2 enemy1Position = glm::vec2(1500, (float) rand() / (float) (RAND_MAX / 650));
	Enemy1 = new EnemyObject(enemy1Position, glm::vec2(85, 85), ResourceManager::GetTexture("dogenemy"));

	glm::vec2 enemy2Position = glm::vec2(1725, (float)rand() / (float)(RAND_MAX / 650));
	Enemy2 = new EnemyObject(enemy2Position, glm::vec2(163, 120), ResourceManager::GetTexture("hemanenemy"));

	glm::vec2 enemy3Position = glm::vec2(1950, (float)rand() / (float)(RAND_MAX / 650));
	Enemy3 = new EnemyObject(enemy3Position, glm::vec2(100, 90), ResourceManager::GetTexture("pikachuenemy"));

	glm::vec2 enemy4Position = glm::vec2(2175, (float)rand() / (float)(RAND_MAX / 650));
	Enemy4 = new EnemyObject(enemy4Position, glm::vec2(100, 90), ResourceManager::GetTexture("bobenemy"));

	glm::vec2 enemy5Position = glm::vec2(2400, (float)rand() / (float)(RAND_MAX / 650));
	Enemy5 = new EnemyObject(enemy5Position, glm::vec2(100, 90), ResourceManager::GetTexture("feelsbadenemy"));

	glm::vec2 enemy6Position = glm::vec2(2625, (float)rand() / (float)(RAND_MAX / 650));
	Enemy6 = new EnemyObject(enemy6Position, glm::vec2(100, 90), ResourceManager::GetTexture("iluminatienemy"));

	glm::vec2 enemy7Position = glm::vec2(2850, (float)rand() / (float)(RAND_MAX / 650));
	Enemy7 = new EnemyObject(enemy7Position, glm::vec2(100, 90), ResourceManager::GetTexture("patoenemy"));
}

void Game::Update(GLfloat dt)
{
	Background->Move(Background);
	Background2->Move(Background2);

	Player->Move(dt, this->State);

	Enemy1->Move(dt);
	Enemy2->Move(dt);
	Enemy3->Move(dt);
	Enemy4->Move(dt);
	Enemy5->Move(dt);
	Enemy6->Move(dt);
	Enemy7->Move(dt);

	// Check for collisions
	this->DoCollisions();
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->Keys[GLFW_KEY_W])	{
		if (Player->Position.y > 0) {
			Player->Velocity.y = -500.0f;
			if (Player->Rotation > -0.3f) {
				Player->Rotation -= 1.0f * dt;
			}
		}
		else {
			Player->Rotation = 0.0f;

			Player->Velocity.y = 0.0f;
		}
	} else if (this->Keys[GLFW_KEY_S]) {
		if (Player->Position.y < 670) {
			Player->Velocity.y = 500.0f;
			if (Player->Rotation < 0.3f) {
				Player->Rotation += 1.0f * dt;
			}
		}
		else {
			Player->Rotation = 0.0f;

			Player->Velocity.y = 0.0f;
		}
	}
	else if (this->State != GAME_OVERING) {
		Player->Rotation = 0.0f;

		Player->Velocity.y = 0.0f;
	}
}

void Game::Render()
{
	Shader shader = ResourceManager::GetShader("sprite");
	RendererPlayer = new SpriteRenderer(shader, ((int) Player->SpriteCount) * 0.2f, ((int) Player->SpriteCount) * 0.2f + 0.2f);

	Background->Draw(*Renderer, 0.1f);
	Background2->Draw(*Renderer, 0.1f);

	Player->Draw(*RendererPlayer, 0.2f);

	Enemy1->Draw(*Renderer, 0.2f);
	Enemy2->Draw(*Renderer, 0.2f);
	Enemy3->Draw(*Renderer, 0.2f);
	Enemy4->Draw(*Renderer, 0.2f);
	Enemy5->Draw(*Renderer, 0.2f);
	Enemy6->Draw(*Renderer, 0.2f);
	Enemy7->Draw(*Renderer, 0.2f);
}


void Game::DoCollisions()
{

	if (CheckCollision(*Player, *Enemy1) || 
		CheckCollision(*Player, *Enemy2) ||
		CheckCollision(*Player, *Enemy3) ||
		CheckCollision(*Player, *Enemy4) ||
		CheckCollision(*Player, *Enemy5) ||
		CheckCollision(*Player, *Enemy6) ||
		CheckCollision(*Player, *Enemy7)) {
		Background->Stuck = true;
		Background2->Stuck = true;
		this->State = GAME_OVERING;
	}

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
