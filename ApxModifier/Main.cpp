#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

int main()
{

	char* filename; //���� ���ϸ�

	//���� ���� �ε�
	filename = "D://test/Original/2017-02-13_151557_apx.txt";
	ApxModifier* a = new ApxModifier(filename, false);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();

	//�� ���� ����
	char newFilename[200] = "D://test/2017-02-13_151557.txt";
	a->writeNewFile(newFilename);
	
	
	/*
	//QGIS ����ȭ�� �ڵ�
	
	char* filename;
	filename = "D://APXTEST/Original/2017-02-07_155227_apx.txt";
	ApxModifier* a = new ApxModifier(filename, true);

	a->interpolateData();
	
	//�� ���� ����
	char newFilename[200] = "D://APXTEST/2017-02-07_155227_apx.txt";
	a->printLocationData(newFilename);
	*/

	return 0;
}