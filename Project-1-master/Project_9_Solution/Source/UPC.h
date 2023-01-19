#ifndef __UPC_H__
#define __UPC_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class UPC : public Module
{
public:
	//Constructor
	UPC(bool startEnabled);

	//Destructor
	~UPC();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
};

#endif
