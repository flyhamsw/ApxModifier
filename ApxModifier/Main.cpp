#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{

	char* filename; //���� ���ϸ�

	//���� ���� �ε�
	filename = "D://test/Original/2017-02-13_151301_apx.txt";
	ApxModifier* a = new ApxModifier(filename, true);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();

	//�� ���� ����
	char newFilename[200] = "D://test/2017-02-13_151557.txt";
	a->writeNewFile(newFilename);
	
	return 0;
}