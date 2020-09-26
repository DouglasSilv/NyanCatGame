
#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,
		size,
		sprite,
		glm::vec3(1.0f),
		glm::vec2(0.04f, 0.0f)),
	Stuck(false) { }

void BackgroundObject::Reset(glm::vec2 position)
{
	this->Position = position;
	this->Stuck = false;
}

void BackgroundObject::Move(BackgroundObject* background)
{
	background->Position.x -= 10.0f ;
	if (background->Position.x <= -1279.0f) {
		background->Position.x = 1279.0f;
	}
}
