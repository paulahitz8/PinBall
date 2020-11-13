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

	right1FlipperTex = App->textures->Load("pinball/flipperdownrightstraight.png");
	right2FlipperTex = App->textures->Load("pinball/flipperuprightstraight.png");
	leftFlipperTex = App->textures->Load("pinball/flipperdownleftstraight.png");
	ballTex = App->textures->Load("pinball/ball.png");

	posInitial = { 566, 815 };

	//Creating the flippers
	// Right Lower flipper 

	right1Flipper = App->physics->CreateRectangle(310, 805, 85, 22, b2_dynamicBody);
	right1Flipper_pivot = App->physics->CreateCircle( 395, 813, 7, b2_staticBody);

	b2RevoluteJointDef joint;

	joint.bodyA = right1Flipper->body;
	joint.bodyB = right1Flipper_pivot->body;

	//right1Flipper->body->SetGravityScale(9.81f);

	joint.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.enableLimit = true;
	joint.upperAngle = 25 * DEGTORAD;
	joint.lowerAngle = -25 * DEGTORAD;

	joint.motorSpeed = -2000.0f * DEGTORAD;
	joint.maxMotorTorque = 1500.0f;
	joint.enableMotor = false;

	right1FlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&joint);


	// Right Upper flipper

	right2Flipper = App->physics->CreateRectangle(454, 320, 85, 22, b2_dynamicBody);
	right2Flipper_pivot = App->physics->CreateCircle(538, 325, 7, b2_staticBody);

	joint.bodyA = right2Flipper->body;
	joint.bodyB = right2Flipper_pivot->body;

	//right2Flipper->body->SetGravityScale(9.81f);

	joint.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.enableLimit = true;
	joint.upperAngle = 25 * DEGTORAD;
	joint.lowerAngle = -25 * DEGTORAD;

	joint.motorSpeed = -2000.0f * DEGTORAD;
	joint.maxMotorTorque = 1500.0f;
	joint.enableMotor = false;

	right2FlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&joint);


	//Left Flipper

	leftFlipper = App->physics->CreateRectangle(200, 805, 85, 20, b2_dynamicBody);
	leftFlipper_pivot = App->physics->CreateCircle(200, 813, 7, b2_staticBody);

	joint.bodyA = leftFlipper->body;
	joint.bodyB = leftFlipper_pivot->body;

	//leftFlipper->body->SetGravityScale(9.81f);

	joint.localAnchorA.Set(PIXEL_TO_METERS(-25), 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.enableLimit = true;
	joint.upperAngle = 25 * DEGTORAD;
	joint.lowerAngle = -25 * DEGTORAD;

	joint.motorSpeed = 2000.0f * DEGTORAD;
	joint.maxMotorTorque = 1500.0f;
	joint.enableMotor = false;

	leftFlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&joint);

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

	r1 = { 302, 818, 109, 26 };
	r2 = { 457, 352, 101, 26 };
	r3 = { 176, 820, 110, 27 };
	rball = { 566, 815, 30, 30 };
	
	//ball->GetPosition(pos.x, pos.y);
	App->renderer->Blit(ballTex, posInitial.x, posInitial.y, &rball);

	//right1Flipper->GetPosition(pos.x, pos.y);
	//App->renderer->Blit(right1FlipperTex, 307, 804, &r1, 1.0f, right1Flipper->GetRotation());
	App->renderer->Blit(right1FlipperTex, 302, 805, &r1);

	//right2Flipper->GetPosition(pos.x, pos.y);
	//App->renderer->Blit(right2FlipperTex, 470, 328, &r2, 1.0f, right2Flipper->GetRotation());
	App->renderer->Blit(right2FlipperTex, 454, 320, &r2);

	//leftFlipper->GetPosition(pos.x, pos.y);
	//App->renderer->Blit(leftFlipperTex, 176, 805, &r3, 1.0f, leftFlipper->GetRotation());
	App->renderer->Blit(leftFlipperTex, 176, 805, &r3);


	//Controlls

	//if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && lifeCount != 0)
	//{
	//	b2Vec2 impulse = b2Vec2(0.0f, -3.5f);
	//	b2Vec2 point = ball->body->GetLocalCenter();

	//	ball->body->ApplyLinearImpulse(impulse, point, true);
	//}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		leftFlipperJoint->EnableMotor(true);
		if (isFlippin == false)
		{
			//App->audio->PlayFx(flipperSound);
		}
		isFlippin = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		leftFlipperJoint->EnableMotor(false);
		isFlippin = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		right1FlipperJoint->EnableMotor(true);
		right1FlipperJoint->EnableMotor(true);
		if (isFlippin == false)
		{
			//App->audio->PlayFx(flipperSound);
		}
		isFlippin = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		right1FlipperJoint->EnableMotor(false);
		right1FlipperJoint->EnableMotor(false);
		isFlippin = false;
	}

	//if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
	//	propeller1Joint->EnableMotor(true);
	//	//App->audio->PlayFx(horseSound);
	//	//horse.Reset();
	//}

	//else
	//{
	//	propeller1Joint->EnableMotor(false);
	//}
	

	return UPDATE_CONTINUE;
}



