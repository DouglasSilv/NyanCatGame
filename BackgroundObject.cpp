
#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,              //posicao
		size,                      //size
		sprite,                    //sprite
		glm::vec3(1.0f),           //color
		glm::vec2(0.04f, 0.0f)),   //velocity
	Stuck(false) { }

void BackgroundObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = false;
}

void BackgroundObject::Move(BackgroundObject* background)
{
	background->Position.x -= 10.0f ;
	if (background->Position.x <= -1279.0f) {
		background->Position.x = 1279.0f;
	}
}
