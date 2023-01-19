#ifndef __DISC_H__
#define __DISC_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Collider.h"
#include "ChooseMap.h"

struct SDL_Texture;
struct Collider;



class Disc : public Module
{
public:
	// Constructor
	Disc(bool startEnabled);

	// Destructor
	~Disc();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new disc
	// Param disc	- A template disc from which the new disc will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	//Disc* AddDisc(const Disc& disc, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

public:
	// Defines the position in the screen
	iPoint position;

	// Defines the speed at which the disc will move (pixels per second)
	iPoint speed;

	MapType map = MapType::Turf;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentDiscAnimation = nullptr;

	// A set of rectangle sprites
	Animation turfDisc;
	Animation japaneseSuperShot;
	Animation germanSuperShot;
	Animation englishSuperShot;

	// Defines wether the disc is alive or not
	// Disc will be set to not alive until "spawnTime" is reached
	bool isAlive = false;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;

	bool HasDiskL = true;
	bool HasDiskR = false;

	// The particle's collider
	Collider* collider = nullptr;

private:

	SDL_Texture* texture = nullptr;

};

#endif //__DISC_H__
