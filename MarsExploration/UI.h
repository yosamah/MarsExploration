#pragma once
#include <fstream>
#include <iostream>
#include "Queue.h"
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

};

