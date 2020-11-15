#pragma once
#include "Module.h"

struct SDL_Texture;

class EndScreen : public Module
{
public:

	EndScreen(Application* app, bool start_enabled = false);
	~EndScreen();

	bool isActive = false;

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:

	SDL_Texture* endScreen;
};