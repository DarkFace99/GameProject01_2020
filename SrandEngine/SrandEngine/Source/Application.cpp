#include <iostream>

#include "Engine.h"

int main(int argc, char** argv) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine& engine = Engine::get();

	engine.Init();

	while (engine.IsRunning()) {
		engine.Event();
		engine.Update();
		// need to impliment time later
		engine.FixedUpdate();
		engine.Draw();
	}

	engine.Clean();

	return 0;
}