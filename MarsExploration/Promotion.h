#pragma once
#include "Event.h"
class Promotion :
    public Event
{

public:
    /* Constructor */  //Initialiser list 3shan al event
    Promotion( int MissionID, int EventDay);

    void Execute(HashTable<Mission*>* Mountainous, PriQ<Mission*>* Emergency);
};

