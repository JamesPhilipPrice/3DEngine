#define SDL_MAIN_HANDLED
#include "GameEngine.h"

using namespace GE;

int main() {
	GameEngine ge;

	if (!ge.init()) {
		DisplayInfoMessage("Couldn't start SDL! Check console output for details");
		return -1;
	}

	while (ge.keep_running()) {
		ge.Update();
		ge.Draw();
	}

	ge.Shutdown();

	return 0;
}