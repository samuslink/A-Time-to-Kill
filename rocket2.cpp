#include "rocket2.h"

CRocket2::CRocket2()
{
	velocity = CVector(0.0, 2.5, 90.0);
	acceleration = CVector(0.0, -1.0, 0.0);
	distanceTravel = 0.0;
	size = 6.0f;
	isExplosion = false;

	explosion = NULL;
	explosionTex = new CTexture;

	Load();
}

CRocket2::~CRocket2()
{
	if (explosion != NULL)
	{
		explosion->KillSystem();
		delete [] explosion;
		explosion = NULL;
	}

	if (explosionTex != NULL)
	{
		delete explosionTex;
		explosionTex = NULL;
	}
}

void CRocket2::SetupExplosionTexture()
{
	glGenTextures(1, &explosionTex->texID);
	glBindTexture(GL_TEXTURE_2D, explosionTex->texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, explosionTex->width, explosionTex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, explosionTex->data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, explosionTex->width, explosionTex->height, GL_RGBA, GL_UNSIGNED_BYTE, explosionTex->data);
}

// Implement new physics system to simulate actual rocket trjectory
void CRocket2::OnAnimate(scalar_t deltaTime)
{
	// get initial direction of rocket
	float cosYaw = (float)cos(DEG2RAD(direction));
	float sinYaw = (float)sin(DEG2RAD(direction)); 
	float sinPitch = (float)sin(DEG2RAD(pitch));

	// account for forward progress of rocket since launch
	float speed = velocity.z * deltaTime;

	// account for gravity on rocket since launch
	float fall = (velocity.y + acceleration.y) * deltaTime;

	// increment gravity effect
	acceleration.y = acceleration.y * 1.05;

	// position rocket
	position.x += float(cosYaw)*speed;
	position.y += (float(sinPitch)+fall)*speed;
	position.z += float(sinYaw)*speed;

	distanceTravel += position.Length();

	if (isExplosion)
		explosion->Update(deltaTime);

	if (!isExplosion)
	{
		if (distanceTravel >= 500000.0f)
		{
			isExplosion = true;
			velocity = CVector(0.0, 0.0, 0.0);
			explosion = new CExplosion2(10, position, 0.1, explosionTex->texID);
		}
	}


}

void CRocket2::OnCollision(CObject *collisionObject)
{
	if (!isExplosion)
	{
		if (typeid(*collisionObject) == typeid(CTerrain))
		{
			if (((CTerrain*)collisionObject)->GetHeight(position.x, position.z) + size >= position.y)
			{
				isExplosion = true;
				velocity = CVector(0.0, 0.0, 0.0);
				explosion = new CExplosion2(1800, position, 5.0, explosionTex->texID);
//			PlayExplosion2();
			//PlaySound("explode2.wav",NULL,SND_FILENAME|SND_SYNC);
			}
		
			// do explosion
		}
		if (typeid(*collisionObject) == typeid(COgroEnemy))
		{
			isExplosion = true;
			velocity = CVector(0.0, 0.0, 0.0);
			explosion = new CExplosion2(1800, position, 5.0, explosionTex->texID);
//		Play//Explosion2();
			//PlaySound("explode2.wav",NULL,SND_FILENAME|SND_SYNC);
		}
		if (typeid(*collisionObject) == typeid(CSodEnemy))
		{
			isExplosion = true;
			velocity = CVector(0.0, 0.0, 0.0);
			explosion = new CExplosion2(1800, position, 15.0, explosionTex->texID);
//		PlayExplosion2();
			//PlaySound("explode2.wav",NULL,SND_FILENAME|SND_SYNC);
		}
	}
}

void CRocket2::OnDraw(CCamera *camera)
{
	// if the rocket has not yet exploded, draw the rocket model
	if (!isExplosion)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0, 0.0, 1.0);
		glTranslatef(position.x, position.y, position.z);
		glRotatef(-direction, 0.0, 1.0, 0.0);
		glScalef(0.025f, 0.025f, 0.025f);
		RenderFrame(0);
		glDisable(GL_TEXTURE_2D);
	}
	// draw explosion
	else
	{
		glDisable(GL_FOG);
		explosion->Render();
		glEnable(GL_FOG);
	}
}


void CRocket2::Load()
{
	CMD2Model::Load("models\\rocketair.md2", "models\\rocket.pcx");
	explosionTex->LoadTexture("explosion2.bmp");
	SetupExplosionTexture();
}

void CRocket2::Unload()
{
}

void CRocket2::OnPrepare()
{
	// perform collision detection from this entity with all other objects in world
	if (!isExplosion)
		ProcessCollisions(FindRoot());

	if (isExplosion)
	{
		if (explosion->IsDead()) /// && !audioSys->GetPerformance()->IsPlaying(entitySound->GetSegment(), NULL))
		{
			explosion->KillSystem();
			delete explosion;
			explosion = NULL;
			isExplosion = false;

			isDead = true;
		}
	}
}