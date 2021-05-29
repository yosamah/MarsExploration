#include "Event.h"
Event::Event(int ED, int MID)
{
	EventDay = ED;
	MissionID = MID;

}
int Event::getED()
{
	return EventDay;
}