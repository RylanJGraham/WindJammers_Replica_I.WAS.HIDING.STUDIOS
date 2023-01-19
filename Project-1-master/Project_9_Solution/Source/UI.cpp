#include "UI.h"


#include "SDL/include/SDL.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ChooseMap.h"
#include "ChooseCharacter.h"
#include "ModuleAudio.h"

#include "Left_Japanese_Player.h"
#include "Right_Japanese_Player.h"
#include "LeftGermanPlayer.h"
#include "RightGermanPlayer.h"
#include "LeftEnglishPlayer.h"
#include "RightEnglishPlayer.h"

#include "stdio.h"

UI::UI(bool startEnabled) : Module(startEnabled)
{
	winR = { 224, 86, 100, 32 };
	winL = { 324, 86, 112, 32 };
	loseR = { 393, 27, 99, 27 };
	loseL = { 0, 54, 100, 27 };
	time = { 175, 11, 15, 5 };
	sets_count = { 315, 27, 78, 27 };

	time_thirty.PushBack({ 192, 86, 32, 32 });
	time_thirty.PushBack({ 192, 86, 32, 32 });
	time_thirty.PushBack({ 192, 86, 32, 32 });
	time_thirty.loop = true;
	time_thirty.speed = 0.1f;

	time_fifteen.PushBack({ 376, 54, 32, 32 });
	time_fifteen.loop = true;
	time_fifteen.speed = 0.1f;

	time_ten.PushBack({ 344, 54, 32, 32 });
	time_ten.loop = true;
	time_ten.speed = 0.1f;

	time_nine.PushBack({ 128, 86, 32, 32 });
	time_nine.loop = true;
	time_nine.speed = 0.1f;

	time_eight.PushBack({ 96, 86, 32, 32 });
	time_eight.loop = true;
	time_eight.speed = 0.1f;

	time_seven.PushBack({ 64, 86, 32, 32 });
	time_seven.loop = true;
	time_seven.speed = 0.1f;

	time_six.PushBack({ 32, 86, 32, 32 });
	time_six.loop = true;
	time_six.speed = 0.1f;

	time_five.PushBack({ 0, 86, 32, 32 });
	time_five.loop = true;
	time_five.speed = 0.1f;

	time_four.PushBack({ 472, 54, 32, 32 });
	time_four.loop = true;
	time_four.speed = 0.1f;

	time_three.PushBack({ 440, 54, 32, 32 });
	time_three.loop = true;
	time_three.speed = 0.1f;

	time_two.PushBack({ 408, 54, 32, 32 });
	time_two.loop = true;
	time_two.speed = 0.1f;

	time_one.PushBack({ 312, 54, 32, 32 });
	time_one.loop = true;
	time_one.speed = 0.1f;
}

UI::~UI()
{

}

bool UI::Start()
{
	bool ret = true;

	t1 = SDL_GetTicks();

	currentAnimation = &time_thirty;

	numSets = 0;
	endSet = false;
	setCountedAlready = false;
	matchStarted = false;

	secondsAux = 6.0f;

	leftScore = 0;
	rightScore = 0;

	uiSprites = App->textures->Load("Assets/Spriteswind/Sprites/UI/UISpriteSheetFinal.png");

	char lookupTable1[] = { "0123456789" };
	char lookupTable2[] = { "0123456789GO" };
	char lookupTable3[] = { "0123456789UP" };
	char lookupTable4[] = { "0123" };

	ScoreFont = App->fonts->Load("Assets/Fonts/Score.png", lookupTable1, 1);
	scoreCounterFont = App->fonts->Load("Assets/Fonts/Score_Counter.png", lookupTable2, 1);
	timeCounterFont = App->fonts->Load("Assets/Fonts/Time_Counter.png", lookupTable3, 1);
	setsCountFont = App->fonts->Load("Assets/Fonts/SetsCount.png", lookupTable4, 1);
	
	winnerRefereeSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Referee/WinnerReferee.wav");
	whistleRefereeSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Referee/Whistle_1.wav");
	crowdWinSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Crowd/CrowdWin.wav");

	return ret;
}

Update_Status UI::Update()
{
	t2 = SDL_GetTicks();
	seconds = (t2 - t1) / 1000;

	if (secondsAux < 5.0f)
	{
			timeCounter = 0;
	}
	else
	{
		timeCounter = 30 - (int)seconds;

		if (endSet == true)
		{
			endSet = false;
			setCountedAlready = false;
			counterLeftScore = 0;
			counterRightScore = 0;
		}
	}

	if (timeCounter == 0 && matchStarted == true)
	{
		if (getCounterRightScore() > getCounterLeftScore() && setCountedAlready == false)
		{
			rightSets++;
			numSets++;
		}
		else if (getCounterRightScore() < getCounterLeftScore() && setCountedAlready == false)
		{
			leftSets++;
			numSets++;
		}

		t1 = SDL_GetTicks();

		if (endSet == false)
		{
			t1Aux = SDL_GetTicks();
			endSet = true;
			setCountedAlready = true;
		}
	}

	if (endSet == true)
	{
		t2Aux = SDL_GetTicks();
		secondsAux = (t2Aux - t1Aux) / 1000;
	}

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)	//Direct WIN (F3)
	{
		leftSets = 3;
		numSets = 3;
		
		//App->audio->PlayMusic("Assets/Music/GameOver.ogg");
		App->audio->PlayFx(winnerRefereeSFX);
		App->audio->PlayFx(crowdWinSFX);
		
		if (App->LeftJapanesePlayer->IsEnabled()) {
			App->LeftJapanesePlayer->currentAnimation = &App->LeftJapanesePlayer->victAnim;
			App->LeftJapanesePlayer->currentAnimation->Update();
		}
		else if (App->leftgermanyplayer->IsEnabled()) {
			App->leftgermanyplayer->currentAnimation = &App->leftgermanyplayer->victAnim;
			App->leftgermanyplayer->currentAnimation->Update();
		}
		else if (App->leftenglishplayer->IsEnabled()) {
			App->leftenglishplayer->currentAnimation = &App->leftenglishplayer->victAnim;
			App->leftenglishplayer->currentAnimation->Update();
		}
		
		if(App->map == MapType::Turf)
			App->fade->FadeToBlack((Module*)App->turflevel, (Module*)App->sceneIntro, 150);
		else if(App->map == MapType::Beach)
			App->fade->FadeToBlack((Module*)App->beachlevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Clay)
			App->fade->FadeToBlack((Module*)App->clay, (Module*)App->sceneIntro, 150);

		//Reset score to 0
		App->ui->counterLeftScore = 0;
		App->ui->leftScore = 0;
		App->ui->counterRightScore = 0;
		App->ui->rightScore = 0;
	}
	else if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) //Direct LOSE (F4)
	{
		rightSets = 3;
		numSets = 3;

		//App->audio->PlayMusic("Assets/Music/GameOver.ogg");
		App->audio->PlayFx(winnerRefereeSFX);
		App->audio->PlayFx(crowdWinSFX);

		if (App->LeftJapanesePlayer->IsEnabled()) {
			App->LeftJapanesePlayer->currentAnimation = &App->LeftJapanesePlayer->victAnim;
			App->LeftJapanesePlayer->currentAnimation->Update();
		}
		else if (App->leftgermanyplayer->IsEnabled()) {
			App->leftgermanyplayer->currentAnimation = &App->leftgermanyplayer->victAnim;
			App->leftgermanyplayer->currentAnimation->Update();
		}
		else if (App->leftenglishplayer->IsEnabled()) {
			App->leftenglishplayer->currentAnimation = &App->leftenglishplayer->victAnim;
			App->leftenglishplayer->currentAnimation->Update();
		}

		if (App->map == MapType::Turf)
			App->fade->FadeToBlack((Module*)App->turflevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Beach)
			App->fade->FadeToBlack((Module*)App->beachlevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Clay)
			App->fade->FadeToBlack((Module*)App->clay, (Module*)App->sceneIntro, 150);

		//Reset score to 0
		App->ui->counterLeftScore = 0;
		App->ui->leftScore = 0;
		App->ui->counterRightScore = 0;
		App->ui->rightScore = 0;
	}

	if (matchStarted == false)
	{
		matchStarted = true;
	}

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status UI::PostUpdate()
{
	// Draw UI 

	//Time
	App->render->Blit(uiSprites, 144, 13, &time);
	
	//Score
	sprintf_s(rightScoreText, 10, "%d", rightScore);
	App->fonts->BlitText(204, 8, ScoreFont, rightScoreText);//right

	sprintf_s(leftScoreText, 10, "%d", leftScore);
	App->fonts->BlitText(66, 8, ScoreFont, leftScoreText);//left
	
	//Counter Score
	sprintf_s(counterRightScoreText, 10, "%2d", counterRightScore);
	App->fonts->BlitText(162, 17, scoreCounterFont, counterRightScoreText);

	sprintf_s(counterLeftScoreText, 10, "%2d", counterLeftScore);
	App->fonts->BlitText(114, 17, scoreCounterFont, counterLeftScoreText);

	//Time Counter
	sprintf_s(timeCounterText, 10, "%2d", timeCounter);
	App->fonts->BlitText(145, 21, timeCounterFont, timeCounterText);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (timeCounter == 30)
	{
		if (currentAnimation != &time_thirty)
			{
				time_thirty.Reset();
				currentAnimation = &time_thirty;
			}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 15)
	{
		if (currentAnimation != &time_fifteen)
		{
			time_fifteen.Reset();
			currentAnimation = &time_fifteen;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 10)
	{
		if (currentAnimation != &time_ten)
		{
			time_ten.Reset();
			currentAnimation = &time_ten;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 9)
	{
		if (currentAnimation != &time_nine)
		{
			time_nine.Reset();
			currentAnimation = &time_nine;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 8)
	{
		if (currentAnimation != &time_eight)
		{
			time_eight.Reset();
			currentAnimation = &time_eight;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 7)
	{
		if (currentAnimation != &time_seven)
		{
			time_seven.Reset();
			currentAnimation = &time_seven;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 6)
	{
		if (currentAnimation != &time_six)
		{
			time_six.Reset();
			currentAnimation = &time_six;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 5)
	{
		if (currentAnimation != &time_five)
		{
			time_five.Reset();
			currentAnimation = &time_five;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 4)
	{
		if (currentAnimation != &time_four)
		{
			time_four.Reset();
			currentAnimation = &time_four;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 3)
	{
		if (currentAnimation != &time_three)
		{
			time_three.Reset();
			currentAnimation = &time_three;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 2)
	{
		if (currentAnimation != &time_two)
		{
			time_two.Reset();
			currentAnimation = &time_two;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}
	else if (timeCounter == 1)
	{
		if (currentAnimation != &time_one)
		{
			time_one.Reset();
			currentAnimation = &time_one;
		}
		App->render->Blit(uiSprites, 136, 8, &rect);
	}

	//Sets Count
	if (timeCounter == 0)
	{
		App->audio->PlayFx(whistleRefereeSFX);
		
		sprintf_s(setsCountLeftText, 10, "%d", leftSets);
		App->fonts->BlitText(62, 120, setsCountFont, setsCountLeftText);

		App->render->Blit(uiSprites, 113, 120, &sets_count);

		sprintf_s(setsCountRightText, 10, "%d", rightSets);
		App->fonts->BlitText(196, 120, setsCountFont, setsCountRightText);
	}

	//Win Lose
	if (getRightSets() > getLeftSets() && (numSets == 3 || (getRightSets() == 2 && getLeftSets() == 0)))
	{
		App->render->Blit(uiSprites, 175, 54, &winR);
		App->render->Blit(uiSprites, 30, 54, &loseL);

		//App->audio->PlayFx(winnerRefereeSFX);
		//App->audio->PlayFx(crowdWinSFX);

		if (App->map == MapType::Turf)
			App->fade->FadeToBlack((Module*)App->turflevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Beach)
			App->fade->FadeToBlack((Module*)App->beachlevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Clay)
			App->fade->FadeToBlack((Module*)App->clay, (Module*)App->sceneIntro, 150);

		App->ui->counterLeftScore = 0;
		App->ui->leftScore = 0;
		App->ui->counterRightScore = 0;
		App->ui->rightScore = 0;
	}
	else if (getRightSets() < getLeftSets() && (numSets == 3 || (getLeftSets() == 2 && getRightSets() == 0 )))
	{
		App->render->Blit(uiSprites, 174, 54, &loseR);
		App->render->Blit(uiSprites, 18, 54, &winL);

		//App->audio->PlayFx(winnerRefereeSFX);
		//App->audio->PlayFx(crowdWinSFX);

		if (App->map == MapType::Turf)
			App->fade->FadeToBlack((Module*)App->turflevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Beach)
			App->fade->FadeToBlack((Module*)App->beachlevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Clay)
			App->fade->FadeToBlack((Module*)App->clay, (Module*)App->sceneIntro, 150);

		App->ui->counterLeftScore = 0;
		App->ui->leftScore = 0;
		App->ui->counterRightScore = 0;
		App->ui->rightScore = 0;
	}

	if (getRightSets() == 3 && getNumSets() == 3)
	{
		App->render->Blit(uiSprites, 175, 54, &winR);
		App->render->Blit(uiSprites, 30, 54, &loseL);

		//App->audio->PlayFx(winnerRefereeSFX);
		//App->audio->PlayFx(crowdWinSFX);

		if (App->map == MapType::Turf)
			App->fade->FadeToBlack((Module*)App->turflevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Beach)
			App->fade->FadeToBlack((Module*)App->beachlevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Clay)
			App->fade->FadeToBlack((Module*)App->clay, (Module*)App->sceneIntro, 150);

		App->ui->counterLeftScore = 0;
		App->ui->leftScore = 0;
		App->ui->counterRightScore = 0;
		App->ui->rightScore = 0;
	}
	else if (getLeftSets() == 3 && getNumSets() == 3)
	{
		App->render->Blit(uiSprites, 174, 54, &loseR);
		App->render->Blit(uiSprites, 18, 54, &winL);

		//App->audio->PlayFx(winnerRefereeSFX);
		//App->audio->PlayFx(crowdWinSFX);

		if (App->map == MapType::Turf)
			App->fade->FadeToBlack((Module*)App->turflevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Beach)
			App->fade->FadeToBlack((Module*)App->beachlevel, (Module*)App->sceneIntro, 150);
		else if (App->map == MapType::Clay)
			App->fade->FadeToBlack((Module*)App->clay, (Module*)App->sceneIntro, 150);

		App->ui->counterLeftScore = 0;
		App->ui->leftScore = 0;
		App->ui->counterRightScore = 0;
		App->ui->rightScore = 0;
	}

	return Update_Status::UPDATE_CONTINUE;
}
	

bool UI::CleanUp()
{
	return true;
}