#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <opencv2\highgui.hpp>

void runApxModifier(char* inputFilename, char* outputFilename)
{
	ApxModifier* a = new ApxModifier(inputFilename, true, true);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

	cout << a->rowInterpolated->heading << endl;

	//새 파일 생성
	a->writeNewFile(outputFilename);
}

void runApxModifier_false(char* inputFilename, char* outputFilename)
{
	ApxModifier* a = new ApxModifier(inputFilename, true, false);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

	//새 파일 생성
	a->writeNewFile(outputFilename);
}

int main()
{
	/*
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151501_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151501.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151505_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151505.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151509_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151509.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151513_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151513.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151517_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151517.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151521_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151521.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151525_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151525.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151529_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151529.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151533_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151533.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151537_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151537.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151541_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151541.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151545_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151545.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151549_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151549.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151553_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151553.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151557_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151557.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151601_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151601.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151605_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151605.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151609_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151609.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151613_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151613.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151617_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151617.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151621_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151621.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151625_apx.txt", "D://오픈소스/SystemCalibration 비교/Original_no_calib/2017-02-13_151625.txt");
	*/

	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151217_apx.txt", "D://오픈소스/SystemCalibration 비교/2017-02-13_151217.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151221_apx.txt", "D://오픈소스/SystemCalibration 비교/2017-02-13_151221.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151225_apx.txt", "D://오픈소스/SystemCalibration 비교/2017-02-13_151225.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151229_apx.txt", "D://오픈소스/SystemCalibration 비교/2017-02-13_151229.txt");
	runApxModifier("D://오픈소스/SystemCalibration 비교/original/2017-02-13_151233_apx.txt", "D://오픈소스/SystemCalibration 비교/2017-02-13_151233.txt");

	return 0;
}