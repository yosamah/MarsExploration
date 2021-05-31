#pragma once
#include <iostream>

class Rover
{
private:
	char RoverType;
	int CheckUpDuration;
	int Speed;
	int MissionCount;
	bool InMaintainance;
	int checkUpEnter;
	int NumBeforeCheck;
	//bool available;

public:
	/* Constructor */
	Rover(char roverType,int checkUpDuration, int speed, int NumBeforeCheck);

	void setRoverType(char);
	char getRoverType();

	void setCheckUpDuration(int);
	int getCheckUpDuration();

	void setSpeed(int);
	int getSpeed();

	void increamentMissionCount();
	int getMissionCount(int day);

	void setMaintain();
	void resetMaintain();

	bool moveToAvail(int day);
};