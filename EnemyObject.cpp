
#include "EnemyObject.h"

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,              //posicao
		size,                      //size
		sprite,                    //sprite
		glm::vec3(1.0f),           //color
		glm::vec2(-300.0f, 0.0f)) { }

void EnemyObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}

void EnemyObject::Move(GLfloat dt)
{
	this->Position += this->Velocity * dt;

	if (this->Position.x < -200.0f) {
		this->Position.x = 1280.0f;
		this->Position.y = (float) rand() / (float) (RAND_MAX / (720 - this->Size.y));
	}
}
