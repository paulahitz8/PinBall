#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "EndScreen.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{

	if (App->end->isActive == true)
	{
		App->player->isDead = false;
		App->end->Disable();
		App->end->isActive = false;
	}

	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("pinball/background1.png");
	ball = App->textures->Load("pinball/ball2.png");

	App->audio->PlayMusic("pinball/Sounds/song.ogg");

	//Font
	fontwhite = App->fonts->Load("pinball/fontwhite.png", "0123456789", 1);
	fontblack = App->fonts->Load("pinball/fontblack.png", "0123456789", 1);

	score = 0;

	//Creating sensors
	ball1S = App->physics->CreateRectangleSensor(326, 219, 61, 58);
	ball1S->listener = (Module*)App->player;

	ball2S = App->physics->CreateRectangleSensor(244, 251, 61, 60);
	ball2S->listener = (Module*)App->player;

	ball3S = App->physics->CreateRectangleSensor(340, 302, 62, 52);
	ball3S->listener = (Module*)App->player;

	rectangle1S = App->physics->CreateRectangleSensor(246, 129, 8, 9);
	rectangle1S->listener = (Module*)App->player;

	rectangle2S = App->physics->CreateRectangleSensor(290, 130, 8, 9);
	rectangle2S->listener = (Module*)App->player;

	rectangle3S = App->physics->CreateRectangleSensor(335, 131, 8, 9);
	rectangle3S->listener = (Module*)App->player;

	blue1S = App->physics->CreateRectangleSensor(318, 369, 5, 5);
	blue1S->listener = (Module*)App->player;

	blue2S = App->physics->CreateRectangleSensor(346, 360, 5, 5);
	blue2S->listener = (Module*)App->player;

	blue3S = App->physics->CreateRectangleSensor(376, 351, 5, 5);
	blue3S->listener = (Module*)App->player;

	blue4S = App->physics->CreateRectangleSensor(459, 425, 5, 5);
	blue4S->listener = (Module*)App->player;

	blue5S = App->physics->CreateRectangleSensor(459, 455, 5, 5);
	blue5S->listener = (Module*)App->player;

	blue6S = App->physics->CreateRectangleSensor(459, 486, 5, 5);
	blue6S->listener = (Module*)App->player;

	blue7S = App->physics->CreateRectangleSensor(72, 701, 5, 5);
	blue7S->listener = (Module*)App->player;

	blue8S = App->physics->CreateRectangleSensor(515, 701, 5, 5);
	blue8S->listener = (Module*)App->player;

	telS = App->physics->CreateRectangleSensor(410, 455, 39, 33);
	telS->listener = (Module*)App->player;

	greenHoleS = App->physics->CreateRectangleSensor(125, 137, 12, 13);
	greenHoleS->listener = (Module*)App->player;

	waterEntrance1S = App->physics->CreateRectangleSensor(180, 428, 26, 9);
	waterEntrance1S->listener = (Module*)App->player;

	waterEntrance2S = App->physics->CreateRectangleSensor(467, 645, 27, 11);
	waterEntrance2S->listener = (Module*)App->player;

	App->player->lifeCount = 3;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(background);
	App->textures->Unload(ball);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(background, 0, 0);

	// Prepare for raycast ------------------------------------------------------
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	sprintf_s(scoreText, 10, "%4d", score);
	sprintf_s(highScoreText, 10, "%4d", highScore);
	sprintf_s(previousScoreText, 10, "%4d", previousScore);
	sprintf_s(lifeText, 10, "%1d", App->player->lifeCount);

	App->fonts->BlitText(540, 35, fontwhite, scoreText);
	App->fonts->BlitText(80, 902, fontwhite, lifeText);

	return UPDATE_CONTINUE;
}

