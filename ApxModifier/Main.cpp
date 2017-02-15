#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{
	char* filename; //기존 파일명
	//char newFilename[200]; //새 파일의 상대경로
	//내삽합 위치, 자세
	double X;
	double Y;
	double Z;
	double heading;
	double roll;
	double pitch;

	//기존 파일 로드
	//filename = "D://APXTEST/Original/2017-01-26_132835_apx.txt";
	filename = "D://APXTEST/Original/2017-01-26_132835_apx_PASHR_Error.txt";
	ApxModifier* a = new ApxModifier(filename);

	//이벤트 전, 후 데이터 검색 및 계산
	a->interpolateData();

	//계산값 저장
	//X = a->rowInterpolated->X;
	//Y = a->rowInterpolated->Y;
	//Z = a->rowInterpolated->Z;
	//heading = a->rowInterpolated->heading;
	//roll = a->rowInterpolated->roll;
	//pitch = a->rowInterpolated->pitch;

	//새 파일 생성
	char newFilename[200] = "D://APXTEST/2017-01-26_132835_apx_GPGGA_Error.txt.txt";
	//strcat_s(newFilename, filename);
	a->writeNewFile(newFilename);

	return 0;
}