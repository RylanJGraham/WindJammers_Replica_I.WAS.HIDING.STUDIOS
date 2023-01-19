#ifndef __LEFT_ENGLISH_PLAYER_H__
#define __LEFT_ENGLISH_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class LeftEnglishPlayer : public Module
{
public:
	// Constructor
	LeftEnglishPlayer(bool startEnabled);

	// Destructor
	~LeftEnglishPlayer();

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

	uint getEngScoreL() { return scoreEngLeft; }

	void Movement();

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;
	int speedslide = 0.75;
	int speedcross = 0.25;
	int slidetickinit;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* shadowTexture = nullptr;

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
	Animation loseAnim;
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
	Animation throwTURF;
	Animation throwCLAY;
	Animation throwBEACH;
	Animation ScoredOn;
	Animation Scored;
	Animation diskHoldTURF;
	Animation diskHoldCLAY;
	Animation diskHoldBEACH;
	Animation shadowAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint slidingSFX = 0;
	uint discThrowSFX = 0;
	uint diskCollisionSFX = 0;
	uint goalSFX = 0;
	uint crowdGoalSFX = 0;
	uint crowdWinSFX = 0;

	uint referee3ptsSFX = 0;
	uint referee5ptsSFX = 0;

	// Font score index
	uint scoreEngLeft = 000;
	int scoreEngFontLeft = -1;
	char scoreEngTextLeft[10] = { "\0" };

	//Detect if has disc
	bool hasDisk = true;

	//God Mode
	bool godMode = false;

	int timevic;
	int timedef;

	//int slidetickinit;
	int throwtickinit;
	bool throwingdisk;

	bool inslide = false;

	bool isDefeated = false;
	bool isCelebrating = false;

	bool scored3 = false;

	bool inAnim = false;
};

#endif //!__LEFT_ENGLISH_PLAYER_H__
