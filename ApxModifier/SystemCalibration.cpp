#include <Windows.h>
#include <stdio.h>
#include <Windows.h>
#include <WinInet.h>
#include <string>

#include "SystemCalibration.h"
//#include <stdio.h>
//#include <Windows.h>
//#include <WinInet.h>
#include <opencv2\highgui.hpp>

using namespace cv;

Mat A2R_RPY(double* roll, double* pitch, double* yaw)
{
	Mat R_rpy;
	Mat Rx, Ry, Rz;
	//double roll, pitch, yaw;
	double x;
	double cos_x, sin_x;

	Rx = Mat(3, 3, CV_64FC1);
	Ry = Mat(3, 3, CV_64FC1);
	Rz = Mat(3, 3, CV_64FC1);

	x = *pitch;
	cos_x = cos(x);
	sin_x = sin(x);

	double* rotX = (double*)Rx.data;
	rotX[0 * Rx.cols + 0] = 1.0;
	rotX[0 * Rx.cols + 1] = 0.0;
	rotX[0 * Rx.cols + 2] = 0.0;
	rotX[1 * Rx.cols + 0] = 0.0;
	rotX[1 * Rx.cols + 1] = cos_x;
	rotX[1 * Rx.cols + 2] = -sin_x;
	rotX[2 * Rx.cols + 0] = 0.0;
	rotX[2 * Rx.cols + 1] = sin_x;
	rotX[2 * Rx.cols + 2] = cos_x;

	x = *roll;
	cos_x = cos(x);
	sin_x = sin(x);

	double* rotY = (double*)Ry.data;
	rotY[0 * Ry.cols + 0] = cos_x;
	rotY[0 * Ry.cols + 1] = 0.0;
	rotY[0 * Ry.cols + 2] = sin_x;
	rotY[1 * Ry.cols + 0] = 0.0;
	rotY[1 * Ry.cols + 1] = 1.0;
	rotY[1 * Ry.cols + 2] = 0.0;
	rotY[2 * Ry.cols + 0] = -sin_x;
	rotY[2 * Ry.cols + 1] = 0.0;
	rotY[2 * Ry.cols + 2] = cos_x;

	x = -*yaw;
	cos_x = cos(x);
	sin_x = sin(x);

	double* rotZ = (double*)Rz.data;
	rotZ[0 * Rz.cols + 0] = cos_x;
	rotZ[0 * Rz.cols + 1] = -sin_x;
	rotZ[0 * Rz.cols + 2] = 0.0;
	rotZ[1 * Rz.cols + 0] = sin_x;
	rotZ[1 * Rz.cols + 1] = cos_x;
	rotZ[1 * Rz.cols + 2] = 0.0;
	rotZ[2 * Rz.cols + 0] = 0.0;
	rotZ[2 * Rz.cols + 1] = 0.0;
	rotZ[2 * Rz.cols + 2] = 1.0;

	R_rpy = Rz * Rx * Ry;

	return R_rpy;
}

Mat R2A_OPK(Mat R_opk, double* roll_rad, double* pitch_rad, double* heading_rad)
{
	Mat R_opk2;
	R_opk2 = Mat(3, 3, CV_64FC1);
	R_opk2 = R_opk;
	double* R_opk_data = (double*)R_opk.data;
	double r1, r2, r3, r4, r5, r6, r7, r8, r9;
	r1 = R_opk_data[0 * R_opk2.cols + 0];
	r2 = R_opk_data[0 * R_opk2.cols + 1];
	r3 = R_opk_data[0 * R_opk2.cols + 2];
	r4 = R_opk_data[1 * R_opk2.cols + 0];
	r5 = R_opk_data[1 * R_opk2.cols + 1];
	r6 = R_opk_data[1 * R_opk2.cols + 2];
	r7 = R_opk_data[2 * R_opk2.cols + 0];
	r8 = R_opk_data[2 * R_opk2.cols + 1];
	r9 = R_opk_data[2 * R_opk2.cols + 2];

	double s_ph, c_ph1, c_ph2, temp;
	s_ph = R_opk_data[0 * R_opk2.cols + 2];
	temp = (1 + s_ph)*(1 - s_ph);
	c_ph1 = sqrt(temp);
	c_ph2 = -sqrt(temp);

	double om, ph, kp;
	om = atan2(-r6, r9);
	kp = atan2(-r2, r1);
	ph = atan2(s_ph, c_ph1);

	*heading_rad = kp;
	*roll_rad = om;
	*pitch_rad = ph;

	Mat OPK;
	OPK = Mat(1, 3, CV_64FC1);
	double* M_OPK = (double*)OPK.data;
	M_OPK[0 * OPK.cols + 0] = om;
	M_OPK[0 * OPK.cols + 1] = ph;
	M_OPK[0 * OPK.cols + 2] = kp;

	return OPK;
}

void SystemCalibration(double* heading_rad, double* roll_rad, double* pitch_rad)
{
	Mat R_rpy;	//R matrix using Roll, Pitch, Yaw

	Mat R_opk;	//R matrix using Omega, Phi, Kappa
	R_rpy = A2R_RPY(roll_rad, pitch_rad, heading_rad);

	Mat R_CB;
	R_CB = Mat(3, 3, CV_64FC1);
	double* rotR_CB = (double*)R_CB.data;
	rotR_CB[0 * R_CB.cols + 0] = -0.0146;
	rotR_CB[0 * R_CB.cols + 1] = -0.9999;
	rotR_CB[0 * R_CB.cols + 2] = -0.0046;
	rotR_CB[1 * R_CB.cols + 0] = 0.9999;
	rotR_CB[1 * R_CB.cols + 1] = -0.0146;
	rotR_CB[1 * R_CB.cols + 2] = 0.0018;
	rotR_CB[2 * R_CB.cols + 0] = -0.0018;
	rotR_CB[2 * R_CB.cols + 1] = -0.0045;
	rotR_CB[2 * R_CB.cols + 2] = 1.0000;	

	R_opk = R_rpy * R_CB;

	Mat M_opk;
	M_opk = R2A_OPK(R_opk, roll_rad, pitch_rad, heading_rad);
}
