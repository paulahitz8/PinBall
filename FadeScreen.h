#pragma once
#include "Module.h"
#include "SDL\include\SDL_rect.h"

class FadeScreen : public Module
{
public:

	FadeScreen(Application* app, bool start_enabled = true);
	~FadeScreen();

	bool Start();
	update_status Update();
	update_status PostUpdate();

	bool FadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);

private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	}

	currentStep = Fade_Step::NONE;

	// A frame count system to handle the fade time and ratio
	uint frameCount = 0;
	uint maxFadeFrames = 0;

	// The rectangle of the screen, used to render the black rectangle
	SDL_Rect screenRect;

	// The modules that should be switched after the first step
	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
};
