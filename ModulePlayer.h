#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Animation.h"

#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;
class PhysBody;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = false);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	uint rec1Fx;
	uint rec2Fx;
	uint rec3Fx;
	uint flipperFx;
	uint bonusFx;

	uint lifeCount = 3;
	int timer = 0;

	bool isFlippin;
	bool isDead = false;
	bool waterSlide = false;

	bool hasPassed1 = false;
	bool hasPassed2 = false;
	bool hasPassed3 = false;
	bool totalPass = false;
	bool isTouchingBalls = false;

	SDL_Texture* right1FlipperTex = nullptr;
	SDL_Texture* right2FlipperTex = nullptr;
	SDL_Texture* leftFlipperTex = nullptr;
	SDL_Texture* ballTex = nullptr;
	SDL_Texture* sensorSprites = nullptr;

	iPoint posInitial;
	b2Vec2 vecInitial;
	iPoint pos;
	iPoint ballPos;

	PhysBody* ball = nullptr;

	PhysBody* propeller1 = nullptr;
	PhysBody* propeller2 = nullptr;
	PhysBody* propeller3 = nullptr;

	PhysBody* propeller1Pivot = nullptr;
	PhysBody* propeller2Pivot = nullptr;
	PhysBody* propeller3Pivot = nullptr;

	b2PrismaticJoint* propeller1Joint;
	b2PrismaticJoint* propeller2Joint;
	b2PrismaticJoint* propeller3Joint;

	PhysBody* right1Flipper = nullptr;
	PhysBody* right2Flipper = nullptr;
	PhysBody* leftFlipper = nullptr;

	PhysBody* right1FlipperPivot = nullptr;
	PhysBody* right2FlipperPivot = nullptr;
	PhysBody* leftFlipperPivot = nullptr;
	 
	b2RevoluteJoint* right1FlipperJoint = nullptr;
	b2RevoluteJoint* right2FlipperJoint = nullptr;
	b2RevoluteJoint* leftFlipperJoint = nullptr;

	Animation* currentEmergency1Animation = nullptr;
	Animation* currentEmergency2Animation = nullptr;
	Animation* currentEmergency3Animation = nullptr;
	Animation* currentBlue1Animation = nullptr;
	Animation* currentBlue2Animation = nullptr;
	Animation* currentBlue3Animation = nullptr;
	Animation* currentBlue4Animation = nullptr;
	Animation* currentBlue5Animation = nullptr;
	Animation* currentBlue6Animation = nullptr;
	Animation* currentBlue7Animation = nullptr;
	Animation* currentBlue8Animation = nullptr;
	Animation* currentTelAnimation = nullptr;

	Animation blank;
	Animation emergency;
	Animation blue;
	Animation tel;
};