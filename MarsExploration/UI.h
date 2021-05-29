#pragma once
#include <fstream>
#include <iostream>
using namespace std;
class MarsStation;
class Event;


class UI
{
	MarsStation *pMars;

public:
	UI(MarsStation* Mars);

	void Read(ifstream& file);  //file.close() //file.eof()
	void Write(ofstream& file);

};

