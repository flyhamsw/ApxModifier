#include "stdafx.h"
#include "ApxModifier.h"
#include <string.h>
#include <iostream>
#include <math.h>

void runApxModifier(char* inputFilename, char* outputFilename)
{
	ApxModifier* a = new ApxModifier(inputFilename, true, true);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();

	//�� ���� ����
	a->writeNewFile(outputFilename);
}

void runApxModifier_false(char* inputFilename, char* outputFilename)
{
	ApxModifier* a = new ApxModifier(inputFilename, true, false);

	//�̺�Ʈ ��, �� ������ �˻� �� ���
	a->interpolateData();

	//�� ���� ����
	a->writeNewFile(outputFilename);
}

int main()
{
	runApxModifier_false("D://���¼ҽ�/atan-INS ��/2017-02-13_atan/original/2017-02-13_151217_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_atan/2017-02-13_151217.txt");
	runApxModifier_false("D://���¼ҽ�/atan-INS ��/2017-02-13_atan/original/2017-02-13_151221_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_atan/2017-02-13_151221.txt");
	runApxModifier_false("D://���¼ҽ�/atan-INS ��/2017-02-13_atan/original/2017-02-13_151225_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_atan/2017-02-13_151225.txt");
	runApxModifier_false("D://���¼ҽ�/atan-INS ��/2017-02-13_atan/original/2017-02-13_151229_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_atan/2017-02-13_151229.txt");
	runApxModifier_false("D://���¼ҽ�/atan-INS ��/2017-02-13_atan/original/2017-02-13_151233_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_atan/2017-02-13_151233.txt");

	runApxModifier("D://���¼ҽ�/atan-INS ��/2017-02-13_INS/original/2017-02-13_151217_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_INS/2017-02-13_151217.txt");
	runApxModifier("D://���¼ҽ�/atan-INS ��/2017-02-13_INS/original/2017-02-13_151221_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_INS/2017-02-13_151221.txt");
	runApxModifier("D://���¼ҽ�/atan-INS ��/2017-02-13_INS/original/2017-02-13_151225_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_INS/2017-02-13_151225.txt");
	runApxModifier("D://���¼ҽ�/atan-INS ��/2017-02-13_INS/original/2017-02-13_151229_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_INS/2017-02-13_151229.txt");
	runApxModifier("D://���¼ҽ�/atan-INS ��/2017-02-13_INS/original/2017-02-13_151233_apx.txt", "D://���¼ҽ�/atan-INS ��/2017-02-13_INS/2017-02-13_151233.txt");

	return 0;
}