#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = false);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();


public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor;
	bool sensed;


	SDL_Texture* ball = nullptr;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	SDL_Texture* background = nullptr;
	
	PhysBody* ball1S = nullptr;
	PhysBody* ball2S = nullptr;
	PhysBody* ball3S = nullptr;
	PhysBody* rectangle1S = nullptr;
	PhysBody* rectangle2S = nullptr;
	PhysBody* rectangle3S = nullptr;
	PhysBody* waterEntrance1S = nullptr;
	PhysBody* waterEntrance2S = nullptr;

	int font = -1;
	int score = 0;
	int highScore = 0;
	int previousScore = 0;

	char scoreText[16] = { "\0" };
	char highScoreText[16] = { "\0" };
	char previousScoreText[16] = { "\0" };

};
