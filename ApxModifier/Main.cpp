#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{
	char* filename; //기존 파일명

					//기존 파일 로드
	filename = "D:/data_wgs84/original/2017-02-13_151445_apx.txt";
	ApxModifier* a = new ApxModifier(filename, false);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

	//새 파일 생성
	char newFilename[200] = "D://data_wgs84/test-tm.txt";
	a->writeNewFile(newFilename);

	return 0;
}