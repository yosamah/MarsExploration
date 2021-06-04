#pragma once
#include <fstream>
#include <iostream>
#include "PriQ.h"
#include "Queue.h"
#include "HashTable.h"
#include "Mission.h"
using namespace std;
class MarsStation;
class Event;


class UI
{
	MarsStation *pMars;
	

public:
	UI(MarsStation* Mars);

	void Read(ifstream& file, Queue<Event>&);  //file.close() //file.eof()
	void Write(ofstream& file);
	void InteractiveMode(HashTable<Mission> Mountainous, PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar, int* Arr);
	void SilentMode();
	void StepByStepMode();
};

