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
	PhysBody* blue1S = nullptr;
	PhysBody* blue2S = nullptr;
	PhysBody* blue3S = nullptr;
	PhysBody* blue4S = nullptr;
	PhysBody* blue5S = nullptr;
	PhysBody* blue6S = nullptr;
	PhysBody* blue7S = nullptr;
	PhysBody* blue8S = nullptr;
	PhysBody* telS = nullptr;
	PhysBody* greenHoleS = nullptr;
	PhysBody* waterEntrance1S = nullptr;
	PhysBody* waterEntrance2S = nullptr;

	int font = -1;
	int score;
	int highScore;
	int previousScore;

	char scoreText[10] = { "\0" };
	char highScoreText[10] = { "\0" };
	char previousScoreText[10] = { "\0" };
	char lifeText[10] = { "\0" };


};
