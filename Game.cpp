#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "BackgroundObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#include "CloudObject.h"
#include "BulletObject.h"

SpriteRenderer* Renderer;
SpriteRenderer* RendererPlayer;

BackgroundObject* Background;
BackgroundObject* Background2;

CloudObject* Cloud;

PlayerObject* Player;

glm::vec2 BackgroundPosition;
glm::vec2 Background2Position;
glm::vec2 PlayerPosition;
glm::vec2 CloudPosition;

std::map<int, BulletObject*> Bullets;

std::map<int, EnemyObject*> Enemies;

std::map<int, glm::vec2> EnemiesPositions;

std::map<int, glm::vec2> BulletsPositions;

int enemyToShoot = 1;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

float GenerateRandomFloat(float min, float max)
{
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;

	float range = max - min;
	return (random * range) + min;
}

void Game::Init()
{
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 Projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", Projection);

	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");

	ResourceManager::LoadTexture("textures/cloud.png", GL_TRUE, "cloud");

	ResourceManager::LoadTexture("textures/nyancat.png", GL_TRUE, "nyancat");

	ResourceManager::LoadTexture("textures/dogenemy.png", GL_TRUE, "dogenemy");
	ResourceManager::LoadTexture("textures/hemanenemy.png", GL_TRUE, "hemanenemy");
	ResourceManager::LoadTexture("textures/pikachuenemy.png", GL_TRUE, "pikachuenemy");
	ResourceManager::LoadTexture("textures/bobenemy.png", GL_TRUE, "bobenemy");
	ResourceManager::LoadTexture("textures/feelsbadenemy.png", GL_TRUE, "feelsbadenemy");
	ResourceManager::LoadTexture("textures/iluminatienemy.png", GL_TRUE, "iluminatienemy");
	ResourceManager::LoadTexture("textures/patoenemy.png", GL_TRUE, "patoenemy");

	ResourceManager::LoadTexture("textures/star.png", GL_TRUE, "star");

	Shader Shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(Shader);

	BackgroundPosition = glm::vec2(0, 0);
	Background = new BackgroundObject(BackgroundPosition, glm::vec2(1280, this->Height), ResourceManager::GetTexture("background"));

	Background2Position = glm::vec2(1280, 0);
	Background2 = new BackgroundObject(Background2Position, glm::vec2((this->Width), (this->Height)), ResourceManager::GetTexture("background"));

	PlayerPosition = glm::vec2(200, 300);
	Player = new PlayerObject(PlayerPosition, ResourceManager::GetTexture("nyancat"));

	EnemiesPositions[1] = glm::vec2(1500, GenerateRandomFloat(0.0f, 650.0f));
	Enemies[1] = new EnemyObject(EnemiesPositions[1], glm::vec2(85, 85), ResourceManager::GetTexture("dogenemy"));

	EnemiesPositions[2] = glm::vec2(1725, GenerateRandomFloat(0.0f, 650.0f));
	Enemies[2] = new EnemyObject(EnemiesPositions[2], glm::vec2(163, 120), ResourceManager::GetTexture("hemanenemy"));

	EnemiesPositions[3] = glm::vec2(1950, GenerateRandomFloat(0.0f, 650.0f));
	Enemies[3] = new EnemyObject(EnemiesPositions[3], glm::vec2(100, 90), ResourceManager::GetTexture("pikachuenemy"));

	EnemiesPositions[4] = glm::vec2(2175, GenerateRandomFloat(0.0f, 650.0f));
	Enemies[4] = new EnemyObject(EnemiesPositions[4], glm::vec2(100, 90), ResourceManager::GetTexture("bobenemy"));

	EnemiesPositions[5] = glm::vec2(2400, GenerateRandomFloat(0.0f, 650.0f));
	Enemies[5] = new EnemyObject(EnemiesPositions[5], glm::vec2(100, 90), ResourceManager::GetTexture("feelsbadenemy"));

	EnemiesPositions[6] = glm::vec2(2625, GenerateRandomFloat(0.0f, 650.0f));
	Enemies[6] = new EnemyObject(EnemiesPositions[6], glm::vec2(100, 90), ResourceManager::GetTexture("iluminatienemy"));

	EnemiesPositions[7] = glm::vec2(2850, GenerateRandomFloat(0.0f, 650.0f));
	Enemies[7] = new EnemyObject(EnemiesPositions[7], glm::vec2(100, 90), ResourceManager::GetTexture("patoenemy"));

	CloudPosition = glm::vec2(1500, GenerateRandomFloat(0.0f, 520));
	Cloud = new CloudObject(CloudPosition, glm::vec2(400, 200), ResourceManager::GetTexture("cloud"));

	BulletsPositions[1] = glm::vec2(-30.0f, 0.0f);
	Bullets[1] = new BulletObject(BulletsPositions[1], glm::vec2(30, 30), ResourceManager::GetTexture("star"));

	BulletsPositions[2] = glm::vec2(-30.0f, 0.0f);
	Bullets[2] = new BulletObject(BulletsPositions[2], glm::vec2(30, 30), ResourceManager::GetTexture("star"));

	BulletsPositions[3] = glm::vec2(-30.0f, 0.0f);
	Bullets[3] = new BulletObject(BulletsPositions[3], glm::vec2(30, 30), ResourceManager::GetTexture("star"));
}

void Game::Update(GLfloat dt)
{
	Background->Move(Background);
	Background2->Move(Background2);

	Player->Move(dt, this->State);

	Cloud->Move(dt);

	for (int n = 1; n <= 7; n++) {
		Enemies[n]->Move(dt);
	}

	if (Player->Position.y > 900.0f) {
		this->State = GAME_ACTIVE;
		Background->Reset(BackgroundPosition);
		Background2->Reset(Background2Position);
		Player->Reset(PlayerPosition);

		for (int n = 1; n <= 7; n++) {
			Enemies[n]->Reset(EnemiesPositions[n]);
		}

		Cloud->Reset(CloudPosition);

		for (int n = 1; n <= 3; n++) {
			Bullets[n]->Reset(BulletsPositions[n]);
		}
	}

	for (int n = 1; n <= 3; n++) {
		if (!OnScreen(*Bullets[n])) {
			Bullets[n]->Move(dt, Enemies[enemyToShoot]->Position);
			enemyToShoot = (int) GenerateRandomFloat(1, 7);
		}
		else {
			Bullets[n]->Move(dt);
		}
	}

	this->DoCollisions();
}

GLboolean Game::OnScreen(GameObject& object)
{
	return object.Position.x > 0 && object.Position.x < this->Width && object.Position.y > 0 && object.Position.y < this->Height;
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_OVER) return;

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
	else if (this->State != GAME_OVER) {
		Player->Rotation = 0.0f;

		Player->Velocity.y = 0.0f;
	}
}

void Game::Render()
{
	Shader Shader = ResourceManager::GetShader("sprite");
	RendererPlayer = new SpriteRenderer(Shader, ((int) Player->SpriteCount) * 0.2f, ((int) Player->SpriteCount) * 0.2f + 0.2f);

	Background->Draw(*Renderer, 0.1f);
	Background2->Draw(*Renderer, 0.1f);

	Player->Draw(*RendererPlayer, 0.2f);

	for (int n = 1; n <= 7; n++) {
		Enemies[n]->Draw(*Renderer, 0.3f);
	}

	Cloud->Draw(*Renderer, 0.3f);

	for (int n = 1; n <= 3; n++) {
		Bullets[n]->Draw(*Renderer, 0.3f);
	}
}


void Game::DoCollisions()
{

	if (CheckCollision(*Player, *Enemies[1]) ||
		CheckCollision(*Player, *Enemies[2]) ||
		CheckCollision(*Player, *Enemies[3]) ||
		CheckCollision(*Player, *Enemies[4]) ||
		CheckCollision(*Player, *Enemies[5]) ||
		CheckCollision(*Player, *Enemies[6]) ||
		CheckCollision(*Player, *Enemies[7]) ||
		CheckCollision(*Player, *Bullets[1]) ||
		CheckCollision(*Player, *Bullets[2]) ||
		CheckCollision(*Player, *Bullets[3])) {
		Player->Velocity.y = 0.0f;
		this->State = GAME_OVER;
	}

}

GLboolean Game::CheckCollision(GameObject& one, GameObject& two)
{
	GLboolean collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;

	GLboolean collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;

	return collisionX && collisionY;
}
