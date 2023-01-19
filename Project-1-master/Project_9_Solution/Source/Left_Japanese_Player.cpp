#include <SDL/include/SDL.h>

#include "Left_Japanese_Player.h"
#include "Right_Japanese_Player.h"
#include "LeftGermanPlayer.h"
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

Left_Japanese_Player::Left_Japanese_Player(bool startEnabled) : Module(startEnabled)
{
	///CHAR1: Japanese
	// idle animation
	idleAnim.PushBack({ 227, 103, 24, 37 });
	idleAnim.PushBack({ 251, 103, 24, 39 });
	idleAnim.PushBack({ 275, 103, 24, 36 });
	idleAnim.PushBack({ 299, 103, 24, 35 });
	idleAnim.PushBack({ 323, 103, 24, 36 });
	idleAnim.PushBack({ 347, 103, 23, 36 });
	idleAnim.PushBack({ 370, 103, 23, 35 });
	idleAnim.PushBack({ 393, 103, 23, 36 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

	// move upwards
	upAnim.PushBack({ 0, 191, 30, 50 });
	upAnim.PushBack({ 30, 191, 30, 53 });
	upAnim.PushBack({ 60, 191, 30, 40 });
	upAnim.PushBack({ 90, 191, 30, 50 });
	upAnim.PushBack({ 120, 191, 30, 53 });
	upAnim.PushBack({ 150, 191, 30, 40 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 94, 148, 31, 34 });
	downAnim.PushBack({ 125, 148, 30, 38 });
	downAnim.PushBack({ 155, 148, 24, 43 });
	downAnim.PushBack({ 179, 148, 29, 35 });
	downAnim.PushBack({ 208, 148, 32, 38 });
	downAnim.PushBack({ 240, 148, 29, 43 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	//Move right 
	rightAnim.PushBack({ 269, 148, 41, 35 });
	rightAnim.PushBack({ 310, 148, 29, 36 });
	rightAnim.PushBack({ 385, 148, 41, 36 });
	rightAnim.PushBack({ 339, 148, 46, 29 });
	rightAnim.PushBack({ 385, 148, 41, 36 });
	rightAnim.PushBack({ 426, 148, 28, 33 });
	rightAnim.PushBack({ 269, 148, 41, 35 });
	rightAnim.PushBack({ 454, 148, 45, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	//Move left
	leftAnim.PushBack({ 269, 404, 41, 35 });
	leftAnim.PushBack({ 310, 404, 29, 36 });
	leftAnim.PushBack({ 339, 404, 46, 29 });
	leftAnim.PushBack({ 385, 404, 41, 36 });
	leftAnim.PushBack({ 426, 404, 28, 33 });
	leftAnim.PushBack({ 456, 404, 45, 32 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	//Slide Left
	SlideLAnim.PushBack({ 474, 359, 30, 33 });
	SlideLAnim.PushBack({ 0, 404, 43, 31 });
	SlideLAnim.PushBack({ 43, 404, 51, 24 });
	SlideLAnim.loop = false;
	SlideLAnim.speed = 0.1f;

	//Slide Right
	SlideRAnim.PushBack({ 474, 103, 30, 33 });
	SlideRAnim.PushBack({ 0, 148, 43, 31 });
	SlideRAnim.PushBack({ 43, 148, 51, 24 });
	SlideRAnim.loop = false;
	SlideRAnim.speed = 0.1f;

	//Slide Up
	SlideUAnim.PushBack({ 374, 191, 28, 33 });
	SlideUAnim.PushBack({ 402, 191, 31, 24 });
	SlideUAnim.PushBack({ 433, 191, 25, 53 });
	SlideUAnim.loop = false;
	SlideUAnim.speed = 0.1f;

	//Slide Down
	SlideDAnim.PushBack({ 213, 46, 32, 41 });
	SlideDAnim.PushBack({ 245, 46, 32, 49 });
	SlideDAnim.PushBack({ 277, 46, 25, 57 });
	SlideDAnim.loop = false;
	SlideDAnim.speed = 0.1f;
	
	//Slide Up Right
	SlideUpRightAnim.PushBack({ 270, 191, 27, 37 });
	SlideUpRightAnim.PushBack({ 297, 191, 32, 30 });
	SlideUpRightAnim.PushBack({ 329, 191, 45, 41 });
	SlideUpRightAnim.loop = false;
	SlideUpRightAnim.speed = 0.1f;

	//Slide Up Left
	SlideUpLeftAnim.PushBack({ 270, 447, 27, 27 });
	SlideUpLeftAnim.PushBack({ 297, 447, 32, 30 });
	SlideUpLeftAnim.PushBack({ 329, 447, 45, 41 });
	SlideUpLeftAnim.loop = false;
	SlideUpLeftAnim.speed = 0.1f;

	//Slide Down Right
	SlideDownRightAnim.PushBack({ 107, 46, 33, 35 });
	SlideDownRightAnim.PushBack({ 140, 46, 37, 40 });
	SlideDownRightAnim.PushBack({ 177, 46, 36, 48 });
	SlideDownRightAnim.loop = false;
	SlideDownRightAnim.speed = 0.1f;

	//Slide Down Left
	SlideDownLeftAnim.PushBack({ 107, 302, 33, 35 });
	SlideDownLeftAnim.PushBack({ 140, 302, 37, 40 });
	SlideDownLeftAnim.PushBack({ 177, 302, 36, 48 });
	SlideDownLeftAnim.loop = false;
	SlideDownLeftAnim.speed = 0.1f;

	//Victory
	victAnim.PushBack({ 77, 0, 33, 40 });
	victAnim.PushBack({ 110, 0, 34, 41 });
	victAnim.PushBack({ 144, 0, 33, 40 });
	victAnim.PushBack({ 177, 0, 34, 41 });
	victAnim.loop = true;
	victAnim.speed = 0.05f;

	//Lose
	loseAnim.PushBack({ 44, 103, 22, 40 });
	loseAnim.PushBack({ 66, 103, 24, 39 });
	loseAnim.PushBack({ 90, 103, 24, 39 });
	loseAnim.PushBack({ 114, 103, 23, 40 });
	loseAnim.PushBack({ 137, 103, 22, 40 });
	loseAnim.loop = true;
	loseAnim.speed = 0.05f;

	//Got scored on
	ScoredOn.PushBack({ 159, 359, 22, 36 });

	//Scored
	Scored.PushBack({ 21, 103, 23, 37 });


	///THROW

	//Disk Throw TURF MAP (RED Disk)
	throwTURF.PushBack({ 164, 723, 35, 40});
	throwTURF.PushBack({ 129, 723, 34, 38});
	throwTURF.PushBack({ 91, 723, 37, 40});
	throwTURF.loop = false;
	throwTURF.speed = 0.2f;

	//Disk Throw CLAY MAP (GREEN Disk)
	throwCLAY.PushBack({ 276, 723, 34, 40});
	throwCLAY.PushBack({ 240, 723, 36, 38});
	throwCLAY.PushBack({ 203, 723, 37, 40});
	throwCLAY.loop = false;
	throwCLAY.speed = 0.2f;

	//Disk Throw BEACH MAP (BLUE Disk)
	throwBEACH.PushBack({ 387, 723, 34, 40});
	throwBEACH.PushBack({ 351, 723, 35, 38});
	throwBEACH.PushBack({ 314, 723, 37, 40});
	throwBEACH.loop = false;
	throwBEACH.speed = 0.2f;


	///HOLD

	//Disk Holding TURF MAP (RED Disk)
	diskHoldTURF.PushBack({ 0, 809, 50, 52});
	diskHoldTURF.PushBack({ 51, 812, 50, 49});
	diskHoldTURF.PushBack({ 103, 814, 50, 47});
	diskHoldTURF.PushBack({ 154, 811, 51, 50});
	diskHoldTURF.PushBack({ 206, 809, 51, 52});
	diskHoldTURF.loop = true;
	diskHoldTURF.speed = 0.1f;
	
	//Disk Holding CLAY MAP (GREEN Disk)
	diskHoldCLAY.PushBack({ 0, 861, 51, 52});
	diskHoldCLAY.PushBack({ 52, 864, 50, 49});
	diskHoldCLAY.PushBack({ 104, 866, 50, 47});
	diskHoldCLAY.PushBack({ 155, 863, 51, 50});
	diskHoldCLAY.PushBack({ 207, 861, 51, 52 });
	diskHoldCLAY.loop = true;
	diskHoldCLAY.speed = 0.1f;

	//Disk Holding BEACH MAP (BLUE Disk)
	diskHoldBEACH.PushBack({ 0, 500, 51, 52 });
	diskHoldBEACH.PushBack({ 52, 503, 50, 49 });
	diskHoldBEACH.PushBack({ 104, 505, 50, 47 });
	diskHoldBEACH.PushBack({ 155, 502, 51, 50 });
	diskHoldBEACH.PushBack({ 207, 500, 51, 52 });
	diskHoldBEACH.loop = true;
	diskHoldBEACH.speed = 0.1f;

	//SHADOW EFFECT
	shadowAnim.PushBack({ 0,0,31,31 });
	shadowAnim.PushBack({ 0,31,31,31 });
	shadowAnim.loop = true;
	shadowAnim.speed = 0.3f;
}

Left_Japanese_Player::~Left_Japanese_Player()
{

}

bool Left_Japanese_Player::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	shadowTexture = App->textures->Load("Assets/Spriteswind/Particles/Shadow_spritesheet.png");
	texture = App->textures->Load("Assets/Spriteswind/Sprites/CHAR1/JapaneseSpriteALL.png");
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

Update_Status Left_Japanese_Player::Update()
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


	//if (godMode == false) {
	//	if (App->particles->diskLParabolic.anim.pingpong == false && App->particles->diskLParabolic.anim.HasFinished() == true)
	//	{

	//		App->ui->leftScore += 200;
	//		App->ui->counterLeftScore += 2;

	//		App->rightgermanyplayer->hasDisk = true;
	//		App->RightJapanesePlayer->hasDisk = true;
	//		App->righenglishplayer->hasDisk = true;

	//		//sfx
	//		App->audio->PlayFx(goalSFX);
	//		App->audio->PlayFx(crowdGoalSFX);
	//		App->audio->PlayFx(referee3ptsSFX);

	//		//reset players positions when scoring
	//		position.x = initialXPos;
	//		position.y = initialYPos;
	//		App->RightJapanesePlayer->position.x = 240;
	//		App->RightJapanesePlayer->position.y = 105;

	//		App->rightgermanyplayer->position.x = 240;
	//		App->rightgermanyplayer->position.y = 105;

	//		App->righenglishplayer->position.x = 240;
	//		App->righenglishplayer->position.y = 105;
	//		App->particles->diskLParabolic.SetToDelete();
	//	}
	//}

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();
	shadowAnim.Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Left_Japanese_Player::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		SDL_Rect shadowRect = shadowAnim.GetCurrentFrame();
		App->render->Blit(shadowTexture, position.x + 3, position.y + 20, &shadowRect);
		App->render->Blit(texture, position.x, position.y, &rect);
	}


	return Update_Status::UPDATE_CONTINUE;
}

void Left_Japanese_Player::OnCollision(Collider* c1, Collider* c2)
{
	/// PLAYER COLLIDERS WITH THE MAP
	//Collider player-upper wall
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::UPPER_WALL) {
		position.y = 40;
	}
	
	//Collider player-lower wall
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LOWER_WALL) {
		position.y = 199-40;
	}

	//Collider player-left goal
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LEFT_3P_GOAL){
		position.x = 10;
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LEFT_5P_GOAL) {
		position.x = 5;
	}

	//Collider player-right goal
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::RIGHT_3P_GOAL) {
		position.x = 295-25;
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


			App->rightgermanyplayer->hasDisk = true;
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
		
		if(c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::FLOOR && App->particles->diskLParabolic.anim.pingpong == false)
		{
			App->particles->diskLParabolic.isAlive = false;
			App->particles->diskLParabolic.SetToDelete();
			App->ui->leftScore += 200;
			App->ui->counterLeftScore += 2;
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

	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::UPPER_WALL)
	{

		Particle* newParticleBounceTop = App->particles->AddParticle(App->particles->caught, c1->rect.x, c1->rect.y, Collider::Type::NONE);

		App->audio->PlayFx(diskCollisionSFX);
	}
	
	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::LOWER_WALL)
	{

		Particle* newParticleBounceTop = App->particles->AddParticle(App->particles->caught, c1->rect.x, c1->rect.y, Collider::Type::NONE);

		App->audio->PlayFx(diskCollisionSFX);
	}
	
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DISK)
	{
		Particle* caughtstraightL = App->particles->AddParticle(App->particles->caughtleftsidenormal, position.x + 20, position.y - 20, Collider::Type::NONE);
		hasDisk = true;
	}
	
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PARABOLIC_DISK)
	{
		Particle* caughtstraightL = App->particles->AddParticle(App->particles->caughtleftsidenormal, position.x + 20, position.y - 20, Collider::Type::NONE);
		hasDisk = true;
	}

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER)
	{
		App->particles->diskL.HasDiskL == true;
	}
	
	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::PLAYER)
	{
		App->particles->diskL.HasDiskL == true;
	}
}

void Left_Japanese_Player::Movement() 
{
	if (hasDisk == false && inslide == false)
	{
		//Left anim
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= speed;
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}

		//Right anim
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}

		//Down anim
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			position.y += speed;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}

		//Up anim
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}

		//Up Left Anim
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.x -= speedcross;
			position.y -= speedcross;

			if (currentAnimation != &leftAnim)
			{
				currentAnimation = &leftAnim;
			}
		}

		//Up Right Anim
		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{
			position.x += speedcross;
			position.y -= speedcross;

			if (currentAnimation != &rightAnim)
			{
				currentAnimation = &rightAnim;
			}
		}

		// Down Left Anim
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			position.x -= speedcross;
			position.y += speedcross;

			if (currentAnimation != &leftAnim)
			{
				currentAnimation = &leftAnim;
			}
		}

		// Down Right Anim
		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			position.x += speedcross;
			position.y += speedcross;

			if (currentAnimation != &rightAnim)
			{
				currentAnimation = &rightAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN) {
			slidetickinit = SDL_GetTicks();
			inslide = true;
		}

	}

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

	//	//Left Slide
	//	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
	//	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
	//	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
	//	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
	//	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
	//	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
	//	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
	//	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT)
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
		int discTime = SDL_GetTicks();
		LOG("%d", discTime);

		//Holding disk animation
		if (currentAnimation != &diskHoldTURF) {
			diskHoldTURF.Reset();
			currentAnimation = &diskHoldTURF;
		}


		//
		//	NORMAL SHOT
		//
		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

				App->particles->diskL.speed.x = 5.0f;
				App->particles->diskL.speed.y = 0.0f;
				Particle* newParticle = App->particles->AddParticle(App->particles->diskL, position.x + 20, position.y, Collider::Type::DISK);
				newParticle->collider->AddListener(this);
				hasDisk = false;
				discTime = 0;
				App->audio->PlayFx(discThrowSFX);
		}
		

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
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
		else if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) 
		{

			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
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
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
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
		else if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{

			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
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

		//
		//	PARABOLIC SHOT
		//
		if (App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskLParabolic.speed.x = 2.0f;
			App->particles->diskLParabolic.speed.y = 0.0f;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskLParabolic, position.x + 20, position.y, Collider::Type::PARABOLIC_DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			discTime = 0;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
		{

			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}


			App->particles->diskLParabolic.speed.x = 2.0f;
			App->particles->diskLParabolic.speed.y = -1.5f;
			App->particles->diskLParabolic.position.x += App->particles->diskLParabolic.speed.x;
			App->particles->diskLParabolic.position.y += App->particles->diskLParabolic.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskLParabolic, position.x + 20, position.y, Collider::Type::PARABOLIC_DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskLParabolic.speed.x = 2.0f;
			App->particles->diskLParabolic.speed.y = 1.5f;
			App->particles->diskLParabolic.position.x += App->particles->diskLParabolic.speed.x;
			App->particles->diskLParabolic.position.y += App->particles->diskLParabolic.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskLParabolic, position.x + 20, position.y, Collider::Type::PARABOLIC_DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

	}

	// If no up/down left/right movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_IDLE 
		&& hasDisk==false
		&&isCelebrating == false
		&& isDefeated == false
		&& inslide == false){ 
		currentAnimation = &idleAnim;
	}

}