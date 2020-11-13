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


	//right1FlipperRect = { 307, 804, 104, 47 };
	//right2FlipperRect= { 470, 328, 79, 73 };
	//leftFlipperRect = { 176, 805, 104, 46 };
	//posInitial = { 566, 815 };

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
	SDL_Rect r1;
	SDL_Rect r2;
	SDL_Rect r3;
	SDL_Rect rball;

	r1 = { 307, 804, 104, 47 };
	r2 = { 470, 328, 79, 73 };
	r3 = { 176, 805, 104, 46 };
	rball = { 566, 815, 30, 30 };
	
	//ball->GetPosition(pos.x, pos.y);
	App->renderer->Blit(ballTex, posInitial.x, posInitial.y, &rball);

	//right1Flipper->GetPosition(pos.x, pos.y);
	//App->renderer->Blit(right1FlipperTex, 307, 804, &r1, 1.0f, right1Flipper->GetRotation());
	App->renderer->Blit(right1FlipperTex, 307, 804, &r1);

	//right2Flipper->GetPosition(pos.x, pos.y);
	//App->renderer->Blit(right2FlipperTex, 470, 328, &r2, 1.0f, right2Flipper->GetRotation());
	App->renderer->Blit(right2FlipperTex, 470, 328, &r2);

	//leftFlipper->GetPosition(pos.x, pos.y);
	//App->renderer->Blit(leftFlipperTex, 176, 805, &r3, 1.0f, leftFlipper->GetRotation());
	App->renderer->Blit(leftFlipperTex, 176, 805, &r3);

	

	return UPDATE_CONTINUE;
}



