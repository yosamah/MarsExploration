#pragma once
#include <iostream>
#include "Rover.h"

class Mission
{
private:
	Rover* rover;
	int ID;
	int TargetLocation;
	int MissionDuration;
	int Significance;

public:
	/* Constructor */
	Mission(int , int, int, int ,Rover* r = NULL);

};

