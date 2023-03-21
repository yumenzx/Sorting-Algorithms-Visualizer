#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "SF_Thread.h"
#include "sortingFunctions.h"

#define VIEW_WIDTH 900
#define VIEW_HEIGHT 570

#define MAXIMUM_FRAME_LIMIT 30

struct visualizerArg {

	SortingMethod& sortingMethod;
	bool& shouldRun;
	bool& shouldShuffle;
	int& n;
	int& sortingSpeed;
	

	visualizerArg(HWND view, bool appIsOpen, SortingMethod& sortingMethod, bool& shouldRun, bool& shouldShuffle, int& n, int& sortingSpeed) : view(view), appIsOpen(appIsOpen), sortingMethod(sortingMethod), shouldRun(shouldRun), shouldShuffle(shouldShuffle), n(n), sortingSpeed(sortingSpeed)
	{}

	HWND view;
	bool appIsOpen;
};

void visualizer(visualizerArg* arg);