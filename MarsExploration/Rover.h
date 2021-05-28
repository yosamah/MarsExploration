#pragma once
#include <iostream>

class Rover
{
private:
	char RoverType;
	int CheckUpDuration;
	int Speed;
	//bool available;

public:
	/* Constructor */
	Rover(char roverType,int checkUpDuration, int speed);

	void setRoverType(char);
	char getRoverType();

	void setCheckUpDuration(int);
	int getCheckUpDuration();

	void setSpeed(int);
	int getSpeed();


};