//
// Created by School on 2025/3/11.
//
#include "game_logic.h"

struct GameData {
	int frameCounter = 0;
	float timeCounter = 0;
};
static GameData data;

bool Madline::EngineDebug::initGameplay() {
	data = {};
	printf("Madline initialised in debug mode\n");
	return true;
}

bool Madline::EngineDebug::process(float delta, Window& gameWindow) {
	data.frameCounter += 1;
	data.timeCounter += delta;
	if (data.timeCounter >= 1.0) {
		data.timeCounter -= 1.0;
		std::printf("FPS: %i ~ Debug mode\n", data.frameCounter);
		data.frameCounter = 0;
	}
	
	return true;
}

void Madline::EngineDebug::onCloseGame() {
	printf("Madline closed in debug mode");
}