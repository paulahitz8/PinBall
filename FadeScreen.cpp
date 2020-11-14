//#define _CRT_SECURE_NO_WARNINGS
//#include "Application.h"
//#include "Globals.h"
//
//#include "ModuleTextures.h"
//#include "ModuleRender.h"
//#include "FadeScreen.h"
//#include "ModuleWindow.h"
//
//#include "SDL/include/SDL_render.h"
//
//FadeScreen::FadeScreen(Application* app, bool start_enabled = true) : Module(app, start_enabled) {}
//
//// Destructor
//FadeScreen::~FadeScreen() {}
//
//// Called before the first frame
//bool FadeScreen::Start()
//{
//	LOG("Preparing Fade Screen");
//
//	screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//	// Enable blending mode for transparency
//	SDL_SetRenderDrawBlendMode(App->renderer->renderer, SDL_BLENDMODE_BLEND);
//
//	return true;
//}
//
//// Called each loop iteration
//update_status FadeScreen::PreUpdate()
//{
//	return UPDATE_CONTINUE;
//}
//
//// Called each loop iteration
//update_status FadeScreen::Update(float dt)
//{
//	// Exit this function if we are not performing a fade
//	if (currentStep == Fade_Step::NONE) return UPDATE_CONTINUE;
//
//	if (currentStep == Fade_Step::TO_BLACK)
//	{
//		++frameCount;
//		if (frameCount >= maxFadeFrames)
//		{
//			moduleToDisable->Disable();
//			moduleToEnable->Enable();
//
//			currentStep = Fade_Step::FROM_BLACK;
//		}
//	}
//	else
//	{
//		--frameCount;
//		if (frameCount <= 0)
//		{
//			currentStep = Fade_Step::NONE;
//		}
//	}
//
//	return UPDATE_CONTINUE;
//}
//
//// Called each loop iteration
//update_status FadeScreen::PostUpdate()
//{
//	// Exit this function if we are not performing a fade
//	if (currentStep == Fade_Step::NONE)
//	{
//		return UPDATE_CONTINUE;
//	}
//
//	float fadeRatio = (float)frameCount / (float)maxFadeFrames;
//
//	// Render the black square with alpha on the screen
//	SDL_SetRenderDrawColor(App->renderer->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
//	SDL_RenderFillRect(App->renderer->renderer, &screenRect);
//
//
//	return UPDATE_CONTINUE;
//}
//
//bool FadeScreen::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
//{
//	// If we are already in a fade process, ignore this call
//	if (currentStep == Fade_Step::NONE)
//	{
//		currentStep = Fade_Step::TO_BLACK;
//		frameCount = 0;
//		maxFadeFrames = frames;
//
//		this->moduleToDisable = moduleToDisable;
//		this->moduleToEnable = moduleToEnable;
//
//		return true;
//	}
//	else
//	{
//		currentStep = Fade_Step::FROM_BLACK;
//		frameCount = frames;
//		maxFadeFrames = frames;
//
//		return true;
//	}
//}
