#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture_disk = App->textures->Load("Assets/Spriteswind/Sprites/TURF_SPRITES/sprite_disk_lawnMap.png");
	texture_particles = App->textures->Load("Assets/Spriteswind/Particles/particlesAndEffects.png");
	//texture = App->textures->Load("Assets/Sprites/particles.png");
	textureFX = App->textures->Load("Assets/Spriteswind/Particles/particlesAndEffects.png");

	//// Explosion particle
	//explosion.anim.PushBack({274, 296, 33, 30});
	//explosion.anim.PushBack({313, 296, 33, 30});
	//explosion.anim.PushBack({346, 296, 33, 30});
	//explosion.anim.PushBack({382, 296, 33, 30});
	//explosion.anim.PushBack({419, 296, 33, 30});
	//explosion.anim.PushBack({457, 296, 33, 30});
	//explosion.anim.loop = false;
	//explosion.anim.speed = 0.3f;

	//laser.anim.PushBack({ 232, 103, 16, 12 });
	//laser.anim.PushBack({ 249, 103, 16, 12 });
	//laser.speed.x = 5;
	//laser.lifetime = 180;
	//laser.anim.speed = 0.2f;

	diskL.anim.PushBack({ 117, 48, 17, 17});
	diskL.anim.PushBack({ 149, 48, 17, 17});
	diskL.anim.PushBack({ 181, 48, 17, 17});
	diskL.anim.PushBack({ 213, 48, 17, 17});
	diskL.lifetime = 1000;
	diskL.speed.x = 5;
	diskL.anim.speed = 0.2f;
	
	diskLParabolic.anim.PushBack({ 35, 8, 18, 30});	//Franja Negra
	diskLParabolic.anim.PushBack({ 53, 7, 26, 32});	//Franja Negra
	diskLParabolic.anim.PushBack({ 79, 6, 37, 35});
	diskLParabolic.anim.PushBack({ 116, 5, 29, 37});
	diskLParabolic.anim.PushBack({ 145, 4, 22, 39});
	diskLParabolic.anim.PushBack({ 167, 2, 3, 40});
	diskLParabolic.anim.PushBack({ 171, 2, 24, 42});
	diskLParabolic.anim.PushBack({ 195, 2, 34, 43});
	diskLParabolic.anim.PushBack({ 229, 0, 44, 45});
	diskLParabolic.anim.pingpong = true;
	diskLParabolic.anim.loop = false;
	diskLParabolic.lifetime = 500;
	diskLParabolic.speed.x = 5;
	diskLParabolic.anim.speed = 0.4f;

	diskR.anim.PushBack({ 117, 48, 17, 17 });
	diskR.anim.PushBack({ 149, 48, 17, 17 });
	diskR.anim.PushBack({ 181, 48, 17, 17 });
	diskR.anim.PushBack({ 213, 48, 17, 17 });
	diskR.lifetime = 1000;
	diskR.speed.x = -5;
	diskR.anim.speed = 0.2f;
	
	diskRParabolic.anim.PushBack({ 35, 8, 18, 30 });
	diskRParabolic.anim.PushBack({ 53, 7, 26, 32 });
	diskRParabolic.anim.PushBack({ 79, 6, 37, 35 });
	diskRParabolic.anim.PushBack({ 116, 5, 29, 37 });
	diskRParabolic.anim.PushBack({ 145, 4, 22, 39 });
	diskRParabolic.anim.PushBack({ 167, 2, 3, 40 });
	diskRParabolic.anim.PushBack({ 171, 2, 24, 42 });
	diskRParabolic.anim.PushBack({ 195, 2, 34, 43 });
	diskRParabolic.anim.PushBack({ 229, 0, 44, 45 });
	diskRParabolic.anim.pingpong = true;
	diskRParabolic.anim.loop = false;
	diskRParabolic.lifetime = 500;
	diskRParabolic.speed.x = -5;
	diskRParabolic.anim.speed = 0.4f;

	wallCollision.anim.PushBack({ 232, 142, 58, 51});
	wallCollision.anim.speed = 0.1f;
	wallCollision.lifetime = 500;

	caught.anim.PushBack({ 232, 202, 70, 69 });
	caught.lifetime = 3;
	caught.speed.x = 0;
	caught.anim.speed = 0.1f;

	caughtleftsidenormal.anim.PushBack({ 4, 192, 41, 77 });
	caughtleftsidenormal.anim.PushBack({ 42, 192, 51, 81 });
	caughtleftsidenormal.anim.PushBack({ 92, 191, 42, 86 });
	caughtleftsidenormal.anim.PushBack({ 134, 191, 54, 79 });
	caughtleftsidenormal.anim.loop = false;
	caughtleftsidenormal.lifetime = 20;
	caughtleftsidenormal.speed.x = 0;
	caughtleftsidenormal.anim.speed = 0.2f;

	caughtrightsidenormal.anim.PushBack({ 251, 285, 46, 68 });
	caughtrightsidenormal.anim.PushBack({ 204, 280, 49, 79 });
	caughtrightsidenormal.anim.PushBack({ 157, 280, 49, 79 });
	caughtrightsidenormal.anim.PushBack({ 110, 280, 45, 79 });
	caughtrightsidenormal.anim.loop = false;
	caughtrightsidenormal.lifetime = 20;
	caughtrightsidenormal.speed.x = 0;
	caughtrightsidenormal.anim.speed = 0.2f;

	caughtrightsideup.anim.PushBack({ 302, 295, 50, 52 });
	//caughtrightsideup.anim.PushBack({ 204, 280, 49, 79 });
	//caughtrightsideup.anim.PushBack({ 157, 280, 49, 79 });
	//caughtrightsideup.anim.PushBack({ 110, 280, 45, 79 });
	caughtrightsideup.anim.loop = false;
	caughtrightsideup.lifetime = 20;
	caughtrightsideup.speed.x = 0;
	caughtrightsideup.anim.speed = 0.2f;

	DashSmokeL.anim.PushBack({ 8, 171, 20, 20 });
	DashSmokeL.anim.PushBack({ 28, 171, 20, 20 });
	DashSmokeL.anim.PushBack({ 48, 171, 20, 20 });
	DashSmokeL.anim.PushBack({ 71, 171, 22, 20 });
	DashSmokeL.anim.PushBack({ 96, 171, 22, 20 });
	DashSmokeL.anim.PushBack({ 116, 171, 22, 20 });
	DashSmokeL.anim.PushBack({ 133, 171, 22, 20 });
	DashSmokeL.anim.PushBack({ 149, 171, 22, 20 });
	DashSmokeL.lifetime = 30;
	DashSmokeL.anim.loop = false;
	DashSmokeL.anim.speed = 0.4f;
	DashSmokeL.speed.x = -1;

	DashSmokeR.anim.PushBack({ 8, 171, 20, 20 });
	DashSmokeR.anim.PushBack({ 28, 171, 20, 20 });
	DashSmokeR.anim.PushBack({ 48, 171, 20, 20 });
	DashSmokeR.anim.PushBack({ 71, 171, 22, 20 });
	DashSmokeR.anim.PushBack({ 96, 171, 22, 20 });
	DashSmokeR.anim.PushBack({ 116, 171, 22, 20 });
	DashSmokeR.anim.PushBack({ 133, 171, 22, 20 });
	DashSmokeR.anim.PushBack({ 149, 171, 22, 20 });
	DashSmokeR.lifetime = 30;
	DashSmokeR.anim.loop = false;
	DashSmokeR.anim.speed = 0.4f;
	DashSmokeR.speed.x = 1;

	DashSmokeU.anim.PushBack({ 8, 171, 20, 20 });
	DashSmokeU.anim.PushBack({ 28, 171, 20, 20 });
	DashSmokeU.anim.PushBack({ 48, 171, 20, 20 });
	DashSmokeU.anim.PushBack({ 71, 171, 22, 20 });
	DashSmokeU.anim.PushBack({ 96, 171, 22, 20 });
	DashSmokeU.anim.PushBack({ 116, 171, 22, 20 });
	DashSmokeU.anim.PushBack({ 133, 171, 22, 20 });
	DashSmokeU.anim.PushBack({ 149, 171, 22, 20 });
	DashSmokeU.lifetime = 30;
	DashSmokeU.anim.loop = false;
	DashSmokeU.anim.speed = 0.4f;
	DashSmokeU.speed.y = -1;

	DashSmokeD.anim.PushBack({ 8, 171, 20, 20 });
	DashSmokeD.anim.PushBack({ 28, 171, 20, 20 });
	DashSmokeD.anim.PushBack({ 48, 171, 20, 20 });
	DashSmokeD.anim.PushBack({ 71, 171, 22, 20 });
	DashSmokeD.anim.PushBack({ 96, 171, 22, 20 });
	DashSmokeD.anim.PushBack({ 116, 171, 22, 20 });
	DashSmokeD.anim.PushBack({ 133, 171, 22, 20 });
	DashSmokeD.anim.PushBack({ 149, 171, 22, 20 });
	DashSmokeD.lifetime = 30;
	DashSmokeD.anim.loop = false;
	DashSmokeD.anim.speed = 0.4f;
	DashSmokeD.speed.y = 1;




	goalscoredleft.anim.PushBack({ 4, 192, 41, 77 });
	goalscoredleft.anim.PushBack({ 42, 192, 51, 81 });
	goalscoredleft.anim.PushBack({ 92, 191, 42, 86 });
	goalscoredleft.anim.PushBack({ 134, 191, 54, 79 });
	goalscoredleft.anim.loop = false;
	goalscoredleft.lifetime = 40;
	goalscoredleft.speed.x = 0;
	goalscoredleft.anim.speed = 0.05f;

	goalscoredright.anim.PushBack({ 251, 285, 46, 68 });
	goalscoredright.anim.PushBack({ 204, 280, 49, 79 });
	goalscoredright.anim.PushBack({ 157, 280, 49, 79 });
	goalscoredright.anim.PushBack({ 110, 280, 45, 79 });
	goalscoredright.anim.loop = false;
	goalscoredright.lifetime = 40;
	goalscoredright.speed.x = 0;
	goalscoredright.anim.speed = 0.05f;

	goalscoredright3pts.anim.PushBack({ 180, 500, 55, 35 });
	goalscoredright3pts.anim.PushBack({ 121, 500, 59, 35 });
	goalscoredright3pts.anim.PushBack({ 180, 500, 55, 35 });
	goalscoredright3pts.anim.PushBack({ 121, 500, 59, 35 });
	goalscoredright3pts.anim.PushBack({ 180, 500, 55, 35 });
	goalscoredright3pts.anim.PushBack({ 121, 500, 59, 35 });
	goalscoredright3pts.anim.PushBack({ 180, 500, 55, 35 });
	goalscoredright3pts.anim.PushBack({ 121, 500, 59, 35 });
	goalscoredright3pts.anim.PushBack({ 180, 500, 55, 35 });
	goalscoredright3pts.anim.PushBack({ 121, 500, 59, 35 });
	goalscoredright3pts.anim.PushBack({ 180, 500, 55, 35 });
	goalscoredright3pts.anim.PushBack({ 121, 500, 59, 35 });
	goalscoredright3pts.anim.PushBack({ 180, 500, 55, 35 });
	goalscoredright3pts.anim.PushBack({ 121, 500, 59, 35 });
	/*--*/
	goalscoredright3pts.anim.PushBack({ 333, 500, 45, 35 });
	goalscoredright3pts.anim.PushBack({ 9, 500, 28, 35 });
	goalscoredright3pts.anim.PushBack({ 37, 500, 24, 35 });
	goalscoredright3pts.anim.PushBack({ 61, 500, 20, 35 });
	goalscoredright3pts.anim.PushBack({ 81, 500, 16, 35 });
	goalscoredright3pts.anim.PushBack({ 97, 500, 12, 35 });
	goalscoredright3pts.anim.PushBack({ 109, 500, 8, 35 });
	goalscoredright3pts.anim.PushBack({ 116, 500, 6, 35 });
	goalscoredright3pts.anim.loop = false;
	goalscoredright3pts.lifetime = 200;
	goalscoredright3pts.speed.x = 0;
	goalscoredright3pts.anim.speed = 0.1f;

	goalscoredright5pts.anim.PushBack({ 239, 570, 60, 35 });
	goalscoredright5pts.anim.PushBack({ 298, 570, 56, 35 });
	goalscoredright5pts.anim.PushBack({ 239, 570, 60, 35 });
	goalscoredright5pts.anim.PushBack({ 298, 570, 56, 35 });
	goalscoredright5pts.anim.PushBack({ 239, 570, 60, 35 });
	goalscoredright5pts.anim.PushBack({ 298, 570, 56, 35 });
	goalscoredright5pts.anim.PushBack({ 239, 570, 60, 35 });
	goalscoredright5pts.anim.PushBack({ 298, 570, 56, 35 });
	goalscoredright5pts.anim.PushBack({ 239, 570, 60, 35 });
	goalscoredright5pts.anim.PushBack({ 298, 570, 56, 35 });
	goalscoredright5pts.anim.PushBack({ 239, 570, 60, 35 });
	goalscoredright5pts.anim.PushBack({ 298, 570, 56, 35 });
	/*--*/
	goalscoredright5pts.anim.PushBack({ 404, 570, 48, 35 });
	goalscoredright5pts.anim.PushBack({ 451, 570, 45, 35 });
	goalscoredright5pts.anim.PushBack({ 108, 570, 32, 35 });
	goalscoredright5pts.anim.PushBack({ 140, 570, 28, 35 });
	goalscoredright5pts.anim.PushBack({ 168, 570, 24, 35 });
	goalscoredright5pts.anim.PushBack({ 192, 570, 20, 35 });
	goalscoredright5pts.anim.PushBack({ 212, 570, 16, 35 });
	goalscoredright5pts.anim.PushBack({ 228, 570, 12, 35 });
	goalscoredright5pts.anim.loop = false;
	goalscoredright5pts.lifetime = 200;
	goalscoredright5pts.speed.x = 0;
	goalscoredright5pts.anim.speed = 0.1f;


	goalscoredleft3pts.anim.PushBack({ 141, 535, 58, 34 });
	goalscoredleft3pts.anim.PushBack({ 200, 535, 55, 34 });
	goalscoredleft3pts.anim.PushBack({ 141, 535, 58, 34 });
	goalscoredleft3pts.anim.PushBack({ 200, 535, 55, 34 });
	goalscoredleft3pts.anim.PushBack({ 141, 535, 58, 34 });
	goalscoredleft3pts.anim.PushBack({ 200, 535, 55, 34 });
	goalscoredleft3pts.anim.PushBack({ 141, 535, 58, 34 });
	goalscoredleft3pts.anim.PushBack({ 200, 535, 55, 34 });
	goalscoredleft3pts.anim.PushBack({ 141, 535, 58, 34 });
	goalscoredleft3pts.anim.PushBack({ 200, 535, 55, 34 });
	goalscoredleft3pts.anim.PushBack({ 141, 535, 58, 34 });
	goalscoredleft3pts.anim.PushBack({ 200, 535, 55, 34 });
	goalscoredleft3pts.anim.PushBack({ 141, 535, 58, 34 });
	goalscoredleft3pts.anim.PushBack({ 200, 535, 55, 34 });
	/*--*/
	goalscoredleft3pts.anim.PushBack({ 9, 535, 32, 35 });
	goalscoredleft3pts.anim.PushBack({ 41, 535, 28, 35 });
	goalscoredleft3pts.anim.PushBack({ 69, 535, 24, 35 });
	goalscoredleft3pts.anim.PushBack({ 93, 535, 20, 35 });
	goalscoredleft3pts.anim.PushBack({ 113, 535, 16, 35 });
	goalscoredleft3pts.anim.PushBack({ 129, 535, 12, 35 });
	goalscoredleft3pts.anim.loop = false;
	goalscoredleft3pts.lifetime = 200;
	goalscoredleft3pts.speed.x = 0;
	goalscoredleft3pts.anim.speed = 0.1f;

	goalscoredleft5pts.anim.PushBack({ 238, 606, 58, 34 });
	goalscoredleft5pts.anim.PushBack({ 297, 606, 56, 34 });
	goalscoredleft5pts.anim.PushBack({ 238, 606, 58, 34 });
	goalscoredleft5pts.anim.PushBack({ 297, 606, 56, 34 });
	goalscoredleft5pts.anim.PushBack({ 238, 606, 58, 34 });
	goalscoredleft5pts.anim.PushBack({ 297, 606, 56, 34 });
	goalscoredleft5pts.anim.PushBack({ 238, 606, 58, 34 });
	goalscoredleft5pts.anim.PushBack({ 297, 606, 56, 34 });
	goalscoredleft5pts.anim.PushBack({ 238, 606, 58, 34 });
	goalscoredleft5pts.anim.PushBack({ 297, 606, 56, 34 });
	goalscoredleft5pts.anim.PushBack({ 238, 606, 58, 34 });
	goalscoredleft5pts.anim.PushBack({ 297, 606, 56, 34 });
	/*--*/
	goalscoredleft5pts.anim.PushBack({ 403, 606, 47, 35 });
	goalscoredleft5pts.anim.PushBack({ 450, 606, 43, 35 });
	goalscoredleft5pts.anim.PushBack({ 146, 606, 32, 35 });
	goalscoredleft5pts.anim.PushBack({ 178, 606, 28, 35 });
	goalscoredleft5pts.anim.PushBack({ 206, 606, 20, 35 });
	goalscoredleft5pts.anim.PushBack({ 226, 606, 12, 35 });
	goalscoredleft5pts.anim.loop = false;
	goalscoredleft5pts.lifetime = 200;
	goalscoredleft5pts.speed.x = 0;
	goalscoredleft5pts.anim.speed = 0.1f;
	
	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1 && !particles[i]->collider->DISK || !particles[i]->collider->PARABOLIC_DISK) //&& !particles[i]->collider->DISK
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
		
		if (particles[i]->collider->DISK && c2->type == Collider::Type::UPPER_WALL || c2->type == Collider::Type::LOWER_WALL) //&& !particles[i]->collider->DISK
		{
			particles[i]->speed.NegateY();
			break;
		}
		else if(particles[i]->collider->DISK && c2->type == Collider::Type::PLAYER || c2->type == Collider::Type::LEFT_3P_GOAL || c2->type == Collider::Type::RIGHT_3P_GOAL
			|| c2->type == Collider::Type::LEFT_5P_GOAL || c2->type == Collider::Type::RIGHT_5P_GOAL)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
		
		if (particles[i]->collider->PARABOLIC_DISK && c2->type == Collider::Type::UPPER_WALL || c2->type == Collider::Type::LOWER_WALL)
		{
			particles[i]->speed.y = 0;
			particles[i]->speed.x = 0;
			break;
		}
		else if(particles[i]->collider->PARABOLIC_DISK && c2->type == Collider::Type::PLAYER)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
		/*else if(particles[i]->collider->PARABOLIC_DISK && particles[i]->anim.pingpong == false)
		{
			particles[i]->speed.x = 0;
			particles[i]->speed.y = 0;
			SDL_Delay(50);
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}*/
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture_particles, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			App->render->Blit(texture_disk, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}