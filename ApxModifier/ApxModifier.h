#pragma once

#include <fstream>
#include <queue>
#include "Row.h"

using namespace std;

class ApxModifier
{
public:
	Row* rowBefore; //GPS-INS Data before the event
	Row* rowAfter; //GPS-INS Data after the event
	RowInterpolated* rowInterpolated; //Interpolated data
	
	ApxModifier(char*);
	void interpolateData();
	void writeNewFile(char*);
	void printLocationData(char*);

private:
	ifstream f;
	ofstream fnew;

	queue<RowGPGGA*> qGPGGA; //Location Queue
	queue<RowPASHR*> qPASHR; //Attitude Queue (INS)
	queue<RowGPHDT*> qGPHDT; //Attidude Queue (GPS)
	queue<RowPTNL*> qPTNL;   //Event Queue
	queue<Row*> qResult;     //Queue for matched result (by time)

	queue<RowGPGGA*> qGPGGA_Det; //Location Queue for Determination
		
	char* filename; //Unmodified filename
	char* newFilename; //Releative directory of modified filename

	void loadData();
	void matchData();	
};