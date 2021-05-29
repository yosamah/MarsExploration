#pragma once
#include <fstream>
#include <iostream>
#include "MarsStation.h"
#include "Event.h"
#include "Formulation.h"
#include "Cancellation.h"
#include "Formulation.h"

using namespace std;

class UI
{
	MarsStation* pMars;

public:
	UI(MarsStation* Mars);

	void Read(ifstream& file);  //file.close() //file.eof()
	void Write(ofstream& file);

};

