#ifndef __DISKMODULE_H__
#define __DISKMODULE_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class DISKMODULE
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	DISKMODULE(int x, int y);

	// Destructor
	virtual ~DISKMODULE();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	bool Has_Scored = false;
	bool Is_Caught = false;
	bool On_Ground = true;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

	enum class Disk_Status {
		PlayerHolds,
		PlayerCatch,
		PlayerThrow,
		IsMoving,
		HitsGoal,
		HitsSide,
		OnGround,
	};

};

#endif // __DISKMODULE_H__
#pragma once
