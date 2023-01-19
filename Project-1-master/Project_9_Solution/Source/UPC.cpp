#include "UPC.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

UPC::UPC(bool startEnabled) : Module(startEnabled)
{
	
}

UPC::~UPC()
{

}

// Load assets
bool UPC::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Spriteswind/Sprites/UI/InitialScreen.png");
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status UPC::Update()
{
	//Normal execution with all of the screens
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 40);
	}
	//Go to: DE screen
	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN) 
	{
		App->fade->FadeToBlack(this, (Module*)App->dataEast, 40);
	}
	//Go to: Main screen
	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->mainScreen, 40);
	}
	//Go to: tutorial screen
	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->tutorialScene, 40);
	}
	//Go to: character selection screen
	if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->chooseCharacter, 40);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status UPC::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool UPC::CleanUp()
{
	if (bgTexture != nullptr) {
		App->textures->Unload(bgTexture);
	}
	
	return true;
}