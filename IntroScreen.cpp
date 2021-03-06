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



IntroScreen::IntroScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

IntroScreen::~IntroScreen() {}

bool IntroScreen::Start()
{
	bool ret = true;

	introScreen = App->textures->Load("pinball/IntroScreen.png");

	return ret;
}

update_status IntroScreen::Update()
{
	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	App->renderer->Blit(introScreen, 0, 0, &rect);
	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_intro, 50.0f);
		App->player->Enable();
		//App->physics->Enable();
		App->scene_intro->Enable();
		
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

