#include "world.h"

CWorld::CWorld()   
{   
    terrain = new CTerrain(32, 0.5);
	texture.LoadTexture("wall.bmp");
}   
   
CWorld::~CWorld()   
{   
    //audioSystem->Shutdown(); 
	//soundSystem->Shutdown();
	//delete soundSystem;
	delete gui;
    delete terrain;
	gui = NULL;
	terrain = NULL;
   // delete audioSystem;   
   // delete worldSound;   
}   
   
CWorld::CWorld(CCamera *c)   
{   
    camera = c;   
    terrain = new CTerrain(32, 1.0f);
	gun = new CGun;
	player = new CPlayer;
	gui = new CGUI;

	gameDone = false;
	gun->Load();
	gun->AttachTo(terrain);
	gun->texture[0].LoadTexture("shock_rifle.bmp");

	player->AttachTo(terrain);
	player->SetCamera(camera);
	player->SetGun(gun);
	player->SetTerrain(terrain);

	LoadWorld();
	timeStart = 300.0;
	timeElapsed = 0.0;
	gui->SetCurrentTime(timeStart);
	gui->SetEnemiesLeft(numOgros + numSods); 
    //audioSystem = new CAudioSystem; 
	//soundSystem = new SoundClass;
    //audioSystem->InitDirectXAudio(NULL);
	//soundSystem->Initialize(NULL);
    //worldSound = audioSystem->Create("ambient.wav", false);   
    //audioSystem->Play(worldSound, DMUS_SEG_REPEAT_INFINITE);
	PlaySound("ambient.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	//soundSystem->LoadWavefile("start.wav");  
}   
   
void CWorld::Animate(float deltaTime)   
{   
    // 根据地形设置摄像机的高度位置    
    camera->position.y = terrain->GetHeight(camera->position.x, camera->position.z) + 10.0f;  
if (camera->position.x <= terrain->GetScanDepth())
		camera->position.x = terrain->GetScanDepth();
	if (camera->position.x >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		camera->position.x = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
	if (camera->position.z <= terrain->GetScanDepth())
		camera->position.z = terrain->GetScanDepth();
	if (camera->position.z >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		camera->position.z = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
    
	terrain->Animate(deltaTime);

	const type_info &ogro = typeid(COgroEnemy);  // get ogro typeid
	const type_info &sod = typeid(CSodEnemy);    // get sod typeid

	numOgros = CountObjectTypes(ogro);           // count ogros
	numSods = CountObjectTypes(sod);             // count sods

	gui->SetEnemiesLeft(numOgros + numSods);
	gui->SetCurrentTime(timeStart - timeElapsed);

	if (!gameDone)
		timeElapsed += deltaTime;
	else
		timeElapsed = timeStart;
}

void CWorld::FadeScreen()
{
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0, 0.0, 0.0, 0.7);
	glBegin(GL_QUADS);
	glVertex3f(-5, -5, -3.0);
	glVertex3f(5, -5, -3.0);
	glVertex3f(5, 5, -3.0);
	glVertex3f(-5, 5, -3.0);
	glEnd();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
} 

void CWorld::SetScreen(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}
void CWorld::Draw(CCamera *camera)   
{   
    terrain->Draw(camera);  
	gui->Draw();

	if (gameDone)
	{
		FadeScreen();
		if (numOgros + numSods <=0)
			gui->DrawWinner();
		else
			gui->DrawLoser();
	}
}   
   
void CWorld::OnPrepare()   
{   
    glClearColor(terrain->fogColor[0], terrain->fogColor[1], terrain->fogColor[2], terrain->fogColor[3]);   
    terrain->Prepare(); 

	if ((numOgros + numSods <= 0) || (timeElapsed >= timeStart))
		gameDone = true;
}   

// LoadWorld()
// desc: initializes the world
void CWorld::LoadWorld()
{
	int enemyIdx = 0;
	int rndInt = 0;

	numOgros = 0;
	numSods = 0;

	srand((unsigned int)time(NULL));
	
	rndInt = (rand() % (MAX_ENEMIES-4)) + 4;	// random # from 4 to MAX
	numOgros = numSods = rndInt;

	// generate ogros
	for (enemyIdx = 0; enemyIdx < numOgros; enemyIdx++)
	{
		ogroEnemy = new COgroEnemy;
		ogroEnemy->AttachTo(terrain);
		ogroEnemy->SetPlayer(player);
		ogroEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		ogroEnemy->position.y = 0.0f;
		ogroEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}

	// generate sods
	for (enemyIdx = 0; enemyIdx < numSods; enemyIdx++)
	{
		sodEnemy = new CSodEnemy;
		sodEnemy->AttachTo(terrain);
		sodEnemy->SetPlayer(player);
		sodEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		sodEnemy->position.y = 0.0f;
		sodEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}
}

// CountObjectTypes
// desc: counts the number of objects passed as classID in the hierarchy
int CWorld::CountObjectTypes(const type_info &classID)
{
	int count = 0;
	CObject *c1;
	CObject *c2;

	c1 = (CObject*)terrain->childNode;

	while (c1 != NULL)
	{
		c2 = c1;
		do
		{
			if (typeid(*c2) == classID)
				count++;
			c2 = (CObject*)c2->nextNode;
		} while (!c2->IsFirstChild());

		count--;

		c1 = (CObject*)c1->childNode;
	}

	return count;
}

