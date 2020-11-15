#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "FadeScreen.h"
#include "LogoScreen.h"
#include "IntroScreen.h"
#include "ModuleSceneIntro.h"



LogoScreen::LogoScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

LogoScreen::~LogoScreen() {}


bool LogoScreen::Start()
{
	bool ret = true;
	timer = 0;

	logoScreen = App->textures->Load("pinball/LogoScreen2.png");

	logoFx = App->audio->LoadFx("pinball/Sounds/LogoScreenMusic.ogg");
	App->audio->PlayFx(logoFx);

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

	if (timer == 190)
	{
		App->fade->FadeToBlack(this, (Module*)App->intro, 50.0f);
	}

	return UPDATE_CONTINUE;
}

bool LogoScreen::CleanUp()
{
	LOG("Freeing scene");

	App->textures->Unload(logoScreen);

	return true;
}

