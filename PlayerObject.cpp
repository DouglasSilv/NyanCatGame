#include "PlayerObject.h"

PlayerObject::PlayerObject()
	: GameObject(), SpriteCount(0) { }

PlayerObject::PlayerObject(glm::vec2 pos, Texture2D sprite)
	: GameObject(pos,                   //posicao
		glm::vec2(120, 50),             //size
		sprite,                         //sprite
		glm::vec3(1.0f),                //color
		glm::vec2(0.0f, 0.0f)),         //velocity
	SpriteCount(0) { }

glm::vec2 PlayerObject::Move(GLfloat dt, GLuint window_width)
{
	// If not stuck to player board
	/*if (!this->Stuck)
	{
		// Move the ball
		this->Position += this->Velocity * dt;
		// Then check if outside window bounds and if so, reverse velocity and restore at correct position
		if (this->Position.x <= 0.0f)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0.0f;
		}
		else if (this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}
		if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
	}*/

	if (this->SpriteCount == 4) {
		this->SpriteCount = 0;
	}
	else {
		this->SpriteCount = this->SpriteCount + 1;
	}
	return this->Position;
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->SpriteCount = 0;
}