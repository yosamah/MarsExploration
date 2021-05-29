#pragma once
#include "Event.h"
class Formulation :
    public Event
{
    char MissionType;
    int TargetLocation;
    int MissionDuration;
    int Significance;
public:

    /* Constructor */             //al wa2t al hy5do hnak                //Initialiser list 3shan al event
    Formulation(char MissionType,int TargetLocation,int MissionDuration,int Significance, int MissionID, int EventDay);
    void virtual Execute(HashTable<Mission>* Mountainous, PriQ<Mission>* Emergency, Queue<int>* MountainousSort, Queue<Mission>* Polar);
    int getED();//get event date

};