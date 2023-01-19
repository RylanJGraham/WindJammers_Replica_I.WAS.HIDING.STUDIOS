#include <SDL/include/SDL.h>
#include "RightEnglishPlayer.h"

#include "LeftEnglishPlayer.h"
#include "Left_Japanese_Player.h"
#include "Right_Japanese_Player.h"
#include "LeftGermanPlayer.h"
#include "RightGermanPlayer.h"

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

#define initialXPos 240
#define initialYPos 105

RightEnglishPlayer::RightEnglishPlayer(bool startEnabled) : Module(startEnabled)
{
	///CHAR3: English
	// idle animation
	idleAnim.PushBack({ 348, 475, 39, 34 });
	idleAnim.PushBack({ 309, 474, 39, 35 });
	idleAnim.PushBack({ 269, 473, 40, 36 });
	idleAnim.PushBack({ 230, 475, 39, 34 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

	// move upwards
	upAnim.PushBack({ 129, 209, 27, 39 });
	upAnim.PushBack({ 97, 209, 25, 39 });
	upAnim.PushBack({ 62, 204, 26, 49 });
	upAnim.PushBack({ 31, 209, 24, 39 });
	upAnim.PushBack({ 0, 209, 26, 39 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 391, 398, 27, 32 });
	downAnim.PushBack({ 354, 393, 30, 43 });
	downAnim.PushBack({ 323, 397, 26, 35 });
	downAnim.PushBack({ 290, 398, 28, 32 });
	downAnim.PushBack({ 253, 393, 30, 43 });
	downAnim.PushBack({ 222, 397, 26, 35 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	//Move right 
	rightAnim.PushBack({ 422, 4, 25, 36 });
	rightAnim.PushBack({ 453, 4, 34, 35 });
	rightAnim.PushBack({ 2, 52, 32, 36 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	//Move left
	leftAnim.PushBack({ 3, 158, 32, 36 });
	leftAnim.PushBack({ 38, 159, 34, 35 });
	leftAnim.PushBack({ 78, 158, 25, 36 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	//Slide Left
	SlideLAnim.PushBack({ 307, 95, 66, 30 });
	SlideLAnim.PushBack({ 311, 216, 45, 31 });
	SlideLAnim.PushBack({ 276, 210, 35, 33 });
	SlideLAnim.PushBack({ 129, 302, 23, 44 });
	SlideLAnim.loop = false;
	SlideLAnim.speed = 0.1f;

	//Slide Right
	SlideRAnim.PushBack({ 307, 55, 66, 30 });
	SlideRAnim.PushBack({ 417, 56, 45, 30 });
	SlideRAnim.PushBack({ 462, 49, 35, 34 });
	SlideRAnim.PushBack({ 203, 100, 25, 44 });
	SlideRAnim.loop = false;
	SlideRAnim.speed = 0.1f;

	//Slide Up
	SlideUAnim.PushBack({ 427, 404, 31, 66 });
	SlideUAnim.PushBack({ 428, 315, 32, 45 });
	SlideUAnim.PushBack({ 424, 369, 36, 32 });
	SlideUAnim.PushBack({ 416, 253, 44, 23 });
	SlideUAnim.loop = false;
	SlideUAnim.speed = 0.1f;

	//Slide Down
	SlideDAnim.PushBack({ 426, 473, 30, 66 });
	SlideDAnim.PushBack({ 427, 583, 32, 45 });
	SlideDAnim.PushBack({ 423, 542, 36, 32 });
	SlideDAnim.PushBack({ 415, 667, 44, 23 });
	SlideDAnim.loop = false;
	SlideDAnim.speed = 0.1f;

	//Slide Up Right
	SlideUpRightAnim.PushBack({ 200, 651, 45, 57 });
	SlideUpRightAnim.PushBack({ 285, 664, 32, 44 });
	SlideUpRightAnim.PushBack({ 247, 672, 33, 35 });
	SlideUpRightAnim.PushBack({ 356, 670, 37, 38 });
	SlideUpRightAnim.loop = false;
	SlideUpRightAnim.speed = 0.1f;

	//Slide Up Left
	SlideUpLeftAnim.PushBack({ 154, 651, 45, 56 });
	SlideUpLeftAnim.PushBack({ 82, 664, 32, 44 });
	SlideUpLeftAnim.PushBack({ 119, 673, 33, 34 });
	SlideUpLeftAnim.PushBack({ 6, 670, 37, 38 });
	SlideUpLeftAnim.loop = false;
	SlideUpLeftAnim.speed = 0.1f;

	//Slide Down Right
	SlideDownRightAnim.PushBack({ 200, 710, 45, 57 });
	SlideDownRightAnim.PushBack({ 285, 710, 32, 44 });
	SlideDownRightAnim.PushBack({ 247, 711, 33, 34 });
	SlideDownRightAnim.PushBack({ 356, 670, 37, 38 });
	SlideDownRightAnim.loop = false;
	SlideDownRightAnim.speed = 0.1f;

	//Slide Down Left
	SlideDownLeftAnim.PushBack({ 154, 711, 45, 57 });
	SlideDownLeftAnim.PushBack({ 82, 710, 32, 44 });
	SlideDownLeftAnim.PushBack({ 119, 711, 33, 35 });
	SlideDownLeftAnim.PushBack({ 6, 670, 37, 38 });
	SlideDownLeftAnim.loop = false;
	SlideDownLeftAnim.speed = 0.1f;

	//Victory
	victAnim.PushBack({ 289, 304, 32, 41 });
	victAnim.PushBack({ 323, 305, 33, 40 });
	victAnim.loop = true;
	victAnim.speed = 0.05f;

	//Lose
	loseAnim.PushBack({ 234, 105, 37, 35 });
	loseAnim.loop = true;
	loseAnim.speed = 0.05f;

	//Got scored on
	ScoredOn.PushBack({ 234, 105, 37, 35 });

	//Scored
	Scored.PushBack({ 327, 257, 38, 38 });

	///THROW
	//Disk Throw TURF MAP (RED Disk)
	throwTURF.PushBack({ 132, 517, 37, 35 });
	throwTURF.PushBack({ 90, 516, 42, 34 });
	throwTURF.PushBack({ 41, 512, 43, 46 });
	throwTURF.PushBack({ 0, 515, 35, 39 });
	throwTURF.loop = false;
	throwTURF.speed = 0.2f;

	//Disk Throw CLAY MAP (GREEN Disk)
	throwCLAY.PushBack({ 132, 563, 37, 35 });
	throwCLAY.PushBack({ 90, 562, 42, 34 });
	throwCLAY.PushBack({ 41, 512, 43, 46 });
	throwCLAY.PushBack({ 0, 515, 35, 39 });
	throwCLAY.loop = false;
	throwCLAY.speed = 0.2f;

	//Disk Throw BEACH MAP (BLUE Disk)
	throwBEACH.PushBack({ 132, 609, 36, 35 });
	throwBEACH.PushBack({ 90, 608, 42, 34 });
	throwBEACH.PushBack({ 41, 512, 43, 46 });
	throwBEACH.PushBack({ 0, 515, 35, 39 });
	throwBEACH.loop = false;
	throwBEACH.speed = 0.2f;

	///HOLD
	//Disk Holding TURF MAP (RED Disk)
	diskHoldTURF.PushBack({ 110, 347, 53, 42 });
	diskHoldTURF.PushBack({ 163, 344, 54, 45 });
	diskHoldTURF.loop = true;
	diskHoldTURF.speed = 0.1f;

	//Disk Holding CLAY MAP (GREEN Disk)
	diskHoldCLAY.PushBack({ 109, 401, 53, 43 });
	diskHoldCLAY.PushBack({ 162, 399, 54, 45 });
	diskHoldCLAY.loop = true;
	diskHoldCLAY.speed = 0.1f;

	//Disk Holding BEACH MAP (BLUE Disk)
	diskHoldBEACH.PushBack({ 109, 455, 53, 44 });
	diskHoldBEACH.PushBack({ 162, 454, 54, 45 });
	diskHoldBEACH.loop = true;
	diskHoldBEACH.speed = 0.1f;

	//SHADOW EFFECT
	shadowAnim.PushBack({ 0,0,31,31 });
	shadowAnim.PushBack({ 0,31,31,31 });
	shadowAnim.loop = true;
	shadowAnim.speed = 0.3f;

}

RightEnglishPlayer::~RightEnglishPlayer()
{

}

bool RightEnglishPlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	shadowTexture = App->textures->Load("Assets/Spriteswind/Particles/Shadow_spritesheet.png");
	texture = App->textures->Load("Assets/Spriteswind/Sprites/CHAR3/English_spritesheet.png");
	currentAnimation = &idleAnim;

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

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct

	return ret;
}

Update_Status RightEnglishPlayer::Update()
{
	//In this function are all the movement inputs and animations updates
	Movement();

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
			currentAnimation = &diskHoldTURF;
			isDefeated = false;
			hasDisk = true;

		}
	}

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();
	shadowAnim.Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status RightEnglishPlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect shadowRect = shadowAnim.GetCurrentFrame();
		App->render->Blit(shadowTexture, position.x + 3, position.y + 20, &shadowRect);
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}


	return Update_Status::UPDATE_CONTINUE;
}

void RightEnglishPlayer::OnCollision(Collider* c1, Collider* c2)
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
		position.x = 295 - 20;
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::RIGHT_5P_GOAL) {
		position.x = 295 - 15;
	}

	//Collider player-net
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::NET) {
		position.x = 150 + 4;
	}

	///Score points
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN) {
		godMode = !godMode;
	}

	if (godMode == false) {

		if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::LEFT_3P_GOAL)
		{
			App->ui->rightScore += 300;
			App->ui->counterRightScore += 3;
			Particle* goalscoredleft = App->particles->AddParticle(App->particles->goalscoredleft, c1->rect.x, c1->rect.y - 25, Collider::Type::NONE);
			Particle* goalscoredright3pts = App->particles->AddParticle(App->particles->goalscoredright3pts, c1->rect.x + 10, c1->rect.y - 10, Collider::Type::NONE);

			timedef = SDL_GetTicks();

			this->isCelebrating = true;
			App->leftgermanyplayer->isDefeated = true;
			App->LeftJapanesePlayer->isDefeated = true;
			App->leftenglishplayer->isDefeated = true;

			App->leftgermanyplayer->hasDisk = true;
			App->LeftJapanesePlayer->hasDisk = true;
			App->leftenglishplayer->hasDisk = true;

			//sfx
			App->audio->PlayFx(goalSFX);
			App->audio->PlayFx(crowdGoalSFX);
			App->audio->PlayFx(referee3ptsSFX);

			//reset players positions when scoring
			position.x = initialXPos;
			position.y = initialYPos;
			App->LeftJapanesePlayer->position.x = 50;
			App->LeftJapanesePlayer->position.y = 105;

			App->leftgermanyplayer->position.x = 50;
			App->leftgermanyplayer->position.y = 105;

			App->leftenglishplayer->position.x = 50;
			App->leftenglishplayer->position.y = 105;
		}
		else if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::LEFT_5P_GOAL)
		{
			App->ui->rightScore += 500;
			App->ui->counterRightScore += 5;
			Particle* goalscoredleft = App->particles->AddParticle(App->particles->goalscoredleft, c1->rect.x, c1->rect.y - 25, Collider::Type::NONE);
			Particle* goalscoredleft5pts = App->particles->AddParticle(App->particles->goalscoredleft5pts, c1->rect.x + 10, c1->rect.y - 10, Collider::Type::NONE);

			timedef = SDL_GetTicks();

			this->isCelebrating = true;
			App->leftgermanyplayer->isDefeated = true;
			App->LeftJapanesePlayer->isDefeated = true;
			App->leftenglishplayer->isDefeated = true;


			App->leftgermanyplayer->hasDisk = true;
			App->LeftJapanesePlayer->hasDisk = true;
			App->leftenglishplayer->hasDisk = true;

			//sfx
			App->audio->PlayFx(goalSFX);
			App->audio->PlayFx(crowdGoalSFX);
			App->audio->PlayFx(referee5ptsSFX);

			//reset players positions when scoring
			position.x = initialXPos;
			position.y = initialYPos;
			App->LeftJapanesePlayer->position.x = 50;
			App->LeftJapanesePlayer->position.y = 105;

			App->leftgermanyplayer->position.x = 50;
			App->leftgermanyplayer->position.y = 105;

			App->leftenglishplayer->position.x = 50;
			App->leftenglishplayer->position.y = 105;
		}
	}
	else if (godMode == true) {
		if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::LEFT_3P_GOAL ||
			c1->type == Collider::Type::DISK && c2->type == Collider::Type::LEFT_5P_GOAL)
		{
			App->ui->rightScore += 0;
			App->leftgermanyplayer->hasDisk = true;
			App->LeftJapanesePlayer->hasDisk = true;
			App->leftenglishplayer->hasDisk = true;

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

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER)
	{
		App->particles->diskR.HasDiskR == true;

	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DISK)
	{

		/*if (c1->rect.y < this->position.y) {
			Particle* UpAngleCatch = App->particles->AddParticle(App->particles->caughtrightsideup, this->position.x - 20, this->position.y - 20, Collider::Type::NONE);
		}*/
		//else if (c1->rect.y < (this->position.y - 40)) {
		//	/*Particle* Down = App->particles->AddParticle(App->particles->caughtrightsidenormaldown, this->position.x - 20, this->position.y - 20, Collider::Type::NONE);*/
		//}

		Particle* caugthstraightR = App->particles->AddParticle(App->particles->caughtrightsidenormal, this->position.x - 20, this->position.y - 20, Collider::Type::NONE);


		hasDisk = true;
	}
}

void RightEnglishPlayer::Movement()
{
	if (hasDisk == false)
	{
		//Left anim
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{
			position.x -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}

		//Right anim
		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}

		//Down anim
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			position.y += speed;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}

		//Up anim
		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}

		//Up Left Anim
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			position.x -= speedcross;
			position.y -= speedcross;

			if (currentAnimation != &leftAnim)
			{
				currentAnimation = &leftAnim;
			}
		}

		//Up Right Anim
		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			position.x += speedcross;
			position.y -= speedcross;

			if (currentAnimation != &rightAnim)
			{
				currentAnimation = &rightAnim;
			}
		}

		// Down Left Anim
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{
			position.x -= speedcross;
			position.y += speedcross;

			if (currentAnimation != &leftAnim)
			{
				currentAnimation = &leftAnim;
			}
		}

		// Down Right Anim
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			position.x += speedcross;
			position.y += speedcross;

			if (currentAnimation != &rightAnim)
			{
				currentAnimation = &rightAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN) {
			slidetickinit = SDL_GetTicks();
			inslide = true;
		}
	}

	if (inslide == true) {

		int timestart = SDL_GetTicks() - slidetickinit;

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN)
		{
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeR, position.x, position.y, Collider::Type::NONE);
			position.x += 40;

			if (currentAnimation != &SlideRAnim) {
				SlideRAnim.Reset();
				currentAnimation = &SlideRAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Up Slide Anim
		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN) {

			position.y -= 40;
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeU, position.x, position.y, Collider::Type::NONE);

			if (currentAnimation != &SlideUAnim)
			{
				SlideUAnim.Reset();
				currentAnimation = &SlideUAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Left Slide Anim
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
		{
			/*App->P2Status = Player_State_Right::PLAYER_DIVE;*/
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeL, position.x, position.y, Collider::Type::NONE);
			position.x -= 40;

			if (currentAnimation != &SlideLAnim)
			{
				SlideLAnim.Reset();
				currentAnimation = &SlideLAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Down Slide Anim
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN)
		{
			Particle* newdashParticle = App->particles->AddParticle(App->particles->DashSmokeD, position.x, position.y, Collider::Type::NONE);
			position.y += 40;
			if (currentAnimation != &SlideDAnim)
			{
				SlideDAnim.Reset();
				currentAnimation = &SlideDAnim;
			}
			App->audio->PlayFx(slidingSFX);

			/*App->P2Status = Player_State_Right::PLAYER_DIVE;*/
		}

		//Up Left Slide Anim
		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
		{
			position.x -= 40;
			position.y -= 40;
			if (currentAnimation != &SlideUpLeftAnim)
			{
				SlideUpLeftAnim.Reset();
				currentAnimation = &SlideUpLeftAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		//Up Right Slide Anim
		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN)
		{
			position.x += 40;
			position.y -= 40;

			if (currentAnimation != &SlideUpRightAnim)
			{
				SlideUpRightAnim.Reset();
				currentAnimation = &SlideUpRightAnim;
			}
			App->audio->PlayFx(slidingSFX);
			/*App->P2Status = Player_State_Right::PLAYER_DIVE;*/
		}

		// Down Left Slide Anim
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
		{
			position.x -= 40;
			position.y += 40;
			if (currentAnimation != &SlideDownLeftAnim)
			{
				SlideDownLeftAnim.Reset();
				currentAnimation = &SlideDownLeftAnim;
			}
			App->audio->PlayFx(slidingSFX);
		}

		// Down Right Slide Anim
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN)
		{
			position.x += 40;
			position.y += 40;

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
	

	//	//Left Slide
	//	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.x -= speedslide;
	//		if (currentAnimation != &SlideLAnim)
	//		{
	//			SlideLAnim.Reset();
	//			currentAnimation = &SlideLAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}

	//	//Right Slide
	//	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.x += speedslide;
	//		if (currentAnimation != &SlideRAnim)
	//		{
	//			SlideRAnim.Reset();
	//			currentAnimation = &SlideRAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}

	//	//Down Slide
	//	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.y += speedslide;
	//		if (currentAnimation != &SlideDAnim)
	//		{
	//			SlideDAnim.Reset();
	//			currentAnimation = &SlideDAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}

	//	//Up Slide
	//	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.y -= speedslide;
	//		if (currentAnimation != &SlideUAnim)
	//		{
	//			SlideUAnim.Reset();
	//			currentAnimation = &SlideUAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}

	//	//Up Left Slide
	//	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.y -= speedslide;
	//		position.x -= speedslide;
	//		if (currentAnimation != &SlideUpLeftAnim)
	//		{
	//			SlideUpLeftAnim.Reset();
	//			currentAnimation = &SlideUpLeftAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}

	//	//Up Right Slide
	//	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.y -= speedslide;
	//		position.x += speedslide;
	//		if (currentAnimation != &SlideUpRightAnim)
	//		{
	//			SlideUpRightAnim.Reset();
	//			currentAnimation = &SlideUpRightAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}

	//	//Down Left Slide
	//	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.y += speedslide;
	//		position.x -= speedslide;
	//		if (currentAnimation != &SlideDownLeftAnim)
	//		{
	//			SlideDownLeftAnim.Reset();
	//			currentAnimation = &SlideDownLeftAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}

	//	//Down Right Slide
	//	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_REPEAT)
	//	{
	//		position.y += speedslide;
	//		position.x += speedslide;
	//		if (currentAnimation != &SlideDownRightAnim)
	//		{
	//			SlideDownRightAnim.Reset();
	//			currentAnimation = &SlideDownRightAnim;
	//		}
	//		App->audio->PlayFx(slidingSFX);
	//	}
	//}

	else if (hasDisk == true)
	{
		//Holding disk animation
		if (currentAnimation != &diskHoldTURF) {
			diskHoldTURF.Reset();
			currentAnimation = &diskHoldTURF;
		}

		if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskR.speed.x = -5.0f;
			App->particles->diskR.speed.y = 0.0f;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskR, position.x - 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			//NOT WORKIN
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskR.speed.x = -1.0f;
			App->particles->diskR.speed.y = 3.5f;
			App->particles->diskR.position.x += App->particles->diskR.speed.x;
			App->particles->diskR.position.y += App->particles->diskR.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskR, position.x - 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}
		else if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{

			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskR.speed.x = -2.0f;
			App->particles->diskR.speed.y = -3.5f;
			App->particles->diskR.position.x += App->particles->diskR.speed.x;
			App->particles->diskR.position.y += App->particles->diskR.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskR, position.x - 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskR.speed.x = -1.0f;
			App->particles->diskR.speed.y = 3.5f;
			App->particles->diskR.position.x += App->particles->diskR.speed.x;
			App->particles->diskR.position.y += App->particles->diskR.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskR, position.x - 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}
		else if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{

			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskR.speed.x = -2.0f;
			App->particles->diskR.speed.y = 3.5f;
			App->particles->diskR.position.x += App->particles->diskR.speed.x;
			App->particles->diskR.position.y += App->particles->diskR.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskR, position.x - 20, position.y, Collider::Type::DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}
	}

	// If no up/down left/right movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_IDLE
		&& hasDisk == false
		&& isCelebrating == false
		&& isDefeated == false
		&& inslide == false)
		currentAnimation = &idleAnim;

}