
#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::UPPER_WALL][Collider::Type::UPPER_WALL] = false;
	matrix[Collider::Type::UPPER_WALL][Collider::Type::LOWER_WALL] = false;
	matrix[Collider::Type::UPPER_WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::UPPER_WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::UPPER_WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::UPPER_WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::UPPER_WALL][Collider::Type::DISK] = true;
	matrix[Collider::Type::UPPER_WALL][Collider::Type::PARABOLIC_DISK] = true;

	matrix[Collider::Type::LOWER_WALL][Collider::Type::UPPER_WALL] = false;
	matrix[Collider::Type::LOWER_WALL][Collider::Type::LOWER_WALL] = false;
	matrix[Collider::Type::LOWER_WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LOWER_WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LOWER_WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::LOWER_WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::LOWER_WALL][Collider::Type::DISK] = true;
	matrix[Collider::Type::LOWER_WALL][Collider::Type::PARABOLIC_DISK] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::UPPER_WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LOWER_WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LEFT_3P_GOAL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::RIGHT_3P_GOAL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DISK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PARABOLIC_DISK] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::UPPER_WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::LOWER_WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::LEFT_3P_GOAL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::RIGHT_3P_GOAL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::UPPER_WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LOWER_WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LEFT_3P_GOAL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RIGHT_3P_GOAL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::UPPER_WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LOWER_WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LEFT_3P_GOAL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RIGHT_3P_GOAL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::LEFT_3P_GOAL] = false;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::DISK] = true;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::PARABOLIC_DISK] = true;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::UPPER_WALL] = false;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::LOWER_WALL] = false;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::NET] = false;
	matrix[Collider::Type::LEFT_3P_GOAL][Collider::Type::LEFT_5P_GOAL] = false;

	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::LEFT_5P_GOAL] = false;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::DISK] = true;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::PARABOLIC_DISK] = true;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::UPPER_WALL] = false;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::LOWER_WALL] = false;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::NET] = false;
	matrix[Collider::Type::LEFT_5P_GOAL][Collider::Type::LEFT_3P_GOAL] = false;

	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::RIGHT_3P_GOAL] = false;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::DISK] = true;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::PARABOLIC_DISK] = true;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::UPPER_WALL] = false;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::LOWER_WALL] = false;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::NET] = false;
	matrix[Collider::Type::RIGHT_3P_GOAL][Collider::Type::RIGHT_5P_GOAL] = false;
	
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::RIGHT_5P_GOAL] = false;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::DISK] = true;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::PARABOLIC_DISK] = true;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::UPPER_WALL] = false;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::LOWER_WALL] = false;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::NET] = false;
	matrix[Collider::Type::RIGHT_5P_GOAL][Collider::Type::RIGHT_3P_GOAL] = false;

	matrix[Collider::Type::NET][Collider::Type::NET] = false;
	matrix[Collider::Type::NET][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::NET][Collider::Type::DISK] = false;
	matrix[Collider::Type::NET][Collider::Type::PARABOLIC_DISK] = false;
	matrix[Collider::Type::NET][Collider::Type::UPPER_WALL] = false;
	matrix[Collider::Type::NET][Collider::Type::LOWER_WALL] = false;
	matrix[Collider::Type::NET][Collider::Type::ENEMY] = true;

	matrix[Collider::Type::DISK][Collider::Type::DISK] = false;
	matrix[Collider::Type::DISK][Collider::Type::PARABOLIC_DISK] = false;
	matrix[Collider::Type::DISK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DISK][Collider::Type::NET] = false;
	matrix[Collider::Type::DISK][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::DISK][Collider::Type::UPPER_WALL] = true;
	matrix[Collider::Type::DISK][Collider::Type::LOWER_WALL] = true;
	matrix[Collider::Type::DISK][Collider::Type::LEFT_3P_GOAL] = true;
	matrix[Collider::Type::DISK][Collider::Type::RIGHT_3P_GOAL] = true;
	matrix[Collider::Type::DISK][Collider::Type::LEFT_5P_GOAL] = true;
	matrix[Collider::Type::DISK][Collider::Type::RIGHT_5P_GOAL] = true;
	
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::NET] = false;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::UPPER_WALL] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::LOWER_WALL] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::LEFT_3P_GOAL] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::RIGHT_3P_GOAL] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::LEFT_5P_GOAL] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::RIGHT_5P_GOAL] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::DISK] = true;
	matrix[Collider::Type::PARABOLIC_DISK][Collider::Type::PARABOLIC_DISK] = true;
	
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::UPPER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::LOWER_WALL: 
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::LEFT_3P_GOAL: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::LEFT_5P_GOAL: 
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
			case Collider::Type::RIGHT_3P_GOAL: 
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::RIGHT_5P_GOAL: 
			App->render->DrawQuad(colliders[i]->rect, 255, 55, 0, alpha);
			break;
			case Collider::Type::NET: // light blue
			App->render->DrawQuad(colliders[i]->rect, 100, 255, 255, alpha);
			break;
			case Collider::Type::DISK: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			case Collider::Type::PARABOLIC_DISK: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}