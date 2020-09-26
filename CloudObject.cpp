
#include "CloudObject.h"

CloudObject::CloudObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,              //posicao
		size,                      //size
		sprite,                    //sprite
		glm::vec3(1.0f),           //color
		glm::vec2(-200.0f, 0.0f)) { }

void CloudObject::Reset(glm::vec2 position)
{
	this->Position = position;
}

void CloudObject::Move(GLfloat dt)
{
	this->Position += this->Velocity * dt;

	if (this->Position.x <= -500.0f) {
		this->Position.x = 1500.0f;
		this->Position.y = (float) rand() / (float)(RAND_MAX / 650);
	}
}
