#include <Windows.h>

#include <iostream>
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>
#include <crtdbg.h>

#include "Engine.h"

const float dt = 0.016f;

int main(int argc, char** argv) {

	HANDLE mutex = CreateMutex(NULL, TRUE, L"BENNY: Everyone is Happy");
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{
		MessageBox(NULL, L"Multiple Instances of Application", NULL, MB_ICONERROR | MB_OK);
		return 0;
	}

	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapchot

	Srand::Engine& engine = Srand::Engine::get();
	glfwSetTime(0);
	Srand::TimeStep& timeStep = Srand::TimeStep::get();

	Srand::Log::Init();
	SR_SYSTEM_INFO("Initializing Log...");

	engine.Init();

	float lastFrameTime = 0;

	while (engine.IsRunning()) 
	{
		engine.Event();
		timeStep.Update();

		while (timeStep.accumulator >= dt) 
		{
			engine.Update();
			timeStep.accumulator -= dt;
		}

		engine.Draw();
	}

	engine.Clean();

	// Clear Singleton Instance
	delete& Srand::AssetManager::get();
	delete& Srand::Engine::get();
	delete& Srand::WindowProperties::get();
	delete  Srand::Shader::get();
	delete& Srand::TimeStep::get();

	_CrtMemCheckpoint(&sNew); //take a snapchot 
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
		_CrtMemDumpStatistics(&sDiff);
		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
		_CrtMemDumpAllObjectsSince(&sOld);
		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
		_CrtDumpMemoryLeaks();
	}

	return 0;
}