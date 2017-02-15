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
	//filename = "D://APXTEST/Original/2017-01-26_132835_apx.txt";
	filename = "D://APXTEST/Original/2017-01-26_132835_apx_PASHR_Error.txt";
	ApxModifier* a = new ApxModifier(filename);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();

	//��갪 ����
	//X = a->rowInterpolated->X;
	//Y = a->rowInterpolated->Y;
	//Z = a->rowInterpolated->Z;
	//heading = a->rowInterpolated->heading;
	//roll = a->rowInterpolated->roll;
	//pitch = a->rowInterpolated->pitch;

	//�� ���� ����
	char newFilename[200] = "D://APXTEST/2017-01-26_132835_apx_GPGGA_Error.txt.txt";
	//strcat_s(newFilename, filename);
	a->writeNewFile(newFilename);

	return 0;
}