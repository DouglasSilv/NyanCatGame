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

EnemyObject* Enemy1;
EnemyObject* Enemy2;
EnemyObject* Enemy3;
EnemyObject* Enemy4;
EnemyObject* Enemy5;
EnemyObject* Enemy6;
EnemyObject* Enemy7;

BulletObject* Bullet1;
BulletObject* Bullet2;
BulletObject* Bullet3;

glm::vec2 backgroundPosition;
glm::vec2 background2Position;
glm::vec2 playerPosition;
glm::vec2 enemy1Position;
glm::vec2 enemy2Position;
glm::vec2 enemy3Position;
glm::vec2 enemy4Position;
glm::vec2 enemy5Position;
glm::vec2 enemy6Position;
glm::vec2 enemy7Position;
glm::vec2 cloudPosition;
glm::vec2 bullet1Position;
glm::vec2 bullet2Position;
glm::vec2 bullet3Position;

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

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

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

	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);

	backgroundPosition = glm::vec2(0, 0);
	Background = new BackgroundObject(backgroundPosition, glm::vec2(1280, this->Height), ResourceManager::GetTexture("background"));

	background2Position = glm::vec2(1280, 0);
	Background2 = new BackgroundObject(background2Position, glm::vec2((this->Width), (this->Height)), ResourceManager::GetTexture("background"));

	playerPosition = glm::vec2(200, 300);
	Player = new PlayerObject(playerPosition, ResourceManager::GetTexture("nyancat"));

	enemy1Position = glm::vec2(1500, GenerateRandomFloat(0.0f, 650.0f));
	Enemy1 = new EnemyObject(enemy1Position, glm::vec2(85, 85), ResourceManager::GetTexture("dogenemy"));

	enemy2Position = glm::vec2(1725, GenerateRandomFloat(0.0f, 650.0f));
	Enemy2 = new EnemyObject(enemy2Position, glm::vec2(163, 120), ResourceManager::GetTexture("hemanenemy"));

	enemy3Position = glm::vec2(1950, GenerateRandomFloat(0.0f, 650.0f));
	Enemy3 = new EnemyObject(enemy3Position, glm::vec2(100, 90), ResourceManager::GetTexture("pikachuenemy"));

	enemy4Position = glm::vec2(2175, GenerateRandomFloat(0.0f, 650.0f));
	Enemy4 = new EnemyObject(enemy4Position, glm::vec2(100, 90), ResourceManager::GetTexture("bobenemy"));

	enemy5Position = glm::vec2(2400, GenerateRandomFloat(0.0f, 650.0f));
	Enemy5 = new EnemyObject(enemy5Position, glm::vec2(100, 90), ResourceManager::GetTexture("feelsbadenemy"));

	enemy6Position = glm::vec2(2625, GenerateRandomFloat(0.0f, 650.0f));
	Enemy6 = new EnemyObject(enemy6Position, glm::vec2(100, 90), ResourceManager::GetTexture("iluminatienemy"));

	enemy7Position = glm::vec2(2850, GenerateRandomFloat(0.0f, 650.0f));
	Enemy7 = new EnemyObject(enemy7Position, glm::vec2(100, 90), ResourceManager::GetTexture("patoenemy"));

	cloudPosition = glm::vec2(1500, GenerateRandomFloat(0.0f, 520));
	Cloud = new CloudObject(cloudPosition, glm::vec2(400, 200), ResourceManager::GetTexture("cloud"));

	bullet1Position = glm::vec2(-30.0f, 0.0f);
	Bullet1 = new BulletObject(bullet1Position, glm::vec2(30, 30), ResourceManager::GetTexture("star"));

	bullet2Position = glm::vec2(-30.0f, 0.0f);
	Bullet2 = new BulletObject(bullet2Position, glm::vec2(30, 30), ResourceManager::GetTexture("star"));

	bullet3Position = glm::vec2(-30.0f, 0.0f);
	Bullet3 = new BulletObject(bullet3Position, glm::vec2(30, 30), ResourceManager::GetTexture("star"));
}

EnemyObject* GetEnemyToShoot()
{
	if (enemyToShoot == 1) {
		return Enemy1;
	}
	else if (enemyToShoot == 2) {
		return Enemy2;
	}
	else if (enemyToShoot == 3) {
		return Enemy3;
	}
	else if (enemyToShoot == 4) {
		return Enemy4;
	}
	else if (enemyToShoot == 5) {
		return Enemy5;
	}
	else if (enemyToShoot == 6) {
		return Enemy6;
	}
	else {
		return Enemy7;
	}
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
	Cloud->Move(dt);

	if (Player->Position.y > 900.0f) {
		this->State = GAME_ACTIVE;
		Background->Reset(backgroundPosition);
		Background2->Reset(background2Position);
		Player->Reset(playerPosition);
		Enemy1->Reset(enemy1Position);
		Enemy2->Reset(enemy2Position);
		Enemy3->Reset(enemy3Position);
		Enemy4->Reset(enemy4Position);
		Enemy5->Reset(enemy5Position);
		Enemy6->Reset(enemy6Position);
		Enemy7->Reset(enemy7Position);
		Cloud->Reset(cloudPosition);
		Bullet1->Reset(bullet1Position);
		Bullet2->Reset(bullet2Position);
		Bullet3->Reset(bullet3Position);
	}

	if (!OnScreen(*Bullet1)) {
		Bullet1->Move(dt, GetEnemyToShoot()->Position);
		enemyToShoot = (int) GenerateRandomFloat(1, 7);
	} else {
		Bullet1->Move(dt);
	}

	if (!OnScreen(*Bullet2)) {
		Bullet2->Move(dt, GetEnemyToShoot()->Position);
		enemyToShoot = (int )GenerateRandomFloat(1, 7);
	}
	else {
		Bullet2->Move(dt);
	}

	if (!OnScreen(*Bullet3)) {
		Bullet3->Move(dt, GetEnemyToShoot()->Position);
		enemyToShoot = (int) GenerateRandomFloat(1, 7);
	}
	else {
		Bullet3->Move(dt);
	}

	// Check for collisions
	this->DoCollisions();
}

GLboolean Game::OnScreen(GameObject& object)
{
	return object.Position.x > 0 && object.Position.x < this->Width && object.Position.y > 0 && object.Position.y < this->Height;
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_OVERING) return;

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

	Enemy1->Draw(*Renderer, 0.3f);
	Enemy2->Draw(*Renderer, 0.3f);
	Enemy3->Draw(*Renderer, 0.3f);
	Enemy4->Draw(*Renderer, 0.3f);
	Enemy5->Draw(*Renderer, 0.3f);
	Enemy6->Draw(*Renderer, 0.3f);
	Enemy7->Draw(*Renderer, 0.3f);
	Cloud->Draw(*Renderer, 0.3f);
	Bullet1->Draw(*Renderer, 0.3f);
	Bullet2->Draw(*Renderer, 0.3f);
	Bullet3->Draw(*Renderer, 0.3f);
}


void Game::DoCollisions()
{

	if (CheckCollision(*Player, *Enemy1) || 
		CheckCollision(*Player, *Enemy2) ||
		CheckCollision(*Player, *Enemy3) ||
		CheckCollision(*Player, *Enemy4) ||
		CheckCollision(*Player, *Enemy5) ||
		CheckCollision(*Player, *Enemy6) ||
		CheckCollision(*Player, *Enemy7) ||
		CheckCollision(*Player, *Bullet1) ||
		CheckCollision(*Player, *Bullet2) ||
		CheckCollision(*Player, *Bullet3)) {
		Background->Stuck = true;
		Background2->Stuck = true;
		Player->Velocity.y = 0.0f;
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
