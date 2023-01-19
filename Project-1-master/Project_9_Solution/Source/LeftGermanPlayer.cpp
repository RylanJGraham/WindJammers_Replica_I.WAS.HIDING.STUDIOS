#include <SDL/include/SDL.h>

#include "LeftGermanPlayer.h"
#include "Left_Japanese_Player.h"
#include "Right_Japanese_Player.h"
#include "RightGermanPlayer.h"
#include "LeftEnglishPlayer.h"
#include "RightEnglishPlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "UI.h"

#include <stdio.h>

#define initialXPos 50
#define initialYPos 105

LeftGermanPlayer::LeftGermanPlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation
	idleAnim.PushBack({ 68, 324, 24, 34 });
	idleAnim.PushBack({ 92, 324, 23, 36 });
	idleAnim.PushBack({ 115, 324, 23, 35 });
	idleAnim.PushBack({ 115, 324, 23, 35 });
	idleAnim.PushBack({ 92, 324, 23, 36 });
	idleAnim.PushBack({ 68, 324, 24, 34 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

	// move upwards
	upAnim.PushBack({ 96, 367, 32, 34 });
	upAnim.PushBack({ 67, 367, 29, 39 });
	upAnim.PushBack({ 32, 367, 30, 36 });
	upAnim.PushBack({ 1, 367, 31, 34 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 138, 324, 26, 30 });
	downAnim.PushBack({ 164, 324, 31, 30 });
	downAnim.PushBack({ 195, 324, 31, 30 });
	downAnim.PushBack({ 226, 324, 29, 30 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;


	////Move Right
	rightAnim.PushBack({ 1, 406, 28, 33 });
	rightAnim.PushBack({ 58, 406, 27, 33 });
	rightAnim.PushBack({ 85, 406, 21, 33 });
	rightAnim.PushBack({ 106, 406, 25, 33 });
	rightAnim.PushBack({ 131, 406, 30, 33 });
	rightAnim.PushBack({ 161, 406, 21, 33 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;


	////Move Left
	leftAnim.PushBack({ 52, 440, 28, 34 });
	leftAnim.PushBack({ 80, 440, 27, 34 });
	leftAnim.PushBack({ 107, 440, 21, 34 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	////Move Up right
	UpRightAnim.PushBack({ 233, 367, 22, 34 });
	UpRightAnim.PushBack({ 29, 406, 29, 33 });
	UpRightAnim.PushBack({ 106, 406, 25, 33 });
	UpRightAnim.PushBack({ 131, 406, 30, 33 });
	UpRightAnim.loop = true;
	UpRightAnim.speed = 0.1f;

	//Move Up Left
	UpLeftAnim.PushBack({ 1, 440, 29, 34 });
	UpLeftAnim.PushBack({ 30, 440, 20, 34 });
	UpLeftAnim.PushBack({ 1, 440, 29, 34 });
	UpLeftAnim.PushBack({ 30, 440, 20, 34 });
	UpLeftAnim.loop = true;
	UpLeftAnim.speed = 0.1f;
	

	//Move Down Left -- DONE
	DownLeftAnim.PushBack({ 98, 474, 27, 31 });
	DownLeftAnim.PushBack({ 78, 474, 20, 31 });
	DownLeftAnim.PushBack({ 30, 440, 20, 34 });
	DownLeftAnim.PushBack({ 52, 474, 26, 34 });
	DownLeftAnim.loop = true;
	DownLeftAnim.speed = 0.1f;

	////Move Down right
	DownRightAnim.PushBack({ 156, 440, 26, 33 });
	DownRightAnim.PushBack({ 182, 440, 21, 33 });
	DownRightAnim.PushBack({ 203, 440, 26, 33 });
	DownRightAnim.PushBack({ 156, 440, 26, 33 });
	DownRightAnim.PushBack({ 182, 440, 21, 33 });
	DownRightAnim.PushBack({ 203, 440, 26, 33 });
	DownRightAnim.loop = true;
	DownRightAnim.speed = 0.1f;

	//Victory
	victAnim.PushBack({ 179, 13, 29, 40 });
	victAnim.PushBack({ 208, 13, 32, 40 });
	victAnim.loop = false;
	victAnim.speed = 0.1f;

	//Slide Left
	SlideLAnim.PushBack({ 168, 239, 56, 31 });
	SlideLAnim.PushBack({ 139, 239, 29, 31 });
	SlideLAnim.PushBack({ 107, 239, 32, 31 });
	SlideLAnim.PushBack({ 224, 239, 31, 31 });
	SlideLAnim.loop = false;
	SlideLAnim.speed = 0.1f;

	//Slide Right
	SlideRAnim.PushBack({ 92, 188, 57, 31 });
	SlideRAnim.PushBack({ 63, 188, 29, 31 });
	SlideRAnim.PushBack({ 32, 188, 31, 31 });
	SlideRAnim.PushBack({ 1, 188, 31, 31 });
	SlideRAnim.loop = false;
	SlideRAnim.speed = 0.1f;

	//Slide Up
	SlideUAnim.PushBack({ 232, 188, 23, 51 });
	SlideUAnim.PushBack({ 203, 188, 29, 50 });
	SlideUAnim.PushBack({ 180, 188, 23, 50 });
	SlideUAnim.PushBack({ 149, 188, 31, 34 });
	SlideUAnim.loop = false;
	SlideUAnim.speed = 0.1f;


	//Slide Down
	SlideDAnim.PushBack({ 29, 239, 24, 49 });
	SlideDAnim.PushBack({ 1, 239, 28, 49 });
	SlideDAnim.PushBack({ 84, 239, 23, 49 });
	SlideDAnim.PushBack({ 53, 239, 31, 49 });
	SlideDAnim.loop = false;
	SlideDAnim.speed = 0.1f;


	//Slide Up Right
	SlideUpRightAnim.PushBack({ 68, 140, 39, 48 });
	SlideUpRightAnim.PushBack({ 38, 140, 30, 48 });
	SlideUpRightAnim.PushBack({ 1, 140, 37, 48 });
	SlideUpRightAnim.PushBack({ 213, 92, 26, 42 });
	SlideUpRightAnim.loop = false;
	SlideUpRightAnim.speed = 0.1f;


	//Slide Up Left
	SlideUpLeftAnim.PushBack({ 31, 91, 40, 49 });
	SlideUpLeftAnim.PushBack({ 1, 91, 30, 50 });
	SlideUpLeftAnim.PushBack({ 219, 53, 37, 35 });
	SlideUpLeftAnim.PushBack({ 191, 53, 28, 35 });
	SlideUpLeftAnim.PushBack({ 107, 238, 32, 31 });
	SlideUpLeftAnim.loop = false;
	SlideUpLeftAnim.speed = 0.1f;


	//Slide Down Left
	SlideDownLeftAnim.PushBack({ 168, 92, 45, 42});
	SlideDownLeftAnim.PushBack({ 137,  92, 31, 42 });
	SlideDownLeftAnim.PushBack({ 102, 92, 35, 42 });
	SlideDownLeftAnim.PushBack({ 71, 92, 31, 42 });
	SlideDownLeftAnim.loop = false;
	SlideDownLeftAnim.speed = 0.1f;


	//Slide Down Right 
	SlideDownRightAnim.PushBack({ 169, 140, 45, 42 });
	SlideDownRightAnim.PushBack({ 138, 140, 31, 42 });
	SlideDownRightAnim.PushBack({ 107, 140, 31, 42 });
	SlideDownRightAnim.PushBack({ 215, 140, 31, 42 });
	SlideDownRightAnim.loop = false;
	SlideDownRightAnim.speed = 0.1f;

	//Throw 
	Throw.PushBack({ 69, 288, 23, 35 });
	Throw.PushBack({ 92, 288, 24, 35 });
	Throw.PushBack({ 116, 288, 30, 35 });
	Throw.PushBack({ 146, 288, 28, 35 });
	Throw.PushBack({ 174, 288, 30, 35 });
	Throw.PushBack({ 204, 288, 26, 35 });
	Throw.PushBack({ 174, 288, 30, 35 });
	Throw.PushBack({ 230, 288, 22, 35 });
	Throw.loop = false;
	Throw.speed = 10.0f;

	/*
	ShadowAnim.PushBack({36, 530, 33, 33});
	ShadowAnim.PushBack({80, 530, 33, 33});
	ShadowAnim.loop = true;
	ShadowAnim.speed = 2.0f;
	*/

	//Holding Disk GET SPRITE WITH DIFFERENT COLOUR DISKS FOR EACH MAP -------------------

	//GET UNDERNEATH ANIMATION FOR WHEN DISK IS FALLING, 2 FRAMES ------------------

	//WON THE SET ARMS CROSSED -----------------

	//Got Scored On
	ScoredOn.PushBack({ 119, 14, 34 ,29 });
	ScoredOn.PushBack({ 119, 14, 34 ,29 });
	ScoredOn.speed = 0.1f;
	ScoredOn.loop = true;
	

	//Scored
	Scored.PushBack({ 153, 14, 26, 29 });

	//Victory 
	victAnim.PushBack({ 179, 14, 29, 39});
	victAnim.PushBack({ 208, 14, 31, 39});
	victAnim.loop = true;
	victAnim.speed = 0.05f;

	HoldingAnim.PushBack({ 70, 287, 22, 36 });
	HoldingAnim.PushBack({ 92, 287, 23, 36 });
	HoldingAnim.loop = true;
	HoldingAnim.speed = 0.1f;

	//SHADOW EFFECT
	shadowAnim.PushBack({ 0,0,31,31 });
	shadowAnim.PushBack({ 0,31,31,31 });
	shadowAnim.loop = true;
	shadowAnim.speed = 0.3f;

}

LeftGermanPlayer::~LeftGermanPlayer()
{

}

bool LeftGermanPlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture2 = App->textures->Load("Assets/Spriteswind/Sprites/CHAR2/CHAR2ALLDISKTHROWwithEffects.png");
	//shadowtexture = App->textures->Load("Assets/Spriteswind/Particles/CHAR2ALLDISKTHROWwithEffects.png");
	shadowTexture = App->textures->Load("Assets/Spriteswind/Particles/Shadow_spritesheet.png");
	//shadowAnimation = &ShadowAnim;
	currentAnimation = &idleAnim;
	
	/*App->P1Status = Player_State_Left::PLAYER_IDLE;*/

	slidingSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Sliding.wav");
	discThrowSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Disc/Throwing_1.wav");
	diskCollisionSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Disc/WallCollision.wav");
	goalSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Disc/Goal.wav");
	crowdGoalSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Crowd/Crowd1.wav");
	crowdWinSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Crowd/CrowdWin.wav");

	referee3ptsSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Referee/ThreePoints.wav");
	referee5ptsSFX = App->audio->LoadFx("Assets/Sound_Effects(SFX)wind/Referee/FivePoints.wav");

	//Initial player coords
	position.x = initialXPos;
	position.y = initialYPos;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 20, 40 }, Collider::Type::PLAYER, this);

	return ret;
}

Update_Status LeftGermanPlayer::Update()
{
	Movement();

	collider->SetPos(position.x, position.y);

	if (isCelebrating == true) {

		int time = SDL_GetTicks() - timedef;
		if (currentAnimation != &victAnim) {
			victAnim.Reset();
			currentAnimation = &victAnim;
		}

		if (time >= 2000) {
			isCelebrating = false;
		}
	}

	if (isDefeated == true) {
		int time = SDL_GetTicks() - timedef;
		if (currentAnimation != &ScoredOn) {
			ScoredOn.Reset();
			currentAnimation = &ScoredOn;
		}

		if (time >= 2000) {
			currentAnimation = &HoldingAnim;
			isDefeated = false;
			hasDisk = true;
		}
	}

	currentAnimation->Update();
	shadowAnim.Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status LeftGermanPlayer::PostUpdate()
{
	if (!destroyed)
	{

		//Shadow
		SDL_Rect shadowRect = shadowAnim.GetCurrentFrame();
		App->render->Blit(shadowTexture, position.x, position.y + 15, &shadowRect);

		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture2, position.x, position.y, &rect);
	}


	return Update_Status::UPDATE_CONTINUE;
}

void LeftGermanPlayer::OnCollision(Collider* c1, Collider* c2)
{
	/// PLAYER COLLIDERS WITH THE MAP
	//Collider player-upper wall
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::UPPER_WALL) {
		position.y = 40;
	}

	//Collider player-lower wall
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LOWER_WALL) {
		position.y = 199 - 40;
	}

	//Collider player-left goal
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LEFT_3P_GOAL) {
		position.x = 10;
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LEFT_5P_GOAL) {
		position.x = 5;
	}

	//Collider player-right goal
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::RIGHT_3P_GOAL) {
		position.x = 295 - 25;
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::RIGHT_5P_GOAL) {
		position.x = 295 - 20;
	}

	//Collider player-net
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::NET) {
		position.x = 150 - 19;
	}


	///Score points
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN) {
		godMode = !godMode;
	}

	if (godMode == false) {

		if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::RIGHT_3P_GOAL)
		{
			App->ui->leftScore += 300;
			App->ui->counterLeftScore += 3;
			Particle* goalscoredright = App->particles->AddParticle(App->particles->goalscoredright, c1->rect.x - 24, c1->rect.y - 25, Collider::Type::NONE);
			Particle* goalscoredright3pts = App->particles->AddParticle(App->particles->goalscoredright3pts, c1->rect.x - 40, c1->rect.y - 25, Collider::Type::NONE);

			timedef = SDL_GetTicks();

			this->isCelebrating = true;
			App->rightgermanyplayer->isDefeated = true;
			App->righenglishplayer->isDefeated = true;
			App->RightJapanesePlayer->isDefeated = true;

			App->rightgermanyplayer->hasDisk = true;
			App->RightJapanesePlayer->hasDisk = true;
			App->righenglishplayer->hasDisk = true;

			//sfx
			App->audio->PlayFx(goalSFX);
			App->audio->PlayFx(crowdGoalSFX);
			App->audio->PlayFx(referee3ptsSFX);

			//reset players positions when scoring
			position.x = initialXPos;
			position.y = initialYPos;
			App->RightJapanesePlayer->position.x = 240;
			App->RightJapanesePlayer->position.y = 105;

			App->rightgermanyplayer->position.x = 240;
			App->rightgermanyplayer->position.y = 105;

			App->righenglishplayer->position.x = 240;
			App->righenglishplayer->position.y = 105;
		}
		else if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::RIGHT_5P_GOAL)
		{

			App->ui->leftScore += 500;
			App->ui->counterLeftScore += 5;
			Particle* goalscoredright = App->particles->AddParticle(App->particles->goalscoredright, c1->rect.x - 24, c1->rect.y - 25, Collider::Type::NONE);
			Particle* goalscoredright5pts = App->particles->AddParticle(App->particles->goalscoredright5pts, c1->rect.x - 40, c1->rect.y - 25, Collider::Type::NONE);

			timedef = SDL_GetTicks();

			this->isCelebrating = true;
			App->rightgermanyplayer->isDefeated = true;
			App->righenglishplayer->isDefeated = true;
			App->RightJapanesePlayer->isDefeated = true;

			

			

			LOG("Start Animation");
		
			App->RightJapanesePlayer->hasDisk = true;
			App->righenglishplayer->hasDisk = true;

			//sfx
			App->audio->PlayFx(goalSFX);
			App->audio->PlayFx(crowdGoalSFX);
			App->audio->PlayFx(referee5ptsSFX);

			//reset players positions when scoring
			position.x = initialXPos;
			position.y = initialYPos;
			App->RightJapanesePlayer->position.x = 240;
			App->RightJapanesePlayer->position.y = 105;

			App->rightgermanyplayer->position.x = 240;
			App->rightgermanyplayer->position.y = 105;

			App->righenglishplayer->position.x = 240;
			App->righenglishplayer->position.y = 105;
		}
	}

	else if (godMode == true) {
		if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::RIGHT_3P_GOAL ||
			c1->type == Collider::Type::DISK && c2->type == Collider::Type::RIGHT_5P_GOAL)
		{
			App->ui->leftScore += 0;
			App->rightgermanyplayer->hasDisk = true;
			App->RightJapanesePlayer->hasDisk = true;
			App->righenglishplayer->hasDisk = true;

			App->audio->PlayFx(goalSFX);
			App->audio->PlayFx(crowdGoalSFX);
		}
	}


	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::UPPER_WALL)
	{

		Particle* newParticleBounceTop = App->particles->AddParticle(App->particles->caught, c1->rect.x, c1->rect.y, Collider::Type::NONE);

		App->audio->PlayFx(diskCollisionSFX);
	}

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::LOWER_WALL)
	{

		Particle* newParticleBounceTop = App->particles->AddParticle(App->particles->caught, c1->rect.x, c1->rect.y, Collider::Type::NONE);

		App->audio->PlayFx(diskCollisionSFX);
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DISK)
	{
		Particle* caughtstraightL = App->particles->AddParticle(App->particles->caughtleftsidenormal, position.x + 20, position.y - 20, Collider::Type::NONE);
		hasDisk = true;
	}

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER)
	{
		App->particles->diskL.HasDiskL == true;
	}

}

void LeftGermanPlayer::Movement() {
	if (hasDisk == false && inslide == false) {

		/*
		if (shadowAnimation != &ShadowAnim)
		{
			leftAnim.Reset();
			shadowAnimation = &ShadowAnim;
		}
		*/

		//Left Anim
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/
		}

		//Right Anim
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/
		}

		//Down Anim
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			position.y += speed;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/
		}

		//Up Anim
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/
		}

		//Up Left Anim
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.x -= speedcross;
			position.y -= speedcross;
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/

			if (currentAnimation != &UpLeftAnim)
			{
				currentAnimation = &UpLeftAnim;
			}

		}

		//Up Right Anim
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.x += speedcross;
			position.y -= speedcross;
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/

			if (currentAnimation != &UpRightAnim)
			{
				currentAnimation = &UpRightAnim;
			}
		}


		// Down Left Anim
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= speedcross;
			position.y += speedcross;
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/

			if (currentAnimation != &DownLeftAnim)
			{
				currentAnimation = &DownLeftAnim;
			}
		}

		// Down Right Anim
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += speedcross;
			position.y += speedcross;
			/*App->P1Status = Player_State_Left::PLAYER_MOVE;*/

			if (currentAnimation != &DownRightAnim)
			{
				currentAnimation = &DownRightAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {
			slidetickinit = SDL_GetTicks();
			inslide = true;
		}
	}


		////Left Slide
		//if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.x -= speedslide;
		//	if (currentAnimation != &SlideLAnim)
		//	{
		//		SlideLAnim.Reset();
		//		currentAnimation = &SlideLAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		////Right Slide
		//if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.x += speedslide;
		//	if (currentAnimation != &SlideRAnim)
		//	{
		//		SlideRAnim.Reset();
		//		currentAnimation = &SlideRAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		////Down Slide
		//if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.y += speedslide;
		//	if (currentAnimation != &SlideDAnim)
		//	{
		//		SlideDAnim.Reset();
		//		currentAnimation = &SlideDAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		////Up Slide
		//if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.y -= speedslide;
		//	if (currentAnimation != &SlideUAnim)
		//	{
		//		SlideUAnim.Reset();
		//		currentAnimation = &SlideUAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		////Up Left Slide
		//if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.y -= speedslide;
		//	position.x -= speedslide;
		//	if (currentAnimation != &SlideUpLeftAnim)
		//	{
		//		SlideUpLeftAnim.Reset();
		//		currentAnimation = &SlideUpLeftAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		////Up Right Slide
		//if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.y -= speedslide;
		//	position.x += speedslide;
		//	if (currentAnimation != &SlideUpRightAnim)
		//	{
		//		SlideUpRightAnim.Reset();
		//		currentAnimation = &SlideUpRightAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		////Down Left Slide
		//if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.y += speedslide;
		//	position.x -= speedslide;
		//	if (currentAnimation != &SlideDownLeftAnim)
		//	{
		//		SlideDownLeftAnim.Reset();
		//		currentAnimation = &SlideDownLeftAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		////Down Right Slide
		//if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT)
		//{
		//	position.y += speedslide;
		//	position.x += speedslide;
		//	if (currentAnimation != &SlideDownRightAnim)
		//	{
		//		SlideDownRightAnim.Reset();
		//		currentAnimation = &SlideDownRightAnim;
		//	}
		//	App->audio->PlayFx(slidingSFX);
		//}

		/*if (App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_REPEAT){
			inslide = true;
		}
		else {
			inslide = false;
		}*/

		//Normal Throw Animation
	

	if (inslide == true) {

		int timestart = SDL_GetTicks() - slidetickinit;

		//Left Slide
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
		{
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeL, position.x, position.y, Collider::Type::NONE);

			if (currentAnimation != &SlideLAnim)
			{
				SlideLAnim.Reset();
				currentAnimation = &SlideLAnim;
			}
			
			position.x -= 40;

			App->audio->PlayFx(slidingSFX);
		}

		//Right Slide
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
		{
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeR, position.x, position.y, Collider::Type::NONE);
			position.x += 40;
			
			if (currentAnimation != &SlideRAnim)
			{
				SlideRAnim.Reset();
				currentAnimation = &SlideRAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Down Slide
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
		{
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeD, position.x, position.y, Collider::Type::NONE);
			position.y += 40;
			if (currentAnimation != &SlideDAnim)
			{
				SlideDAnim.Reset();
				currentAnimation = &SlideDAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Up Slide
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN)
		{
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeU, position.x, position.y, Collider::Type::NONE);
			position.y -= 40;
			if (currentAnimation != &SlideUAnim)
			{
				SlideUAnim.Reset();
				currentAnimation = &SlideUAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Up Left Slide
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
		{
			position.y -= 40;
			position.x -= 40;
			if (currentAnimation != &SlideUpLeftAnim)
			{
				SlideUpLeftAnim.Reset();
				currentAnimation = &SlideUpLeftAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Up Right Slide
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
		{
			position.y -= 40;
			position.x += 40;
			if (currentAnimation != &SlideUpRightAnim)
			{
				SlideUpRightAnim.Reset();
				currentAnimation = &SlideUpRightAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Down Left Slide
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
		{
			position.y += 40;
			position.x -= 40;
			if (currentAnimation != &SlideDownLeftAnim)
			{
				SlideDownLeftAnim.Reset();
				currentAnimation = &SlideDownLeftAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Down Right Slide
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
		{
			position.y += 40;
			position.x += 40;
			if (currentAnimation != &SlideDownRightAnim)
			{
				SlideDownRightAnim.Reset();
				currentAnimation = &SlideDownRightAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		if (timestart >= 800) {
			inslide = false;
		}
	}


	else if (hasDisk == true) {

		if (currentAnimation != &HoldingAnim) {
			HoldingAnim.Reset();
			currentAnimation = &HoldingAnim;
		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE)
		{
			
			if (currentAnimation != &Throw) {
				Throw.Reset();
				currentAnimation = &Throw;
			}

			App->particles->diskL.speed.x = 5.0f;
			App->particles->diskL.speed.y = 0.0f;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskL, position.x + 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);

		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &Throw) {
				Throw.Reset();
				currentAnimation = &Throw;
			}

			App->particles->diskL.speed.x = 1.0f;
			App->particles->diskL.speed.y = -3.5f;
			App->particles->diskL.position.x += App->particles->diskL.speed.x;
			App->particles->diskL.position.y += App->particles->diskL.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskL, position.x + 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation != &Throw) {
				Throw.Reset();
				currentAnimation = &Throw;
			}

			App->particles->diskL.speed.x = 2.0f;
			App->particles->diskL.speed.y = -3.5f;
			App->particles->diskL.position.x += App->particles->diskL.speed.x;
			App->particles->diskL.position.y += App->particles->diskL.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskL, position.x + 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &Throw) {
				Throw.Reset();
				currentAnimation = &Throw;
			}

			App->particles->diskL.speed.x = 1.0f;
			App->particles->diskL.speed.y = 3.5f;
			App->particles->diskL.position.x += App->particles->diskL.speed.x;
			App->particles->diskL.position.y += App->particles->diskL.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskL, position.x + 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation != &Throw) {
				Throw.Reset();
				currentAnimation = &Throw;
			}

			App->particles->diskL.speed.x = 2.0f;
			App->particles->diskL.speed.y = 3.5f;
			App->particles->diskL.position.x += App->particles->diskL.speed.x;
			App->particles->diskL.position.y += App->particles->diskL.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskL, position.x + 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}
	}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_IDLE
			&& hasDisk == false
			&& isCelebrating == false
			&& isDefeated == false
			&& inslide == false
			/*&& inAnim == false*/
			/*&& inslide != true
			&& scored3 != true*/) {
			currentAnimation = &idleAnim;
		}


}



		
		/*App->P1Status = Player_State_Left::PLAYER_IDLE;*/
	//if (inslide == true) {

	//	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	//	{
	//		position.x += speedslide;
	//		currentAnimation = &SlideRAnim;
	//		/*inslide = false;*/
	//	}

	//	//Up Slide Anim
	//	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) {
	//		position.y -= speedslide;

	//		if (currentAnimation != &SlideUAnim)
	//		{
	//			SlideUAnim.Reset();
	//			currentAnimation = &SlideUAnim;
	//		}
	//		inslide = false;
	//	}

	//	//Left Slide Anim
	//	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	//	{
	//		/*App->P2Status = Player_State_Right::PLAYER_DIVE;*/
	//		position.x -= speedslide;

	//		if (currentAnimation != &SlideLAnim)
	//		{
	//			SlideLAnim.Reset();
	//			currentAnimation = &SlideLAnim;
	//		}
	//		inslide = false;
	//	}

	//	//Down Slide Anim
	//	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
	//	{
	//		position.y += speedslide;

	//		if (currentAnimation != &SlideDAnim)
	//		{
	//			SlideDAnim.Reset();
	//			currentAnimation = &SlideDAnim;
	//		}
	//		inslide = false;
	//		/*App->P2Status = Player_State_Right::PLAYER_DIVE;*/
	//	}

	//	//Up Left Slide Anim
	//	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
	//	{
	//		position.x -= speedcross;
	//		position.y -= speedcross;

	//		if (currentAnimation != &SlideUpLeftAnim)
	//		{
	//			SlideUpLeftAnim.Reset();
	//			currentAnimation = &SlideUpLeftAnim;
	//		}
	//		inslide = false;
	//	}

	//	//Up Right Slide Anim
	//	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
	//	{
	//		position.x += speedcross;
	//		position.y -= speedcross;

	//		if (currentAnimation != &SlideUpRightAnim)
	//		{
	//			SlideUpRightAnim.Reset();
	//			currentAnimation = &SlideUpRightAnim;
	//		}
	//		inslide = false;
	//		/*App->P2Status = Player_State_Right::PLAYER_DIVE;*/
	//	}

	//	// Down Left Slide Anim
	//	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
	//	{
	//		position.x -= speedcross;
	//		position.y += speedcross;

	//		if (currentAnimation != &SlideDownLeftAnim)
	//		{
	//			SlideDownLeftAnim.Reset();
	//			currentAnimation = &SlideDownLeftAnim;
	//		}
	//		inslide = false;
	//	}

	//	// Down Right Slide Anim
	//	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
	//	{
	//		position.x += speedcross;
	//		position.y += speedcross;

	//		if (currentAnimation != &SlideDownRightAnim)
	//		{
	//			SlideDownRightAnim.Reset();
	//			currentAnimation = &SlideDownRightAnim;
	//		}
	//		inslide = false;
		/*}*/

		/*	if (App->input->keys[SDL_SCANCODE_RIGHT] != Key_State::KEY_REPEAT &&
				App->input->keys[SDL_SCANCODE_LEFT] != Key_State::KEY_REPEAT &&
				App->input->keys[SDL_SCANCODE_UP] != Key_State::KEY_REPEAT &&
				App->input->keys[SDL_SCANCODE_DOWN] != Key_State::KEY_REPEAT
				&& inslide == true) {


			}*/
	/*}*/

	//if (scored3 == true) {

	//	currentAnimation = &victAnim;
	//	double startTime = SDL_GetTicks();
	//	double endtime = startTime + 10000;

	//	while(startTime < endtime) {
	//		currentAnimation = &victAnim;
	//	}

	//	scored3 = false;
	//}
//}

