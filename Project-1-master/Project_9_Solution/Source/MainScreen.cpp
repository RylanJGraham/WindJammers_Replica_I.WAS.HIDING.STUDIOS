#include "MainScreen.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

MainScreen::MainScreen(bool startEnabled) : Module(startEnabled)
{
	
	//Purple letters anim
	Letters.PushBack({ 255, 52, 258, 10 });
	Letters.PushBack({ 510, 47, 258, 11 });
	Letters.PushBack({ 765, 41, 258, 11 });
	Letters.PushBack({ 1020, 35, 258, 11 });
	Letters.PushBack({ 1275, 29, 258, 11 });
	Letters.PushBack({ 1530, 23, 258, 13 });
	Letters.PushBack({ 1785, 17, 258, 13 });
	Letters.PushBack({ 2040, 12, 258, 10 });
	Letters.PushBack({ 2295, 5, 258, 10 });
	Letters.PushBack({ 2550, 0, 258, 10 });
	Letters.speed = 0.5f;
	Letters.loop = false;

	//main logo anim
	Logo.PushBack({ 0, 96, 20, 26 });
	Logo.PushBack({ 294, 55, 294, 62 });
	Logo.PushBack({ 591, 53, 292, 69 });
	Logo.PushBack({ 888, 46, 292, 75 });
	Logo.PushBack({ 1186, 45, 288, 74 });
	Logo.PushBack({ 1482, 41, 280, 73 });
	Logo.PushBack({ 1776, 35, 280, 74 });
	Logo.PushBack({ 2086, 29, 280, 73 });
	Logo.PushBack({ 2360, 22, 285, 83 });
	Logo.PushBack({ 2653, 20, 286, 84 });
	Logo.PushBack({ 2947, 17, 288, 92 });
	Logo.PushBack({ 3239, 11, 288, 97 });
	Logo.PushBack({ 3826, 9, 284, 100 });
	Logo.PushBack({ 4119, 5, 285, 111 });
	Logo.PushBack({ 4412, 0, 281, 119 });
	Logo.PushBack({ 4705, 0, 288, 119 });
	Logo.PushBack({ 4998, 0, 281, 120 });
	Logo.PushBack({ 5291, 0, 285, 120 });
	Logo.PushBack({ 5584, 0, 285, 120 });
	Logo.PushBack({ 5877, 0, 285, 120 });
	Logo.PushBack({ 6170, 0, 285, 120 });
	Logo.PushBack({ 6463, 0, 285, 120 });
	Logo.PushBack({ 6756, 0, 285, 120 });
	Logo.PushBack({ 7049, 0, 285, 120 });
	Logo.PushBack({ 7341, 0, 285, 120 });
	Logo.PushBack({ 7635, 0, 285, 120 });
	Logo.PushBack({ 7928, 0, 285, 120 });
	Logo.PushBack({ 8220, 0, 285, 120 });
	Logo.PushBack({ 8514, 0, 285, 120 });
	Logo.PushBack({ 8807, 0, 285, 120 });
	Logo.speed = 0.6f;
	Logo.loop = false;
}

MainScreen::~MainScreen()
{

}

// Load assets
bool MainScreen::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bgTexture = App->textures->Load("Assets/Spriteswind/Sprites/UI/MainMenu.png");
	Lettersp = App->textures->Load("Assets/Spriteswind/Sprites/UI/Start3.png");
	Logow = App->textures->Load("Assets/Spriteswind/Sprites/UI/Start4.png");

	currentAnimation = &Logo;

	selectionSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/UI/Select.wav");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status MainScreen::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->chooseCharacter, 90);
		App->audio->PlayFx(selectionSFX);
	}

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status MainScreen::PostUpdate()
{
	SDL_Rect rect = Logo.GetCurrentFrame();
	SDL_Rect rect2 = Letters.GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(Logow, 15, 30, &rect, false);
	
	if (currentAnimation->GetLoopCount() >= 1) {
		currentAnimation = &Letters;
		App->render->Blit(Lettersp, 22, 35, &rect2, false);
	}
	
	return Update_Status::UPDATE_CONTINUE;
}