#include <iostream>

#include "Engine.h"

int main(int argc, char** argv) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine& engine = Engine::get();
	//TimeStep& timeStep = TimeStep::get();

	engine.Init();

	float lastFrameTime = 0;

	while (engine.IsRunning()) {
		/*float time = (float)glfwGetTime();
		timeStep = time - lastFrameTime;
		lastFrameTime = time;*/

		engine.Event();
		engine.Update();

		//engine.FixedUpdate(timeStep);	// need to impliment time later

		engine.Draw();
	}

	engine.Clean();

	// Clear Singleton Instance
	delete &AssetManager::get();
	delete &Engine::get();
	delete& WindowProperties::get();
	delete Shader::get();
	delete &TimeStep::get();
	return 0;
}