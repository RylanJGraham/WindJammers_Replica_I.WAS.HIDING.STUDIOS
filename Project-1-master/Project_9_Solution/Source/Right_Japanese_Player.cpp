#include <SDL/include/SDL.h>

#include "Right_Japanese_Player.h"
#include "Left_Japanese_Player.h"
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

#define initialXPos 240
#define initialYPos 105

Right_Japanese_Player::Right_Japanese_Player(bool startEnabled) : Module(startEnabled)
{
	///CHAR1: Japanese
	// idle animation
	idleAnim.PushBack({ 228, 359, 22, 37 });
	idleAnim.PushBack({ 250, 359, 24, 39 });
	idleAnim.PushBack({ 274, 359, 25, 36 });
	idleAnim.PushBack({ 299, 359, 24, 35 });
	idleAnim.PushBack({ 323, 359, 24, 36 });
	idleAnim.PushBack({ 347, 359, 23, 36 });
	idleAnim.PushBack({ 370, 359, 23, 35 });
	idleAnim.PushBack({ 393, 359, 23, 36 });
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
	rightAnim.PushBack({ 339, 148, 46, 29 });
	rightAnim.PushBack({ 385, 148, 41, 36 });
	rightAnim.PushBack({ 426, 148, 28, 33 });
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
	SlideUpRightAnim.speed = 2;

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
	ScoredOn.PushBack({ 159, 103, 22, 36 });

	//Scored
	Scored.PushBack({ 21, 359, 23, 37 });


	///THROW
	
	//Disk Throw TURF MAP (RED Disk)
	throwTURF.PushBack({ 92, 763, 33, 40});
	throwTURF.PushBack({ 125, 763, 36, 38});
	throwTURF.PushBack({ 161, 763, 37, 40});
	throwTURF.loop = false;
	throwTURF.speed = 0.2f;

	//Disk Throw CLAY MAP (GREEN Disk)
	throwCLAY.PushBack({ 203, 763, 33, 40});
	throwCLAY.PushBack({ 236, 763, 36, 38});
	throwCLAY.PushBack({ 272, 763, 37, 40});
	throwCLAY.loop = false;
	throwCLAY.speed = 0.2f;

	//Disk Throw BEACH MAP (BLUE Disk)
	throwBEACH.PushBack({ 314, 763, 34, 40});
	throwBEACH.PushBack({ 349, 763, 35, 38});
	throwBEACH.PushBack({ 384, 763, 37, 40});
	throwBEACH.loop = false;
	throwBEACH.speed = 0.2f;


	///HOLD

	//Disk Holding TURF MAP (RED Disk)
	diskHoldTURF.PushBack({ 256, 809, 51, 52});
	diskHoldTURF.PushBack({ 308, 811, 51, 50});
	diskHoldTURF.PushBack({ 360, 814, 50, 47});
	diskHoldTURF.PushBack({ 412, 812, 50, 49});
	diskHoldTURF.PushBack({ 463, 809, 49, 52});
	diskHoldTURF.loop = true;
	diskHoldTURF.speed = 0.1f;

	//Disk Holding CLAY MAP (GREEN Disk)
	diskHoldCLAY.PushBack({ 257, 861, 51, 52});
	diskHoldCLAY.PushBack({ 309, 863, 51, 50});
	diskHoldCLAY.PushBack({ 361, 866, 50, 47});
	diskHoldCLAY.PushBack({ 413, 864, 50, 49});
	diskHoldCLAY.PushBack({ 464, 861, 48, 52});
	diskHoldCLAY.loop = true;
	diskHoldCLAY.speed = 0.1f;

	//Disk Holding BEACH MAP (BLUE Disk)
	diskHoldBEACH.PushBack({ 252, 604, 51, 52 });
	diskHoldBEACH.PushBack({ 201, 607, 50, 49 });
	diskHoldBEACH.PushBack({ 149, 609, 50, 47 });
	diskHoldBEACH.PushBack({ 97, 606, 51, 50 });
	diskHoldBEACH.PushBack({ 45, 604, 51, 52 });
	diskHoldBEACH.loop = true;
	diskHoldBEACH.speed = 0.1f;

	//SHADOW EFFECT
	shadowAnim.PushBack({ 0,0,31,31 });
	shadowAnim.PushBack({ 0,31,31,31 });
	shadowAnim.loop = true;
	shadowAnim.speed = 0.3f;

}

Right_Japanese_Player::~Right_Japanese_Player()
{

}

bool Right_Japanese_Player::Start()
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

Update_Status Right_Japanese_Player::Update()
{
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

Update_Status Right_Japanese_Player::PostUpdate()
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

void Right_Japanese_Player::OnCollision(Collider* c1, Collider* c2)
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
	
	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::UPPER_WALL) {
		position.y = 40;
	}

	//Collider player-lower wall
	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::LOWER_WALL) {
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
		else if (App->particles->diskRParabolic.anim.GetPingPongCount() >= 1 && c2->type != Collider::Type::PLAYER)
		{
			App->ui->leftScore += 200;
			App->ui->counterLeftScore += 2;
			Particle* goalscoredleft = App->particles->AddParticle(App->particles->goalscoredleft, c1->rect.x, c1->rect.y - 25, Collider::Type::NONE);
			Particle* goalscoredright3pts = App->particles->AddParticle(App->particles->goalscoredright3pts, c1->rect.x + 10, c1->rect.y - 10, Collider::Type::NONE);

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

	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::UPPER_WALL)
	{
		//NOT BOUNCE BUT STAYING SAME Y POS
		Particle* newParticleBounceTop = App->particles->AddParticle(App->particles->caught, c1->rect.x, c1->rect.y, Collider::Type::NONE);

		App->audio->PlayFx(diskCollisionSFX);
	}

	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::LOWER_WALL)
	{
		//NOT BOUNCE BUT STAYING SAME Y POS
		Particle* newParticleBounceTop = App->particles->AddParticle(App->particles->caught, c1->rect.x, c1->rect.y, Collider::Type::NONE);

		App->audio->PlayFx(diskCollisionSFX);
	}

	if (c1->type == Collider::Type::DISK && c2->type == Collider::Type::PLAYER)
	{
		App->particles->diskR.HasDiskR == true;
	
	}
	
	if (c1->type == Collider::Type::PARABOLIC_DISK && c2->type == Collider::Type::PLAYER)
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
	
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PARABOLIC_DISK)
	{

		Particle* caugthstraightR = App->particles->AddParticle(App->particles->caughtrightsidenormal, this->position.x - 20, this->position.y - 20, Collider::Type::NONE);
		

		hasDisk = true;
	}


}

void Right_Japanese_Player::Movement()
{
	if (hasDisk == false && inslide == false)
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
		int discTime = SDL_GetTicks();
		LOG("%d", discTime);

		//Holding disk animation
		if (currentAnimation != &diskHoldTURF) {
			diskHoldTURF.Reset();
			currentAnimation = &diskHoldTURF;
		}

		//
		// NORMAL SHOT
		//
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
			discTime = 0;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}


			App->particles->diskR.speed.x = -1.0f;
			App->particles->diskR.speed.y = -3.5f;
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
		

		//
		// PARABOLIC SHOT
		//
		if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskRParabolic.speed.x = -2.0f;
			App->particles->diskRParabolic.speed.y = 0.0f;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskRParabolic, position.x - 20, position.y, Collider::Type::PARABOLIC_DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			discTime = 0;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}


			App->particles->diskRParabolic.speed.x = -2.0f;
			App->particles->diskRParabolic.speed.y = -1.5f;
			App->particles->diskRParabolic.position.x += App->particles->diskRParabolic.speed.x;
			App->particles->diskRParabolic.position.y += App->particles->diskRParabolic.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskRParabolic, position.x - 20, position.y, Collider::Type::PARABOLIC_DISK);
			newParticle->collider->AddListener(this);
			hasDisk = false;
			App->audio->PlayFx(discThrowSFX);
		}

		if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			//Throwing animation
			if (currentAnimation != &throwTURF) {
				throwTURF.Reset();
				currentAnimation = &throwTURF;
			}

			App->particles->diskRParabolic.speed.x = -2.0f;
			App->particles->diskRParabolic.speed.y = 1.5f;
			App->particles->diskRParabolic.position.x += App->particles->diskRParabolic.speed.x;
			App->particles->diskRParabolic.position.y += App->particles->diskRParabolic.speed.y;
			Particle* newParticle = App->particles->AddParticle(App->particles->diskRParabolic, position.x - 20, position.y, Collider::Type::PARABOLIC_DISK);
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
		&& App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_IDLE
		&& hasDisk == false
		&& isCelebrating == false
		&& isDefeated == false
		&& inslide == false) {
		currentAnimation = &idleAnim;
	}
}