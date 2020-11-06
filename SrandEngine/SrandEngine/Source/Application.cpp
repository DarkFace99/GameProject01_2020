#include <iostream>

#include "Engine.h"

int main(int argc, char** argv) {
	
	Engine& engine = Engine::get();

	engine.Init();

	while (engine.IsRunning()) {
		engine.Event();
		engine.Update();
		engine.FixedUpdate();	// need to impliment time later
		engine.Draw();
	}

	engine.Clean();

	return 0;
}