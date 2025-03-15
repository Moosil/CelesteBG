//
// Created by School on 2025/3/10.
//

#include "windows/input.h"

void Game::resetInput(Game::Input* input) {
	input->lmb = {};
	input->rmb = {};
	
	std::fill(input->keyBoard.begin(), input->keyBoard.end(), Button());
}

void Game::processInputAfter(Game::Input* input) {
	for (int i = 0; i < Button::BUTTONS_COUNT; i++) {
		input->keyBoard[i].pressed = false;
		input->keyBoard[i].released = false;
		input->keyBoard[i].triggered = false;
		input->keyBoard[i].altPressed = false;
	}
	
	input->lmb.pressed = false;
	input->lmb.triggered = false;
	input->lmb.released = false;
	input->lmb.altPressed = false;
	input->rmb.pressed = false;
	input->rmb.triggered = false;
	input->rmb.released = false;
	input->lmb.altPressed = false;
}

void Game::processEventButton(Game::Button &b, bool newState) {
	if (newState) {
		if (!b.held) {
			b.pressed = true;
			b.triggered = true;
			b.held = true;
		}
		b.triggered = true;
	} else {
		b.pressed = false;
		b.triggered = false;
		b.held = false;
		b.released = true;
	}
}