#include "Application.h"
#include "Disc.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

Disc::Disc(bool startEnabled) : Module(startEnabled)
{
	
}

Disc::~Disc()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Disc::Start()
{
	LOG("Loading Disc");

	texture = App->textures->Load("Assets/Spriteswind/Sprites/TURF_SPRITES/sprite_disk_lawnMap.png");

	//WHEN CHOOSE MAP CHANGE DISK
	if(App->map == MapType::Turf)
		texture = App->textures->Load("Assets/Spriteswind/Sprites/TURF_SPRITES/sprite_disk_lawnMap.png");
	else if(App->map == MapType::Beach)
		texture = App->textures->Load("Assets/Spriteswind/Sprites/BEACH_SPRITES/sprite_disk_beachMap.png");
	else if(App->map == MapType::Clay)
		texture = App->textures->Load("Assets/Spriteswind/Sprites/BEACH_SPRITES/sprite_disk_beachMap.png");

	turfDisc.PushBack({ 117, 48, 17, 17 });
	turfDisc.PushBack({ 149, 48, 17, 17 });
	turfDisc.PushBack({ 181, 48, 17, 17 });
	turfDisc.PushBack({ 213, 48, 17, 17 });
	turfDisc.loop = true;
	speed.x = 5;
	turfDisc.speed = 0.2f;

	collider->AddListener(this);
	//collider = App->collisions->AddCollider({ position.x, position.y, 20, 40 }, Collider::Type::DISK, this);

	//App->disc->Enable();

	return true;
}

Update_Status Disc::PreUpdate()
{
	

	return Update_Status::UPDATE_CONTINUE;
}

bool Disc::CleanUp()
{

	return true;
}

void Disc::OnCollision(Collider* c1, Collider* c2)
{
	// Destroy particles that collide
	if (this != nullptr && collider == c1 && c2->type == Collider::Type::PLAYER) //&& !particles[i]->collider->DISK
	{
		collider->pendingToDelete = true;
		Disable();
	}
	
}

Update_Status Disc::Update()
{
	frameCount++;

	// The disc is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		if(MapType::Turf)
			turfDisc.Update();
		//Add anims

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				Disable();
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (turfDisc.HasFinished())
			Disable();

		// Update the position in the screen
		position.x += speed.x;
		position.y += speed.y;

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Disc::PostUpdate()
{
	if (isAlive == true)
	{
		App->render->Blit(texture, position.x, position.y, &turfDisc.GetCurrentFrame());
	}

	return Update_Status::UPDATE_CONTINUE;
}

//Disc* Disc::AddParticle(const Disc& particle, int x, int y, Collider::Type colliderType, uint delay)
//{
//	Particle* newParticle = nullptr;
//
//	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
//	{
//		//Finding an empty slot for a new particle
//		if (particles[i] == nullptr)
//		{
//			newParticle = new Particle(particle);
//			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
//			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
//			newParticle->position.y = y;
//
//			//Adding the particle's collider
//			if (colliderType != Collider::Type::NONE)
//				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);
//
//			particles[i] = newParticle;
//			break;
//		}
//	}
//
//	return newParticle;
//}