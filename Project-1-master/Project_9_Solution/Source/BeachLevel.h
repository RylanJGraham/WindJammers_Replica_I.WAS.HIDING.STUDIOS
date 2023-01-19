#ifndef __BeachLevel_H__
#define __BeachLevel_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class BeachLevel : public Module
{
public:
	//Constructor
	BeachLevel(bool startEnabled);

	//Destructor
	~BeachLevel();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* uiSprites = nullptr;
	SDL_Texture* textureVS = nullptr;
	SDL_Texture* refTexture = nullptr;

	Animation refereeAnim;

	SDL_Rect winL;
	SDL_Rect winR;
	SDL_Rect loseL;
	SDL_Rect loseR;
	SDL_Rect time;

	Animation background;

	Animation leftJapanese;
	Animation leftGerman;
	Animation leftEnglish;
	Animation rightJapanese;
	Animation rightGerman;
	Animation rightEnglish;

	uint counter = 000;
	int counterFont = -1;
	char counterText[10] = { "\0" };
};

#endif
