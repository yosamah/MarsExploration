#pragma once
#include <iostream>

class Rover
{
private:

	int ID;
	char RoverType;
	int CheckUpDuration;
	int Speed;
	int MissionCount;
	bool InMaintainance;
	int checkUpEnter;
	int NumBeforeCheck;

public:
	/* Constructor */
	Rover(char roverType,int checkUpDuration, int speed, int NumBeforeCheck);

	/*Setters and getters for the all rovers' info*/
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
	
	int getID();
	void setID(int);

	int getMissionCountMain();
	void setCheckUpEnter(int d);

	bool getInMain();
};