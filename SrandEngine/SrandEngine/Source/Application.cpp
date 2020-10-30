#include <iostream>

#include "Engine.h"

int main(int argc, char** argv) {
	
	Engine& engine = Engine::get();

	engine.Init();

	while (engine.IsRunning()) {
		engine.Event();
		engine.Update();
		// need to impliment time later
		engine.FixedUpdate();
		engine.Draw();
	}
	return 0;
}