#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{
	char* filename; //���� ���ϸ�

	//���� ���� �ε�
	filename = "D://APXTEST/Original/2017-02-07_145101_apx.txt";
	ApxModifier* a = new ApxModifier(filename, true);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();

	//�� ���� ����
	char newFilename[200] = "D://APXTEST/test.txt";
	a->writeNewFile(newFilename);
	//>printLocationData(newFilename);

	return 0;
}