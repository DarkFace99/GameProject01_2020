#include <iostream>

#include "Engine.h"

int main(int argc, char** argv) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Srand::Engine& engine = Srand::Engine::get();
	//TimeStep& timeStep = TimeStep::get();

	engine.Init();

	float lastFrameTime = 0;

	while (engine.IsRunning()) {
		/*float time = (float)glfwGetTime();
		timeStep = time - lastFrameTime;
		lastFrameTime = time;*/

		engine.OnEvent();
		engine.Update();

		//engine.FixedUpdate(timeStep);	// need to impliment time later

		engine.Draw();
	}

	engine.Clean();

	// Clear Singleton Instance
	delete& Srand::AssetManager::get();
	delete& Srand::Engine::get();
	delete& Srand::WindowProperties::get();
	delete  Srand::Shader::get();
	delete& Srand::TimeStep::get();
	return 0;
}