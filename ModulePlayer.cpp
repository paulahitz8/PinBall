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

	posInitial = { 570, 815 };
	ballPos = posInitial;


	ball = App->physics->CreateCircle(posInitial.x, posInitial.y, 15, b2_dynamicBody);
	



	//Creating the flippers
	
	// Right Lower flipper 
	right1Flipper = App->physics->CreateRectangle(300, 805, 105, 20, b2_dynamicBody);
	right1Flipper_pivot = App->physics->CreateCircle( 385, 817, 7, b2_staticBody);

	b2RevoluteJointDef joint;

	joint.bodyA = right1Flipper->body;
	joint.bodyB = right1Flipper_pivot->body;

	right1Flipper->body->SetGravityScale(2.0f);

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
	right2Flipper_pivot = App->physics->CreateCircle(522, 332, 7, b2_staticBody);

	joint.bodyA = right2Flipper->body;
	joint.bodyB = right2Flipper_pivot->body;

	right2Flipper->body->SetGravityScale(2.0f);

	joint.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.enableLimit = true;
	joint.upperAngle = 37 * DEGTORAD;
	joint.lowerAngle = -25 * DEGTORAD;

	joint.motorSpeed = -2000.0f * DEGTORAD;
	joint.maxMotorTorque = 1500.0f;
	joint.enableMotor = false;

	right2FlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&joint);


	//Left Flipper

	leftFlipper = App->physics->CreateRectangle(210, 805, 105, 20, b2_dynamicBody);
	leftFlipper_pivot = App->physics->CreateCircle(205, 817, 7, b2_staticBody);

	joint.bodyA = leftFlipper->body;
	joint.bodyB = leftFlipper_pivot->body;

	leftFlipper->body->SetGravityScale(2.0f);

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


	//Creating the propellers

	//Propeller 1
	propeller1 = App->physics->CreateRectangle(580, 890, 28, 86, b2_dynamicBody);
	propeller1_pivot = App->physics->CreateCircle(580, 890, 14, b2_staticBody);

	b2PrismaticJointDef jointProp;

	jointProp.bodyA = propeller1->body;
	jointProp.bodyB = propeller1_pivot->body;

	jointProp.localAxisA.Set(0, 1);

	jointProp.localAnchorA.Set(0, 0);
	jointProp.localAnchorB.Set(0, 0);
	jointProp.collideConnected = false;

	jointProp.upperTranslation = PIXEL_TO_METERS(50);
	jointProp.enableLimit = true;
	jointProp.lowerTranslation = 0;

	jointProp.enableMotor = false;
	jointProp.maxMotorForce = 700;
	jointProp.motorSpeed = 5000;

	propeller1Joint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&jointProp);


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





	//Controls

	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		//ball = App->physics->add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 15, b2_dynamicBody));
		//delete ball;
		//ball->body = nullptr;

		ball = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 15, b2_dynamicBody);
		//ballPos.x = App->input->GetMouseX();
		//ballPos.y = App->input->GetMouseY();
	}

	if (((ballPos.x > 50 && ballPos.x < 96) && (ballPos.y >829 && ballPos.y < 872)) ||
		((ballPos.x > 493 && ballPos.x < 544) && (ballPos.y > 829 && ballPos.y < 872)))//&& lifeCount != 0)
	{
		b2Vec2 impulse = b2Vec2(0.0f, -8.0f);
		b2Vec2 point = ball->body->GetLocalCenter();
		ball->body->ApplyLinearImpulse(impulse, point, true);
		
	}

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
		right2FlipperJoint->EnableMotor(true);
		if (isFlippin == false)
		{
			//App->audio->PlayFx(flipperSound);
		}
		isFlippin = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		right1FlipperJoint->EnableMotor(false);
		right2FlipperJoint->EnableMotor(false);
		isFlippin = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		propeller1Joint->EnableMotor(true);
	}

	else
	{
		propeller1Joint->EnableMotor(false);
	}
	

	if (ballPos.y > 900)
	{
		
		if (lifeCount != 0)
		{
			ballPos = posInitial;
			lifeCount--;
		}
		else
		{
			isDead = true;
			//gameover
		}
	}



	SDL_Rect r1;
	SDL_Rect r2;
	SDL_Rect r3;
	SDL_Rect rball;

	r1 = { 302, 818, 109, 26 };
	r2 = { 457, 352, 101, 26 };
	r3 = { 176, 820, 110, 27 };
	rball = { 566, 815, 30, 30 };

	//Ball
	ball->GetPosition(ballPos.x, ballPos.y);
	App->renderer->Blit(ballTex, ballPos.x, ballPos.y, &rball);

	//Down right flipper
	right1Flipper->GetPosition(pos.x, pos.y);
	App->renderer->Blit(right1FlipperTex, pos.x, pos.y, &r1, 1.0f, right1Flipper->GetRotation());

	//Up right flipper
	right2Flipper->GetPosition(pos.x, pos.y);
	App->renderer->Blit(right2FlipperTex, pos.x - 5, pos.y - 5, &r2, 1.0f, right2Flipper->GetRotation());

	//Left flipper
	leftFlipper->GetPosition(pos.x, pos.y);
	App->renderer->Blit(leftFlipperTex, pos.x, pos.y, &r3, 1.0f, leftFlipper->GetRotation());


	return UPDATE_CONTINUE;
}



