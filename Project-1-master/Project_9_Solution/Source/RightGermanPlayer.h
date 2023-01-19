#ifndef __RightGermanPlayer_H__
#define __RightGermanPlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class RightGermanPlayer : public Module
{
public:
	// Constructor
	RightGermanPlayer(bool startEnabled);

	// Destructor
	~RightGermanPlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void Movement();

	void PointsScored();

	void DASH();

	void throwing(){
		Throw.PushBack({ 161, 288, 23, 35 });
		Throw.PushBack({ 137, 288, 24, 35 });
		Throw.PushBack({ 107, 288, 30, 35 });
		Throw.PushBack({ 79, 288, 28, 35 });
		Throw.PushBack({ 49, 288, 30, 35 });
		Throw.PushBack({ 23, 288, 26, 35 });
		Throw.PushBack({ 49, 288, 30, 35 });
		Throw.PushBack({ 79, 288, 28, 35 });
		Throw.PushBack({ 1, 288, 22, 35 });
		Throw.loop = false;
		Throw.speed = 0.1f;
	}


	uint getGerScoreR() { return scoreGerRight; }

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;
	int speedslide = 40;
	int speedcross = 0.25;
	int t1;
	int slidetickinit;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture2 = nullptr;
	SDL_Texture* shadowTexture = nullptr;
	SDL_Texture* particlestexture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation victAnim;
	Animation SlideLAnim;
	Animation SlideRAnim;
	Animation SlideUAnim;
	Animation SlideDAnim;
	Animation UpRightAnim;
	Animation UpLeftAnim;
	Animation DownRightAnim;
	Animation DownLeftAnim;
	Animation SlideUpLeftAnim;
	Animation SlideUpRightAnim;
	Animation SlideDownRightAnim;
	Animation SlideDownLeftAnim;
	Animation Throw;
	Animation ScoredOn;
	Animation Scored;
	Animation HoldingAnim;
	Animation shadowAnim;
	Animation DiskCollisionBoundary;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	//God Mode
	bool godMode = false;

	bool isDefeated = false;
	bool isCelebrating = false;

	int timevic;
	int timedef;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
	uint ShotFx = 0;
	uint discThrowSFX = 0;
	bool hasDisk = false;
	bool inslide = false;
	uint slidingSFX = 0;
	uint diskCollisionSFX = 0;
	uint goalSFX = 0;
	uint crowdGoalSFX = 0;
	uint crowdWinSFX = 0;

	uint referee3ptsSFX = 0;
	uint referee5ptsSFX = 0;


	// Font score index
	uint scoreGerRight = 000;
	int scoreGerFontRight = -1;
	char scoreGerTextRight[10] = { "\0" };

};

#endif //!__RightGermanPlayer_H__ once

