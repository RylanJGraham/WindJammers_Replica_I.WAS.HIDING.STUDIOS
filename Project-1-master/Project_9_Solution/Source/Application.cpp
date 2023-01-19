#include <SDL/include/SDL.h>
#include <stdio.h>

#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Left_Japanese_Player.h"
#include "Right_Japanese_Player.h"
#include "UPC.h"
#include "SceneIntro.h"
#include "DataEast.h"
#include "MainScreen.h"
#include "TutorialScene.h"
#include "TurfLevel.h"
#include"BeachLevel.h"
#include "ClayModule.h"
#include "LeftGermanPlayer.h"
#include "RightGermanPlayer.h"
#include "LeftEnglishPlayer.h"
#include "RightEnglishPlayer.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ChooseMap.h"
#include "ChooseCharacter.h"
#include "UI.h"
#include "ModuleController.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);
	
	modules[4] = controller = new ModuleController(true);
	modules[5] = Upc = new UPC(true);
	modules[6] = sceneIntro = new SceneIntro(false);
	modules[7] = dataEast = new DataEast(false);
	modules[8] = mainScreen = new MainScreen(false);
	modules[9] = tutorialScene = new TutorialScene(false);
	modules[10] = chooseCharacter = new ChooseCharacter(false);
	modules[11] = chooseMap = new ChooseMap(false);
	modules[12] = turflevel = new TurfLevel(false);		//Gameplay scene starts disabled
	modules[13] = beachlevel = new BeachLevel(false);
	modules[14] = clay = new ClayModule(false);
	modules[15] = LeftJapanesePlayer = new Left_Japanese_Player(false);	//Player starts disabled
	modules[16] = leftgermanyplayer = new LeftGermanPlayer(false);
	modules[17] = rightgermanyplayer = new RightGermanPlayer(false);
	modules[18] = RightJapanesePlayer = new Right_Japanese_Player(false);
	modules[19] = leftenglishplayer = new LeftEnglishPlayer(false);
	modules[20] = righenglishplayer = new RightEnglishPlayer(false);
	modules[21] =	particles =		new ModuleParticles(true);
	modules[22] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled
	modules[23] =	collisions =	new ModuleCollisions(true);
	modules[24] =	fade =			new ModuleFadeToBlack(true);
	modules[25] =	fonts =			new ModuleFonts(true);
	modules[26] =	ui	 =			new UI(false);
	modules[27] =	render =		new ModuleRender(true);
	
	
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
