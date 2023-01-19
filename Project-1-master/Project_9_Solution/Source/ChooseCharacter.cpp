#include "ChooseCharacter.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ChooseCharacter::ChooseCharacter(bool startEnabled) : Module(startEnabled)
{
	p1.PushBack({359, 11, 20, 16});

	p2.PushBack({ 392, 11, 23, 16 });

	//CharacterType::Turf;
	xMove1 = 9;		xMove2 = 39;
	yMove1 = 72;	yMove2 = 72;
}

ChooseCharacter::~ChooseCharacter()
{

}

bool ChooseCharacter::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	////CharacterType::Turf;
	//xMove1 = 9;		xMove2 = 39;
	//yMove1 = 72;	yMove2 = 72;

	currentAnimation1 = &p1;
	currentAnimation2 = &p2;

	chooseCharacterTexture = App->textures->Load("Assets/Spriteswind/Sprites/UI/choose_character_screen.png");
	playerIcon = App->textures->Load("Assets/Spriteswind/Sprites/UI/UISpriteSheetFinal.png");

	App->audio->PlayMusic("Assets/Music/001 Windjammers _ Flying Power Disc (wjammers) [#002] Get Ready! (Select).ogg", 1.0f);

	changeOption = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/UI/ChangeOption.wav");

	App->LockedinP1 = Player_Locked::NotLocked;
	App->LockedinP2 = Player_Locked::NotLocked;

	chooseJapAudio = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/JapaneseCharacter/Japanese_1.wav");
	chooseGerAudio = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/GermanCharacter/German_1.wav");
	chooseEngAudio = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/EnglishCharacter/English_select.wav");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status ChooseCharacter::Update()
{
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && App->LockedinP1 != Player_Locked::Locked1)
	{
		if (xMove1 == 9 && yMove1 == 72)
		{
			xMove1 = 9; yMove1 = 128;
		}
		App->audio->PlayFx(changeOption);
	}
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN && App->LockedinP1 != Player_Locked::Locked1)
	{
		if (xMove1 == 9 && yMove1 == 128)
		{
			xMove1 = 9; yMove1 = 72;
		}
		App->audio->PlayFx(changeOption);
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN && App->LockedinP1 != Player_Locked::Locked1)
	{
		if (xMove1 == 9 && yMove1 == 72)
		{
			xMove1 =  153; yMove1 = 72;
		}
		App->audio->PlayFx(changeOption);
	}
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN && App->LockedinP1 != Player_Locked::Locked1)
	{
		if (xMove1 == 153 && yMove1 == 72)
		{
			xMove1 = 9; yMove1 = 72;
		}
		App->audio->PlayFx(changeOption);
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && App->LockedinP2 != Player_Locked::Locked2)
	{
		if (xMove2 == 39 && yMove2 == 72)
		{
			xMove2 = 39; yMove2 = 128;
		}
		App->audio->PlayFx(changeOption);
	}
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN && App->LockedinP2 != Player_Locked::Locked2)
	{
		if (xMove2 == 39 && yMove2 == 128)
		{
			xMove2 = 39; yMove2 = 72;
		}
		App->audio->PlayFx(changeOption);
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN && App->LockedinP2 != Player_Locked::Locked2)
	{
		if (xMove2 == 39 && yMove2 == 72)
		{
			xMove2 = 183; yMove2 = 72;
		}
		App->audio->PlayFx(changeOption);
	}
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN && App->LockedinP2 != Player_Locked::Locked2)
	{
		if (xMove2 == 183 && yMove2 == 72)
		{
			xMove2 = 39; yMove2 = 72;
		}
		App->audio->PlayFx(changeOption);
	}

	/*if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->chooseMap, 40);
	}*/


	if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->LockedinP1 != Player_Locked::Locked1)
	{
		if (xMove1 == 9 && yMove1 == 72) {
			App->choice1 = Player_Chosen_Left::Japanese;
			App->LockedinP1 = Player_Locked::Locked1;
			App->audio->PlayFx(chooseJapAudio);
		}

		if (xMove1 == 9 && yMove1 == 128) {
			App->choice1 = Player_Chosen_Left::German;
			App->LockedinP1 = Player_Locked::Locked1;
			App->audio->PlayFx(chooseGerAudio);
		}

		if (xMove1 == 153 && yMove1 == 72) {
			App->choice1 = Player_Chosen_Left::English;
			App->LockedinP1 = Player_Locked::Locked1;
			App->audio->PlayFx(chooseEngAudio);
		}
	}

	if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->LockedinP2 != Player_Locked::Locked2)
	{
		if (xMove2 == 39 && yMove2 == 72) {
			App->choice2 = Player_Chosen_Right::Japanese;
			App->LockedinP2 = Player_Locked::Locked2;
			App->audio->PlayFx(chooseJapAudio);
		}

		if (xMove2 == 39 && yMove2 == 128) {
			App->choice2 = Player_Chosen_Right::German;
			App->LockedinP2 = Player_Locked::Locked2;
			App->audio->PlayFx(chooseGerAudio);
		}

		if (xMove2 == 183 && yMove2 == 72) {
			App->choice2 = Player_Chosen_Right::English;
			App->LockedinP2 = Player_Locked::Locked2;
			App->audio->PlayFx(chooseEngAudio);
		}
	}
	
	if (App->LockedinP1 == Player_Locked::Locked1 && App->LockedinP2 == Player_Locked::Locked2) {
		App->fade->FadeToBlack(this, (Module*)App->chooseMap, 90);
	}
	
	/*if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN) {
		inccheck1();
	}
	if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {
		inccheck2();
	}*/


	/*if (returncheck() == 1 && returncheck2() == 1) {
		App->fade->FadeToBlack(this, (Module*)App->chooseMap, 40);
		
	}*/

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ChooseCharacter::PostUpdate()
{

	SDL_Rect rect1 = currentAnimation1->GetCurrentFrame();
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	// Draw everything --------------------------------------
	App->render->Blit(chooseCharacterTexture, 0, 0, NULL);
	App->render->Blit(playerIcon, xMove1, yMove1, &rect1);
	App->render->Blit(playerIcon, xMove2, yMove2, &rect2);

	return Update_Status::UPDATE_CONTINUE;
}

bool ChooseCharacter::CleanUp()
{
	
	App->chooseCharacter->Disable();
	
	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	return true;
}