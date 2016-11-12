#include "player.h"

void CPlayer::FireWeapon()
{
	// use camera->lookAt vector and multiply
	// this lookAt vector by the ammo's speed
	// to get the ammo velocity vector.
	// create the new ammo and attach it to
	// the world. fire the ammo

	CRocket *newRocket = new CRocket;

	newRocket->pitch = camera->pitch;
	newRocket->direction = direction;
	newRocket->position = position;
	newRocket->forward = camera->lookAt.UnitVector();
    
	//newRocket->SetAudioSystem(audioSys);
	newRocket->AttachTo(terrain);

	//audioSys->PlayRocket();
}

void CPlayer::FireAuxWeapon()
{
	CRocket2 *newRocket2 = new CRocket2;

	newRocket2->pitch = camera->pitch;
	newRocket2->direction = direction;
	newRocket2->position = position;
	newRocket2->forward = camera->lookAt.UnitVector();
	//newRocket2->SetAudioSystem(audioSys);
	newRocket2->AttachTo(terrain);

	//audioSys->PlayRocket();
}