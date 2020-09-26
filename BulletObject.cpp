
#include "BulletObject.h"

BulletObject::BulletObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,              //posicao
		size,                      //size
		sprite,                    //sprite
		glm::vec3(1.0f),           //color
		glm::vec2(-650.0f, -300.0f)) { 
	this->Rotation = 5.0f;
	this->Angle = glm::vec2(1.0f, 1.0f);
}

void BulletObject::Reset(glm::vec2 position)
{
	this->Position = position;
}

float RandomFloat(float min, float max)
{
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;

	float range = max - min;
	return (random * range) + min;
}

void BulletObject::Move(GLfloat dt, glm::vec2 fromPosition)
{
	this->Position = fromPosition;
	this->Angle = glm::vec2(RandomFloat(0.7f, 1.0f), RandomFloat(-0.5f, 0.5f));
	this->Move(dt);
}


void BulletObject::Move(GLfloat dt)
{
	this->Position += this->Angle * this->Velocity * dt;
}
