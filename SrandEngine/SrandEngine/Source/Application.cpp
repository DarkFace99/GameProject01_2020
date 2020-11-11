#include <iostream>

#include "Engine.h"

int main(int argc, char** argv) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine& engine = Engine::get();

	engine.Init();

	while (engine.IsRunning()) {
		engine.Event();
		engine.Update();
		engine.FixedUpdate();	// need to impliment time later
		engine.Draw();
	}

	engine.Clean();

	// Clear Singleton Instance
	delete &AssetManager::get();
	delete& Engine::get();

	return 0;
}