#include "PlayerObject.h"
#include <iostream>
#include <iomanip>

PlayerObject::PlayerObject()
	: GameObject(), SpriteCount(1) { }

PlayerObject::PlayerObject(glm::vec2 pos, Texture2D sprite)
	: GameObject(pos,  
		glm::vec2(120, 50),            
		sprite,                      
		glm::vec3(1.0f),               
		glm::vec2(0.0f, 0.0f)),        
	SpriteCount(1) { }

glm::vec2 PlayerObject::Move(GLfloat dt, GameState gameState)
{
	this->Position.y += this->Velocity.y * dt;

	if (this->SpriteCount >= 5) {
		this->SpriteCount = 1;
	}
	else {
		this->SpriteCount = this->SpriteCount + 0.2f;
	}

	if (gameState == GAME_OVER) {
		this->Rotation += 5.0f * dt;
		this->Position.y += 300.0f * dt;
	}

	return this->Position;
}

void PlayerObject::Reset(glm::vec2 position)
{
	this->Position = position;
	this->Rotation = 0;
	this->SpriteCount = 0;
}