#include "DataEast.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

DataEast::DataEast(bool startEnabled) : Module(startEnabled)
{
	DElogo.PushBack({ 0, 41, 99, 33 });
	DElogo.PushBack({ 108, 41, 141, 32 });
	DElogo.PushBack({ 251, 41, 245, 29});
	DElogo.PushBack({ 502, 38, 245, 31});
	DElogo.PushBack({ 753, 35, 245, 44 });
	DElogo.PushBack({ 1004, 32, 245, 50 });
	DElogo.PushBack({ 1254, 29, 245, 54 });
	DElogo.PushBack({ 1506, 28, 245, 61 });
	DElogo.PushBack({ 1757, 25, 245, 70 });
	DElogo.PushBack({ 2008, 22, 245, 71 });
	DElogo.PushBack({ 2259, 19, 245, 75 });
	DElogo.PushBack({ 2510, 17, 245, 78 });
	DElogo.PushBack({ 3012, 15, 245, 86 });
	DElogo.PushBack({ 3268, 8, 246, 85 });
	DElogo.PushBack({ 3514, 6, 250, 88 });
	DElogo.PushBack({ 3765, 3, 251, 89 });
	DElogo.speed = 0.4f;
	DElogo.loop = false;
}

DataEast::~DataEast()
{

}

// Load assets
bool DataEast::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Spriteswind/Sprites/UI/MainMenu.png");
	DELogo = App->textures->Load("Assets/Spriteswind/Sprites/UI/Start2.png");


	currentAnimation = &DElogo;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status DataEast::Update()
{
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->mainScreen, 40);
	}

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status DataEast::PostUpdate()
{
	SDL_Rect rect = DElogo.GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(DELogo, 30, 65, &rect, false);

	return Update_Status::UPDATE_CONTINUE;
}