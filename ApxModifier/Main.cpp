#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{
	char* filename; //���� ���ϸ�

	//���� ���� �ε�
	filename = "D://APXTEST/Original/2017-02-07_144833_apx.txt";
	ApxModifier* a = new ApxModifier(filename);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();

	//�� ���� ����
	char newFilename[200] = "D://APXTEST/test.txt";
	a->writeNewFile(newFilename);

	return 0;
}