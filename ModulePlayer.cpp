#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "Box2D/Box2D/Box2D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	right1FlipperTex = App->textures->Load("pinball/flipperdownright.png");
	right2FlipperTex = App->textures->Load("pinball/flipperupright.png");
	leftFlipperTex = App->textures->Load("pinball/flipperdownleft.png");
	ballTex = App->textures->Load("pinball/ball.png");

	posInitial = { 566, 815 };

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(right1FlipperTex);
	App->textures->Unload(right2FlipperTex);
	App->textures->Unload(leftFlipperTex);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	ball->GetPosition(pos.x, pos.y);
	App->renderer->Blit(ballTex, pos.x, pos.y, NULL);

	right1Flipper->GetPosition(pos.x, pos.y);
	App->renderer->Blit(right1FlipperTex, pos.x, pos.y, &right1FlipperRect, 1.0f, right1Flipper->GetRotation());

	right2Flipper->GetPosition(pos.x, pos.y);
	App->renderer->Blit(right2FlipperTex, pos.x, pos.y, &right2FlipperRect, 1.0f, right2Flipper->GetRotation());

	leftFlipper->GetPosition(pos.x, pos.y);
	App->renderer->Blit(leftFlipperTex, pos.x, pos.y, &leftFlipperRect, 1.0f, leftFlipper->GetRotation());


	return UPDATE_CONTINUE;
}



