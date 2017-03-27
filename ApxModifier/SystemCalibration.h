#pragma once
#include <string>

#include <stdio.h>
#include <Windows.h>
#include <opencv2\highgui.hpp>

using namespace cv;

Mat A2R_RPY(double* roll, double* pitch, double* yaw);
Mat R2A_OPK(Mat R_opk, double* roll_rad, double* pitch_rad, double* heading_rad);
void SystemCalibration(double* heading_rad, double* roll_rad, double* pitch_rad);