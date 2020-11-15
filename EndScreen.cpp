#include "EndScreen.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
//#include "ModuleWindow.h"
#include "FadeScreen.h"
#include "LogoScreen.h"
#include "IntroScreen.h"
#include "ModuleSceneIntro.h"
#include "ModulePlayer.h"



EndScreen::EndScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

EndScreen::~EndScreen() {}

bool EndScreen::Start()
{
	bool ret = true;

	//app->audio->PlayMusic("Assets/audio/music/TitleScreenMusic.ogg");

	endScreen = App->textures->Load("pinball/IntroScreen.png");

	return ret;
}

update_status EndScreen::Update()
{
	SDL_Rect rect;
	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	App->renderer->Blit(endScreen, 0, 0, &rect);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->player->Enable();
		App->scene_intro->Enable();

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

