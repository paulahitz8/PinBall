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


LogoScreen::LogoScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

LogoScreen::~LogoScreen() {}


bool LogoScreen::Start()
{
	bool ret = true;

	logoScreen = App->textures->Load("Assets/textures/logoscreen.png");

	//App->audio->PlayMusic("Assets/audio/music/LogoScreenMusic.ogg");

	//app->map->active = false;
	//app->player->active = false;
	//app->scene->active = false;
	//app->titleScreen->active = false;
	//app->winScreen->active = false;
	//app->deathScreen->active = false;

	return ret;
}


update_status LogoScreen::Update()
{
	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	App->renderer->Blit(logoScreen, 0, 0, &rect);
	timer++;

	return UPDATE_CONTINUE;
}

update_status LogoScreen::PostUpdate()
{

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) { return UPDATE_STOP; }

	//if (timer == 190)
	//{
	//	app->fadeScreen->active = true;
	//	app->fadeScreen->FadeToBlack(this, (Module*)app->titleScreen, 50.0f);
	//}

	return UPDATE_CONTINUE;
}

bool LogoScreen::CleanUp()
{
	LOG("Freeing scene");

	App->textures->Unload(logoScreen);

	return true;
}

