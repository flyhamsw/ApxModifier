#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

void runApxModifier(char* inputFilename, char* outputFilename)
{
	ApxModifier* a = new ApxModifier(inputFilename, true, true);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

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
	runApxModifier_false("D://오픈소스/atan-INS 비교/2017-02-13_atan/original/2017-02-13_151217_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_atan/2017-02-13_151217.txt");
	runApxModifier_false("D://오픈소스/atan-INS 비교/2017-02-13_atan/original/2017-02-13_151221_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_atan/2017-02-13_151221.txt");
	runApxModifier_false("D://오픈소스/atan-INS 비교/2017-02-13_atan/original/2017-02-13_151225_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_atan/2017-02-13_151225.txt");
	runApxModifier_false("D://오픈소스/atan-INS 비교/2017-02-13_atan/original/2017-02-13_151229_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_atan/2017-02-13_151229.txt");
	runApxModifier_false("D://오픈소스/atan-INS 비교/2017-02-13_atan/original/2017-02-13_151233_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_atan/2017-02-13_151233.txt");

	runApxModifier("D://오픈소스/atan-INS 비교/2017-02-13_INS/original/2017-02-13_151217_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_INS/2017-02-13_151217.txt");
	runApxModifier("D://오픈소스/atan-INS 비교/2017-02-13_INS/original/2017-02-13_151221_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_INS/2017-02-13_151221.txt");
	runApxModifier("D://오픈소스/atan-INS 비교/2017-02-13_INS/original/2017-02-13_151225_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_INS/2017-02-13_151225.txt");
	runApxModifier("D://오픈소스/atan-INS 비교/2017-02-13_INS/original/2017-02-13_151229_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_INS/2017-02-13_151229.txt");
	runApxModifier("D://오픈소스/atan-INS 비교/2017-02-13_INS/original/2017-02-13_151233_apx.txt", "D://오픈소스/atan-INS 비교/2017-02-13_INS/2017-02-13_151233.txt");

	return 0;
}