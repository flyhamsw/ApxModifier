#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{
	char* filename; //���� ���ϸ�
	//���� ���� �ε�
	filename = "D://data_wgs84/original/2017-02-13_151557_apx.txt";
	ApxModifier* a = new ApxModifier(filename, false);
	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();
	//�� ���� ����
	char newFilename[200] = "D://data_wgs84/2017-02-13_151557.txt";
	a->writeNewFile(newFilename);

	return 0;
}