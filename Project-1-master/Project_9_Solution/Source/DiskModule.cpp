#include "DiskModule.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

DISKMODULE::DISKMODULE(int x, int y) : position(x, y)
{
	spawnPos = position;
}

DISKMODULE::~DISKMODULE()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* DISKMODULE::GetCollider() const
{
	return collider;
}

void DISKMODULE::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void DISKMODULE::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void DISKMODULE::OnCollision(Collider* collider)
{
	/*App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);*/

	SetToDelete();
}

void DISKMODULE::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}