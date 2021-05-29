#pragma once
#include "Event.h"
class Formulation :
    public Event
{
    char MissionType;
    int TargetLocation;
    int MissionDuration;
    int Significance;
    //char missionType;
public:
    /* Constructor */                                                    //Initialiser list 3shan al event
    Formulation(char MT,int TL,int MD,int Signif, int MID, int ED);//asa,y el parameters
    // momken 
    void Execute(HashTable<Mission*>* Mountainous, PriQ<Mission*>* Emergency, Queue<int>* MountainousSort, Queue<Mission*>* Polar);

};