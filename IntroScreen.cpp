#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
//#include "ModuleWindow.h"
#include "FadeScreen.h"
#include "LogoScreen.h"
#include "IntroScreen.h"
//#include "ModuleSceneIntro.h"
//#include "ModulePlayer.h"



IntroScreen::IntroScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

IntroScreen::~IntroScreen() {}

bool IntroScreen::Start()
{
	bool ret = true;

	//app->audio->PlayMusic("Assets/audio/music/TitleScreenMusic.ogg");

	introScreen = App->textures->Load("Assets/textures/titleScreen.png");

	return ret;
}

update_status IntroScreen::Update()
{
	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	App->renderer->Blit(introScreen, 0, 0, &rect);
	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
	/*	app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->scene, 50.0f);*/
	}

	return UPDATE_CONTINUE;
}

update_status IntroScreen::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) { return UPDATE_STOP; }

	return UPDATE_CONTINUE;
}

bool IntroScreen::CleanUp()
{
	LOG("Freeing scene");

	App->textures->Unload(introScreen);

	return true;
}

