#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{

	char* filename; //기존 파일명

	//기존 파일 로드
	filename = "D://test/Original/2017-02-13_151301_apx.txt";
	ApxModifier* a = new ApxModifier(filename, true);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

	//새 파일 생성
	char newFilename[200] = "D://test/2017-02-13_151557.txt";
	a->writeNewFile(newFilename);
	
	return 0;
}