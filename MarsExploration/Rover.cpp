#include "Rover.h"


Rover::Rover(char roverType, int checkUpDuration, int speed)
{
	RoverType = roverType;
	CheckUpDuration = checkUpDuration;
	Speed = speed;
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