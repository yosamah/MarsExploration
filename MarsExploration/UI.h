#pragma once
#include <fstream>
#include <iostream>

class UI
{
private:
	int x;

public:

		void Read(ifstream& file);  //file.close() //file.eof()
		void Write(ofstream& file);
		void setAv();
};

