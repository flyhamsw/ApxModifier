#include "stdafx.h"
#include "ApxModifier.h"
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>

void runApxModifier(char* inputFileName, char* outputFileName, queue<RowInterpolated*>* qAllRows, queue<string>* qOutputFileNames)
{
	ApxModifier* a = new ApxModifier(inputFileName, false);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

	//새 파일 생성
	qAllRows->push(a->writeNewFile(outputFileName));

	int dotIdx;
	int slIdx;

	for (int i = strlen(outputFileName); i >= 0; i--)
	{
		if (outputFileName[i] == '.')
		{
			dotIdx = i;
		}
		else if (outputFileName[i] == '/')
		{
			slIdx = i;
			break;
		}
	}

	string jpgName = outputFileName;
	jpgName = jpgName.substr(slIdx + 1, dotIdx - slIdx - 1); //.t

	qOutputFileNames->push(jpgName);
}

int main()
{
	queue<RowInterpolated*> qAllRows;
	queue<string> qOutputFileNames;

	runApxModifier("D://data/original/2017-01-26_132831_apx.txt", "D://data/2017-01-26_132831.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132835_apx.txt", "D://data/2017-01-26_132835.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132839_apx.txt", "D://data/2017-01-26_132839.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132847_apx.txt", "D://data/2017-01-26_132847.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132851_apx.txt", "D://data/2017-01-26_132851.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132855_apx.txt", "D://data/2017-01-26_132855.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132859_apx.txt", "D://data/2017-01-26_132859.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132903_apx.txt", "D://data/2017-01-26_132903.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132907_apx.txt", "D://data/2017-01-26_132907.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132911_apx.txt", "D://data/2017-01-26_132911.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132915_apx.txt", "D://data/2017-01-26_132915.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132923_apx.txt", "D://data/2017-01-26_132923.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132927_apx.txt", "D://data/2017-01-26_132927.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132931_apx.txt", "D://data/2017-01-26_132931.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132935_apx.txt", "D://data/2017-01-26_132935.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132939_apx.txt", "D://data/2017-01-26_132939.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132947_apx.txt", "D://data/2017-01-26_132947.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132951_apx.txt", "D://data/2017-01-26_132951.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132955_apx.txt", "D://data/2017-01-26_132955.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_132959_apx.txt", "D://data/2017-01-26_132959.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_133107_apx.txt", "D://data/2017-01-26_133107.txt", &qAllRows, &qOutputFileNames);
	runApxModifier("D://data/original/2017-01-26_133111_apx.txt", "D://data/2017-01-26_133111.txt", &qAllRows, &qOutputFileNames);

	//Write entire data in one file
	int qSize = qAllRows.size();

	ofstream fnew;

	fnew.open("D://data/result.txt");
	fnew.precision(8);
	fnew.setf(ios::fixed);
	fnew.setf(ios::showpoint);

	if (fnew.is_open())
	{
		for (int i = 0; i < qSize; i++)
		{
			fnew << qOutputFileNames.front() << ".jpg" << '\t' << qAllRows.front()->X << '\t' << qAllRows.front()->Y << '\t' << qAllRows.front()->Z << '\t' << qAllRows.front()->roll << '\t' << qAllRows.front()->pitch << '\t' << qAllRows.front()->heading << endl;
			qAllRows.pop();
			qOutputFileNames.pop();
		}		
	}

	fnew.close();

	return 0;
}