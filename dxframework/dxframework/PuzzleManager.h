#pragma once

/////////////////////////////////////////////////////////////////////////////////////////
// The goal of this manager is to provide the necessary foundation for children puzzles.
// Children are prefectly capable of adding new functions and variables, but this is
//    meant to handle the basics.
// Any additions should be commented as such
/////////////////////////////////////////////////////////////////////////////////////////

// necessary includes
#include <stdio.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <windows.h>
#include <iostream>

// probably necessary includes
#include "DirectXFramework.h"
#include "SoundEffect.h"
#include "SoundLoader.h"
#include "AudioManager.h"


class PuzzleManager
{
protected:
	// some basic variables that may come in handy depending on puzzles made

	// tracks puzzles complete
	int puzzleCounter;

	// bool used if a puzzle is complete. ex: open door if true
	bool puzzleComplete;


public:
	PuzzleManager(void);
	~PuzzleManager(void);

	// initialize will allow child classes to create their puzzles. For example, a torch puzzle can be initialized
	virtual void Initialize(void);

	// update checks for completion of the puzzle. For example, if 4 of 4 torches are lit, return the bool
	virtual void Update(void);

	// if puzzles render objects
	virtual void Render(void);

	// simple method for confirmed puzzle completion
	void isPuzzleComplete(void)
	{ puzzleComplete = true; }

	// return for when a puzzle is complete
	bool puzzleIsComplete(void)
	{ return puzzleComplete = true; }


};

