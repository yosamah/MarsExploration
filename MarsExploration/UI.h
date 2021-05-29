#pragma once
#include <fstream>
#include <iostream>


class MarsStation;
class Event;


using namespace std;

class UI
{
	MarsStation* pMars;

public:
	UI(MarsStation* Mars);

	void Read(ifstream& file);  //file.close() //file.eof()
	void Write(ofstream& file);

};

