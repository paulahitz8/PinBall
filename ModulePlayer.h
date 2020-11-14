#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"

#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;
class PhysBody;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	uint lifeCount = 3;

	bool isFlippin;
	bool isDead = false;
	bool waterSlide = false;

	SDL_Texture* right1FlipperTex = nullptr;
	SDL_Texture* right2FlipperTex = nullptr;
	SDL_Texture* leftFlipperTex = nullptr;
	SDL_Texture* ballTex = nullptr;

	iPoint posInitial;
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
};