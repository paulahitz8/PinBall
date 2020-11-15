#pragma once
#include "Module.h"
//#include "Globals.h"
//#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;

class LogoScreen : public Module
{
public:

	LogoScreen(Application* app, bool start_enabled = true);
	 ~LogoScreen();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:

	SDL_Texture* logoScreen;
	SDL_Rect rect;
	int timer = 0;
	uint logoFx = 0;
};