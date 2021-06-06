#include "Rover.h"


Rover::Rover(char roverType, int checkUpDuration, int speed, int N)
{
	RoverType = roverType;
	CheckUpDuration = checkUpDuration;
	Speed = speed;
	MissionCount = 0;
	InMaintainance = false;
	checkUpEnter = 0;
	NumBeforeCheck = N;
}



void Rover::setRoverType(char RT)
{
	RoverType = RT;
}
char Rover::getRoverType()
{
	return RoverType;
}

void Rover::setCheckUpDuration(int CUD)
{
	CheckUpDuration = CUD;
}
int Rover::getCheckUpDuration()
{
	return CheckUpDuration;
}

void Rover::setSpeed(int s)
{
	Speed = s;
}
int Rover::getSpeed()
{
	return Speed;
}
void Rover::increamentMissionCount()
{
	MissionCount++;
}
int Rover::getMissionCount(int d)
{
	if (MissionCount == NumBeforeCheck)
	{
		MissionCount = 0;
		checkUpEnter = d;
		return -1;
	}	
	if (InMaintainance)
	{
		resetMaintain();
		return -1;
	}
		
	return MissionCount;
}
int Rover::getMissionCountMain()
{
	return MissionCount;
}
void Rover::setMaintain()
{
	if (!InMaintainance)
	{
		if (Speed != 1)
			Speed = Speed / 2;
		InMaintainance = true;
	}
	
}
void Rover::resetMaintain()
{
	if (InMaintainance)
	{
		Speed = Speed * 2;
		MissionCount = 0;
		InMaintainance = false;
	}
}
bool Rover::moveToAvail(int day)
{
	return (day - checkUpEnter == CheckUpDuration);
}
int Rover::getID()
{
	return ID;
}

void Rover::setID(int id)
{
	ID = id;
}

void Rover::setCheckUpEnter(int d)
{
	checkUpEnter = d;
}


bool Rover::getInMain()
{
	return InMaintainance;
}