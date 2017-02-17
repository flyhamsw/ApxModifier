#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{
	char* filename; //기존 파일명

	//기존 파일 로드
	filename = "D://APXTEST/Original/2017-02-07_144833_apx.txt";
	ApxModifier* a = new ApxModifier(filename);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

	//새 파일 생성
	char newFilename[200] = "D://APXTEST/test.txt";
	a->writeNewFile(newFilename);

	return 0;
}