#pragma once
#include "Module.h"

struct SDL_Texture;

class IntroScreen : public Module
{
public:

	IntroScreen(Application* app, bool start_enabled = false);
	~IntroScreen();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:

	SDL_Texture* introScreen;
	SDL_Rect rect;
};