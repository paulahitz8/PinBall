#include "EndScreen.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "FadeScreen.h"
#include "LogoScreen.h"
#include "IntroScreen.h"
#include "ModuleSceneIntro.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"



EndScreen::EndScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

EndScreen::~EndScreen() {}

bool EndScreen::Start()
{
	bool ret = true;
	isActive = true;
	App->player->lifeCount = 6;

	endScreen = App->textures->Load("pinball/gameoverScreen.png");
	endFx = App->audio->LoadFx("pinball/Sounds/gameOver.wav");
	//App->audio->PlayFx(endFx);
	return ret;
}

update_status EndScreen::Update()
{
	SDL_Rect rect;
	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	
	App->renderer->Blit(endScreen, 0, 0, &rect);
	
	//Scores
	if (App->scene_intro->score > App->scene_intro->previousScore && App->scene_intro->score > App->scene_intro->highScore)
	{
		App->scene_intro->highScore = App->scene_intro->score;
	}
	else if (App->scene_intro->score < App->scene_intro->previousScore)
	{
		App->scene_intro->highScore = App->scene_intro->previousScore;
	}

	App->scene_intro->previousScore = App->scene_intro->score;

	App->fonts->BlitText(382, 685, App->scene_intro->fontblack, App->scene_intro->scoreText);
	App->fonts->BlitText(382, 879, App->scene_intro->fontblack, App->scene_intro->highScoreText);
	App->fonts->BlitText(382, 793, App->scene_intro->fontblack, App->scene_intro->previousScoreText);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->player->Enable();
		App->scene_intro->Enable();
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) 
	{
		LOG("There are no physics available here");
	}

	return UPDATE_CONTINUE;
}

update_status EndScreen::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) { return UPDATE_STOP; }

	
	return UPDATE_CONTINUE;
}

bool EndScreen::CleanUp()
{
	LOG("Freeing scene");

	App->textures->Unload(endScreen);

	return true;
}