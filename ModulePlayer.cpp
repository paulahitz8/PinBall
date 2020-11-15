#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "EndScreen.h"
#include "LogoScreen.h"
#include "Box2D/Box2D/Box2D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	blank.PushBack({ 600, 118, 29, 29 });

	emergency.PushBack({ 479, 118, 29, 29 });

	blue.PushBack({ 391, 196, 27, 27 });
	blue.PushBack({ 600, 196, 27, 27 });
	blue.speed = 0.02f;

	tel.PushBack({ 622, 429, 73, 61 });
	tel.PushBack({ 600, 196, 27, 27 });
	tel.speed = 0.2f;

	right1FlipperTex = App->textures->Load("pinball/flipperdownrightstraight.png");
	right2FlipperTex = App->textures->Load("pinball/flipperuprightstraight.png");
	leftFlipperTex = App->textures->Load("pinball/flipperdownleftstraight.png");
	ballTex = App->textures->Load("pinball/ball.png");
	sensorSprites = App->textures->Load("pinball/Sprites.png");

	rec1Fx = App->audio->LoadFx("pinball/Sounds/rec1.ogg");
	rec2Fx = App->audio->LoadFx("pinball/Sounds/rec2.ogg");
	rec3Fx = App->audio->LoadFx("pinball/Sounds/rec3.ogg");
	flipperFx = App->audio->LoadFx("pinball/Sounds/flipper.wav");
	ballSpawn = App->audio->LoadFx("pinball/Sounds/MenuSelectionClick.ogg");
	bonusFx = App->audio->LoadFx("pinball/Sounds/bonus.ogg");
	boingFx = App->audio->LoadFx("pinball/Sounds/boing.ogg");


	posInitial = { 570, 820 };
	vecInitial = { 570, 815 };
	ballPos = posInitial;
	

	currentEmergency1Animation = &blank;
	currentEmergency2Animation = &blank;
	currentEmergency3Animation = &blank;
	currentBlue1Animation = &blank;
	currentBlue2Animation = &blank;
	currentBlue3Animation = &blank;
	currentBlue4Animation = &blank;
	currentBlue5Animation = &blank;
	currentBlue6Animation = &blank;
	currentBlue7Animation = &blank;
	currentBlue8Animation = &blank;
	currentTelAnimation = &blank;


	ball = App->physics->CreateCircle(posInitial.x, posInitial.y, 15, b2_dynamicBody);

	//Creating the flippers
	// Right Lower flipper 
	b2RevoluteJointDef joint;
	right1Flipper = App->physics->CreateRectangle(300, 805, 105, 20, b2_dynamicBody);
	right1FlipperPivot = App->physics->CreateCircle( 385, 817, 7, b2_staticBody);
	joint.bodyA = right1Flipper->body;
	joint.bodyB = right1FlipperPivot->body;
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
	right2FlipperPivot = App->physics->CreateCircle(522, 332, 7, b2_staticBody);
	joint.bodyA = right2Flipper->body;
	joint.bodyB = right2FlipperPivot->body;
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
	leftFlipperPivot = App->physics->CreateCircle(205, 817, 7, b2_staticBody);
	joint.bodyA = leftFlipper->body;
	joint.bodyB = leftFlipperPivot->body;
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
	//Propeller
	b2PrismaticJointDef jointProp;
	propeller1 = App->physics->CreateRectangle(580, 890, 28, 86, b2_dynamicBody);
	propeller1Pivot = App->physics->CreateCircle(580, 890, 14, b2_staticBody);
	jointProp.bodyA = propeller1->body;
	jointProp.bodyB = propeller1Pivot->body;
	jointProp.upperTranslation = PIXEL_TO_METERS(50);
	jointProp.lowerTranslation = 0;
	jointProp.localAnchorA.Set(0, 0);
	jointProp.localAnchorB.Set(0, 0);	
	jointProp.localAxisA.Set(0, 1);
	jointProp.collideConnected = false;
	jointProp.enableLimit = true;
	jointProp.enableMotor = false;
	jointProp.maxMotorForce = 3000;
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
	App->textures->Unload(sensorSprites);

	delete ball;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->end->isActive == false) 
	{

		if (totalPass == true)
		{
			timer++;
			if (timer == 20)
			{
				totalPass = false;
				timer = 0;
			}
		}

		if (totalPassB == true)
		{
			timerB++;
			if (timerB == 20)
			{
				totalPassB = false;
				timerB = 0;
			}
		}

		if (ringRang == true)
		{
			timerR++;
			if (timerR == 50)
			{
				ringRang = false;
				currentTelAnimation = &blank;
				timerR = 0;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP) 
		
		{
			App->audio->PlayFx(boingFx);
			propeller1Joint->EnableMotor(true);
		}

		else
		{
			propeller1Joint->EnableMotor(false);
		}

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			ball = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 15, b2_dynamicBody);
		}

		if (((ballPos.x > 50 && ballPos.x < 96) && (ballPos.y > 829 && ballPos.y < 872)) ||
			((ballPos.x > 493 && ballPos.x < 544) && (ballPos.y > 829 && ballPos.y < 872)))
		{
			b2Vec2 impulse = b2Vec2(0.0f, -8.0f);
			b2Vec2 point = ball->body->GetLocalCenter();
			ball->body->ApplyLinearImpulse(impulse, point, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			right1FlipperJoint->EnableMotor(true);
			right2FlipperJoint->EnableMotor(true);
			if (isFlippin == false)
			{
				App->audio->PlayFx(flipperFx);
			}
			isFlippin = true;
		}

		else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			right1FlipperJoint->EnableMotor(false);
			right2FlipperJoint->EnableMotor(false);
			isFlippin = false;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			leftFlipperJoint->EnableMotor(true);
			if (isFlippin == false)
			{
				App->audio->PlayFx(flipperFx);
			}
			isFlippin = true;
		}

		else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		{
			leftFlipperJoint->EnableMotor(false);
			isFlippin = false;
		}


		if (App->scene_intro->score > App->scene_intro->highScore)
		{
			App->scene_intro->highScore = App->scene_intro->score;
		}


		if (ballPos.y > 920)
		{
			lifeCount--;
			if (lifeCount > 0)
			{
				b2Vec2 startPos = { PIXEL_TO_METERS(570.0f),PIXEL_TO_METERS(815.0f) };

				currentEmergency1Animation = &blank;
				currentEmergency2Animation = &blank;
				currentEmergency3Animation = &blank;
				currentBlue1Animation = &blank;
				currentBlue2Animation = &blank;
				currentBlue3Animation = &blank;
				currentBlue4Animation = &blank;
				currentBlue5Animation = &blank;
				currentBlue6Animation = &blank;
				currentBlue7Animation = &blank;
				currentBlue8Animation = &blank;
				currentTelAnimation = &blank;

				hasPassed1 = false;
				hasPassed2 = false;
				hasPassed3 = false;
				totalPass = false;
				isTouchingBalls = false;
				hasPassedB1 = false;
				hasPassedB2 = false;
				hasPassedB3 = false;
				hasPassedB4 = false;
				hasPassedB5 = false;
				hasPassedB6 = false;
				hasPassedB7 = false;
				hasPassedB8 = false;
				totalPassB = false;
				ringRang = false;

				ball->body->SetTransform(startPos, ball->GetRotation());

				App->audio->PlayFx(ballSpawn);
			}
			else if (lifeCount == 0)
			{
				currentEmergency1Animation = &blank;
				currentEmergency2Animation = &blank;
				currentEmergency3Animation = &blank;
				currentBlue1Animation = &blank;
				currentBlue2Animation = &blank;
				currentBlue3Animation = &blank;
				currentBlue4Animation = &blank;
				currentBlue5Animation = &blank;
				currentBlue6Animation = &blank;
				currentBlue7Animation = &blank;
				currentBlue8Animation = &blank;
				currentTelAnimation = &blank;

				hasPassed1 = false;
				hasPassed2 = false;
				hasPassed3 = false;
				totalPass = false;
				isTouchingBalls = false;
				hasPassedB1 = false;
				hasPassedB2 = false;
				hasPassedB3 = false;
				hasPassedB4 = false;
				hasPassedB5 = false;
				hasPassedB6 = false;
				hasPassedB7 = false;
				hasPassedB8 = false;
				totalPassB = false;
				ringRang = false;
				
				b2Vec2 startPos = { PIXEL_TO_METERS(570.0f),PIXEL_TO_METERS(815.0f) };
				App->player->ball->body->SetTransform(startPos, App->player->ball->GetRotation());
				isDead = true;
			}
		}

		currentEmergency1Animation->Update();
		currentEmergency2Animation->Update();
		currentEmergency3Animation->Update();
		currentBlue1Animation->Update();
		currentBlue2Animation->Update();
		currentBlue3Animation->Update();
		currentBlue4Animation->Update();
		currentBlue5Animation->Update();
		currentBlue6Animation->Update();
		currentBlue7Animation->Update();
		currentBlue8Animation->Update();
		currentTelAnimation->Update();

		SDL_Rect rectEmergency1 = currentEmergency1Animation->GetCurrentFrame();
		SDL_Rect rectEmergency2 = currentEmergency2Animation->GetCurrentFrame();
		SDL_Rect rectEmergency3 = currentEmergency3Animation->GetCurrentFrame();
		SDL_Rect rectBlue1 = currentBlue1Animation->GetCurrentFrame();
		SDL_Rect rectBlue2 = currentBlue2Animation->GetCurrentFrame();
		SDL_Rect rectBlue3 = currentBlue3Animation->GetCurrentFrame();
		SDL_Rect rectBlue4 = currentBlue4Animation->GetCurrentFrame();
		SDL_Rect rectBlue5 = currentBlue5Animation->GetCurrentFrame();
		SDL_Rect rectBlue6 = currentBlue6Animation->GetCurrentFrame();
		SDL_Rect rectBlue7 = currentBlue7Animation->GetCurrentFrame();
		SDL_Rect rectBlue8 = currentBlue8Animation->GetCurrentFrame();
		SDL_Rect rectTel = currentTelAnimation->GetCurrentFrame();

		App->renderer->Blit(sensorSprites, 237, 119, &rectEmergency1);
		App->renderer->Blit(sensorSprites, 280, 119, &rectEmergency2);
		App->renderer->Blit(sensorSprites, 325, 119, &rectEmergency3);
		App->renderer->Blit(sensorSprites, 304, 359, &rectBlue1);
		App->renderer->Blit(sensorSprites, 332, 350, &rectBlue2);
		App->renderer->Blit(sensorSprites, 362, 340, &rectBlue3);
		App->renderer->Blit(sensorSprites, 447, 415, &rectBlue4);
		App->renderer->Blit(sensorSprites, 447, 445, &rectBlue5);
		App->renderer->Blit(sensorSprites, 447, 475, &rectBlue6);
		App->renderer->Blit(sensorSprites, 57, 690, &rectBlue7);
		App->renderer->Blit(sensorSprites, 501, 690, &rectBlue8);
		App->renderer->Blit(sensorSprites, 380, 425, &rectTel);

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
	}

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {

	if (isDead == true) 
	{
		App->scene_intro->Disable();
		App->end->Enable();
		App->physics->debug = false;
		lifeCount = 3;
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	if (hasPassed1 == true && hasPassed2 == true && hasPassed3 == true)
	{
		totalPass = true;
		App->scene_intro->score += 500;
		currentEmergency1Animation = &blank;
		currentEmergency2Animation = &blank;
		currentEmergency3Animation = &blank;
		hasPassed1 = false;
		hasPassed2 = false;
		hasPassed3 = false;
	}

	else if (bodyA == App->scene_intro->rectangle1S) 
	{
		if (hasPassed1 == false && totalPass == false)
		{
			App->audio->PlayFx(rec1Fx);
			currentEmergency1Animation = &emergency;
			hasPassed1 = true;
		}
	}

	else if (bodyA == App->scene_intro->rectangle2S)
	{
		if (hasPassed2 == false && totalPass == false)
		{
			App->audio->PlayFx(rec2Fx);
			currentEmergency2Animation = &emergency;
			hasPassed2 = true;
		}
	} 

	else if (bodyA == App->scene_intro->rectangle3S)
	{
		if (hasPassed3 == false && totalPass == false)
		{
			App->audio->PlayFx(rec3Fx);
			currentEmergency3Animation = &emergency;
			hasPassed3 = true;
		}
	} 

	if (bodyA == App->scene_intro->ball1S || bodyA == App->scene_intro->ball2S || bodyA == App->scene_intro->ball3S)
	{
		if (isTouchingBalls == false)
		{
			isTouchingBalls = true;
			App->scene_intro->score += 15;
		}
	}

	else 
	{
		isTouchingBalls = false;
	}

	if (hasPassedB1 == true && hasPassedB2 == true && hasPassedB3 == true && hasPassedB4 == true && hasPassedB5 == true && hasPassedB6 == true && hasPassedB7 == true && hasPassedB8 == true)
	{
		totalPassB = true;
		App->audio->PlayFx(bonusFx);
		App->scene_intro->score += 500;
		currentBlue1Animation = &blank;
		currentBlue2Animation = &blank;
		currentBlue3Animation = &blank;
		currentBlue4Animation = &blank;
		currentBlue5Animation = &blank;
		currentBlue6Animation = &blank;
		currentBlue7Animation = &blank;
		currentBlue8Animation = &blank;
		hasPassedB1 = false;
		hasPassedB2 = false;
		hasPassedB3 = false;
		hasPassedB4 = false;
		hasPassedB5 = false;
		hasPassedB6 = false;
		hasPassedB7 = false;
		hasPassedB8 = false;
	}

	else if (bodyA == App->scene_intro->blue1S)
	{
		if (hasPassedB1 == false && totalPassB == false)
		{
			currentBlue1Animation = &blue;
			hasPassedB1 = true;
		}
	}

	else if (bodyA == App->scene_intro->blue2S)
	{
		if (hasPassedB2 == false && totalPassB == false)
		{
			currentBlue2Animation = &blue;
			hasPassedB2 = true;
		}
	}

	else if (bodyA == App->scene_intro->blue3S)
	{
		if (hasPassedB3 == false && totalPassB == false)
		{
			currentBlue3Animation = &blue;
			hasPassedB3 = true;
		}
	}

	else if (bodyA == App->scene_intro->blue4S)
	{
		if (hasPassedB4 == false && totalPassB == false)
		{
			currentBlue4Animation = &blue;
			hasPassedB4 = true;
		}
	}

	else if (bodyA == App->scene_intro->blue5S)
	{
		if (hasPassedB5 == false && totalPassB == false)
		{
			currentBlue5Animation = &blue;
			hasPassedB5 = true;
		}
	}

	else if (bodyA == App->scene_intro->blue6S)
	{
		if (hasPassedB6 == false && totalPassB == false)
		{
			currentBlue6Animation = &blue;
			hasPassedB6 = true;
		}
	}

	else if (bodyA == App->scene_intro->blue7S)
	{
		if (hasPassedB7 == false && totalPassB == false)
		{
			currentBlue7Animation = &blue;
			hasPassedB7 = true;
		}
	}

	else if (bodyA == App->scene_intro->blue8S)
	{
		if (hasPassedB8 == false && totalPassB == false)
		{
			currentBlue8Animation = &blue;
			hasPassedB8 = true;
		}
	}

	if (bodyA == App->scene_intro->telS)
	{
		if (ringRang == false)
		{
			App->scene_intro->score += 20;
			currentTelAnimation = &tel;
			ringRang = true;
		}
	}

	if (bodyA == App->scene_intro->greenHoleS)
	{
		App->scene_intro->score += 250;
	}
}


