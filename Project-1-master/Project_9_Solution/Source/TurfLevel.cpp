#include "TurfLevel.h"
#include <SDL/include/SDL.h>

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "Left_Japanese_Player.h"
#include "Right_Japanese_Player.h"
#include "LeftGermanPlayer.h"
#include "RightGermanPlayer.h"
#include "LeftEnglishPlayer.h"
#include "RightEnglishPlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "UI.h"

#include "ModuleParticles.h"

#include <stdio.h>

TurfLevel::TurfLevel(bool startEnabled) : Module(startEnabled)
{

	background.PushBack({ 0, 0, 304, 224 });
	background.PushBack({ 304, 0, 304, 224 });
	background.PushBack({ 608, 0, 304, 224 });
	background.PushBack({ 912, 0, 304, 224 });
	background.speed = 0.07f;
	background.loop = true;

	refereeAnim.PushBack({ 304, 0, 304, 224 });
	refereeAnim.speed = 0.1f;
	refereeAnim.loop = true;


	// VS players
	leftJapanese.PushBack({ 366, 113, 120, 54 });
	leftJapanese.loop = true;
	leftJapanese.speed = 0.1f;

	leftGerman.PushBack({ 205, 117, 123, 54 });
	leftGerman.loop = true;
	leftGerman.speed = 0.1f;

	leftEnglish.PushBack({ 57, 119, 124, 55 });
	leftEnglish.loop = true;
	leftEnglish.speed = 0.1f;

	rightJapanese.PushBack({ 366, 50, 122, 53 });
	rightJapanese.loop = true;
	rightJapanese.speed = 0.1f;

	rightGerman.PushBack({ 208, 49, 124, 55 });
	rightGerman.loop = true;
	rightGerman.speed = 0.1f;

	rightEnglish.PushBack({ 56, 46, 126, 56 });
	rightEnglish.loop = true;
	rightEnglish.speed = 0.1f;


	winR = {224, 86, 100, 32};
	winL = {324, 86, 112, 32};
	loseR = {393, 27, 99, 27};
	loseL = {0, 54, 100, 27};
	time = {175, 11, 15, 5 };
}

TurfLevel::~TurfLevel()
{

}

// Load assets
bool TurfLevel::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Spriteswind/Sprites/TURF_SPRITES/TurfMap_spritesheet.png");
	uiSprites = App->textures->Load("Assets/Spriteswind/Sprites/UI/UISpriteSheetFinal.png");

	refTexture = App->textures->Load("Assets/Spriteswind/Sprites/TURF_SPRITES/TURF_JUDGE/JudgeTURF_spritesheet.png");
	textureVS = App->textures->Load("Assets/Spriteswind/Sprites/UI/Character_versus_screen.png");


	char lookupTable[] = { "0123456789" };
	counter = App->fonts->Load("Assets/Fonts/.png", lookupTable, 1);

	App->audio->PlayMusic("Assets/Music/turf.ogg", 1.0f);

	///TURF MAP Colliders
	App->collisions->Enable();
	//Upperside collider
	App->collisions->AddCollider({ 0, 0, 304, 40 }, Collider::Type::UPPER_WALL);
	//Bottomside collider
	App->collisions->AddCollider({ 0, 199, 304, 25 }, Collider::Type::LOWER_WALL);
	//Leftside 3points goal
	App->collisions->AddCollider({ 0, 17, 10, 88 }, Collider::Type::LEFT_3P_GOAL);
	App->collisions->AddCollider({ 0, 151, 10, 66 }, Collider::Type::LEFT_3P_GOAL);
	//Leftside 5points goal
	App->collisions->AddCollider({ 0, 105, 5, 46 }, Collider::Type::LEFT_5P_GOAL);
	//Rightside 3points goal
	App->collisions->AddCollider({ 295, 17, 10, 88 }, Collider::Type::RIGHT_3P_GOAL);
	App->collisions->AddCollider({ 295, 151, 10, 66 }, Collider::Type::RIGHT_3P_GOAL);
	//Rightside 5points goal
	App->collisions->AddCollider({ 300, 105, 5, 46 }, Collider::Type::RIGHT_5P_GOAL);
	//Center net
	App->collisions->AddCollider({ 151, 32, 3, 171 }, Collider::Type::NET);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	switch (App->choice1)
	{
	case Player_Chosen_Left::German:
		App->leftgermanyplayer->Enable();
		break;
	case Player_Chosen_Left::Japanese:
		App->LeftJapanesePlayer->Enable();
		break;
	case Player_Chosen_Left::English:
		App->leftenglishplayer->Enable();
		break;
	}

	switch (App->choice2)
	{
	case Player_Chosen_Right::German:
		App->rightgermanyplayer->Enable();
		break;
	case Player_Chosen_Right::Japanese:
		App->RightJapanesePlayer->Enable();
		break;
	case Player_Chosen_Right::English:
		App->righenglishplayer->Enable();
		break;
	}

	App->enemies->Enable();
	App->ui->Enable();
	
	//case Player_Chosen_Right::Spanish:
	//	/*	App->leftgermanyplayer->Enable();*/
	//	break;

	
	//App->leftgermanyplayer->Enable();
	//App->LeftJapanesePlayer->Enable();
	//App->rightgermanyplayer->Enable();
	//
	//App->rightgermanyplayer->Enable();

	return ret;
}

Update_Status TurfLevel::Update()
{
	background.Update();
	refereeAnim.Update();

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->dataEast, 90);

		App->LeftJapanesePlayer->scoreJapLeft = 0;
		App->RightJapanesePlayer->scoreJapRight = 0;
		App->leftgermanyplayer->scoreGerLeft = 0;
		App->rightgermanyplayer->scoreGerRight = 0;
		App->leftenglishplayer->scoreEngLeft = 0;
		App->righenglishplayer->scoreEngRight = 0;

		App->ui->counterLeftScore = 0;
		App->ui->leftScore = 0;
		App->ui->counterRightScore = 0;
		App->ui->rightScore = 0;
	}
	
	

	leftJapanese.Update();
	leftGerman.Update();
	leftEnglish.Update();
	rightJapanese.Update();
	rightGerman.Update();
	rightEnglish.Update();
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status TurfLevel::PostUpdate()
{
	// Draw everything --------------------------------------
	// Animation of the public
	App->render->Blit(bgTexture, 0, 0, &(background.GetCurrentFrame()), 0.5f);
	
	//Referee
	SDL_Rect rect = refereeAnim.GetCurrentFrame();
	App->render->Blit(refTexture, 0, 0, &rect);

	//VS players
	if (counter < 150) {
		if (App->LeftJapanesePlayer->IsEnabled()) {
			SDL_Rect leftJapaneseRect = leftJapanese.GetCurrentFrame();
			App->render->Blit(textureVS, 30, 40, &leftJapaneseRect);
		}
		else if (App->leftgermanyplayer->IsEnabled()) {
			SDL_Rect leftGermanRect = leftGerman.GetCurrentFrame();
			App->render->Blit(textureVS, 30, 40, &leftGermanRect);
		}
		else if (App->leftenglishplayer->IsEnabled()) {
			SDL_Rect leftEnglishRect = leftEnglish.GetCurrentFrame();
			App->render->Blit(textureVS, 30, 40, &leftEnglishRect);
		}

		if (App->RightJapanesePlayer->IsEnabled()) {
			SDL_Rect rightJapaneseRect = rightJapanese.GetCurrentFrame();
			App->render->Blit(textureVS, 150, 40, &rightJapaneseRect);
		}
		else if (App->rightgermanyplayer->IsEnabled()) {
			SDL_Rect rightGermanRect = rightGerman.GetCurrentFrame();
			App->render->Blit(textureVS, 150, 40, &rightGermanRect);
		}
		else if (App->righenglishplayer->IsEnabled()) {
			SDL_Rect rightEnglishRect = rightEnglish.GetCurrentFrame();
			App->render->Blit(textureVS, 150, 40, &rightEnglishRect);
		}
	}
	counter++;

	return Update_Status::UPDATE_CONTINUE;
}


bool TurfLevel::CleanUp()
{
	
	Player_Chosen_Right::NONE;
	Player_Chosen_Left::NONE;

	App->LockedinP1 == Player_Locked::NotLocked;
	App->LockedinP2 == Player_Locked::NotLocked;

	App->leftgermanyplayer->Disable();
	App->LeftJapanesePlayer->Disable();
	App->rightgermanyplayer->Disable();
	App->RightJapanesePlayer->Disable();
	App->righenglishplayer->Disable();
	App->leftenglishplayer->Disable();
	App->collisions->Disable();
	App->turflevel->Disable();
	App->enemies->Disable();
	App->ui->Disable();

	return true;
}