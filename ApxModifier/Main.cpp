#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{
	char* filename; //���� ���ϸ�
	//char newFilename[200]; //�� ������ �����
	//������ ��ġ, �ڼ�
	double X;
	double Y;
	double Z;
	double heading;
	double roll;
	double pitch;

	//���� ���� �ε�
	filename = "D://APXTEST/Original/2017-02-13_151249_apx.txt";
	ApxModifier* a = new ApxModifier(filename);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	//a->interpolateData();

	//�� ���� ����
	//char newFilename[200] = "D://APXTEST/2017-01-26_132835_apx_GPGGA_Error.txt.txt";
	//strcat_s(newFilename, filename);
	//a->writeNewFile(newFilename);

	a->printLocationData("D://APXTEST/2017-02-13_151249_apx.txt");

	return 0;
}