#include "stdafx.h"
#include "Row.h"
#include "ApxModifier.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

//Constant value for pi
const double pi = 3.141592653589793238463;

//Constant value for determination of running
//In detData method, it will be determined to use the data if the average distance between each point are bigger than DET_RUNNING
const double DET_RUNNING = 0.25;

//Constant value for determination of cornering
//In detData method, it will be determined to use the data if the average distance between each point and line connecting the first/last point are bigger than DET_CORNERING
const double DET_CORNERING = 0.2;

ApxModifier::ApxModifier(char* txt_filename, bool det_option, bool priority_option)
{
	filename = txt_filename;
	f.open(filename);
	loadData();
	matchData(det_option);
	this->priority_option = priority_option;
}

//Copyright: http://m.blog.naver.com/tacma/20108668315
void convertWGS84_to_TM(double *plon, double *plat)
{
	double lon, lat;
	lon = *plon;
	lat = *plat;
	double m_arScaleFactor = 1;
	double m_arLonCenter = 127 * pi / 180; //Projection center of Korean central belt 2010
	double m_arLatCenter = 38 * pi / 180; //Projection center of Korean central belt 2010
	double m_arFalseNorthing = 600000.0;
	double m_arFalseEasting = 200000.0;
	double x, y;
	double m_dDstInd;
	double m_arMajor = 6378137.0;
	double m_arMinor = 6356752.3142;
	double delta_lon; // Delta longitude (Given longitude - center longitude)
	double sin_phi, cos_phi; // sin and cos value
	double al, als; // temporary values
	double b, c, t, tq; // temporary values
	double con, n, ml; // cone constant, small m
	double temp = m_arMinor / m_arMajor;
	double m_ecc = 1.0 - temp * temp;
	double m_eccp = (1 / temp)*(1 / temp) - 1;
	double m_dDstE0 = 1.0 - 0.25 * m_ecc * (1.0 + m_ecc / 16.0 * (3.0 + 1.25 * m_ecc));
	double m_dDstE1 = 0.375 * m_ecc * (1.0 + 0.25 * m_ecc * (1.0 + 0.46875 * m_ecc));
	double m_dDstE2 = 0.05859375 * m_ecc * m_ecc * (1.0 + 0.75 * m_ecc);
	double m_dDstE3 = m_ecc * m_ecc * m_ecc * (35.0 / 3072.0);
	double m_dDstMl0 = m_arMajor * (m_dDstE0 * m_arLatCenter - m_dDstE1 * sin(2.0 * m_arLatCenter) + m_dDstE2 * sin(4.0 * m_arLatCenter) - m_dDstE3 * sin(6.0 * m_arLatCenter));
	m_dDstInd = 0.0;
	delta_lon = lon - m_arLonCenter;
	sin_phi = sin(lat);
	cos_phi = cos(lat);
	b = 0;
	x = 0.5 * m_arMajor * m_arScaleFactor * log((1.0 + b) / (1.0 - b));
	con = acos(cos_phi * cos(delta_lon) / sqrt(1.0 - b * b));
	al = cos_phi * delta_lon;
	als = al * al;
	c = m_eccp * cos_phi * cos_phi;
	tq = tan(lat);
	t = tq * tq;
	con = 1.0 - m_ecc * sin_phi * sin_phi;
	n = m_arMajor / sqrt(con);
	ml = m_arMajor * (m_dDstE0 * lat - m_dDstE1 * sin(2.0 * lat) + m_dDstE2 * sin(4.0 * lat) - m_dDstE3 * sin(6.0 * lat));
	x = m_arScaleFactor * n * al * (1.0 + als / 6.0 * (1.0 - t + c + als / 20.0 * (5.0 - 18.0 * t + t * t + 72.0 * c - 58.0 * m_eccp))) + m_arFalseEasting;
	y = m_arScaleFactor * (ml - m_dDstMl0 + n * tq * (als * (0.5 + als / 24.0 * (5.0 - t + 9.0 * c + 4.0 * c * c + als / 30.0 * (61.0 - 58.0 * t + t * t + 600.0 * c - 330.0 * m_eccp))))) + m_arFalseNorthing;
	*plon = x;
	*plat = y;
}

void ApxModifier::loadData()
{
	cout << "=========================================================" << endl << "Loading file (" << filename << ") ...";
	if (f.is_open())
	{
		//Split data and store to RowGPGGA, RowPASHR, RowPTNL
		char line[300];
		
		while (!f.eof())
		{
			//Get a line and store to a stringstream
			f.getline(line, sizeof(line));
			stringstream line_stream(line);

			while (!line_stream.eof())
			{
				//In a stringstream, get a comma separated word
				//Determine whether it is GPS data or INS Data
				char* lineHeader = new char[20];
				line_stream.getline(lineHeader, 20, ',');
				
				if (strcmp(lineHeader, "$GPGGA") == 0)
				{
					char* time = new char[20];
					char* lat = new char[20];
					char* latHeading = new char[20];
					char* lng = new char[20];
					char* lngHeading = new char[20];
					char* gpsQuality = new char[20];
					char* numOfSV = new char[20];
					char* HDOP = new char[20];
					char* alt = new char[20];
					char* altUnit = new char[20];
					char* heightWGS84 = new char[20];
					char* heightWGS84Unit = new char[20];
					char* DGPS = new char[20];
					char* checksum = new char[20];

					line_stream.getline(time, 20, ',');
					line_stream.getline(lat, 20, ',');
					line_stream.getline(latHeading, 20, ',');
					line_stream.getline(lng, 20, ',');
					line_stream.getline(lngHeading, 20, ',');
					line_stream.getline(gpsQuality, 20, ',');
					line_stream.getline(numOfSV, 20, ',');
					line_stream.getline(HDOP, 20, ',');
					line_stream.getline(alt, 20, ',');
					line_stream.getline(altUnit, 20, ',');
					line_stream.getline(heightWGS84, 20, ',');
					line_stream.getline(heightWGS84Unit, 20, ',');
					line_stream.getline(DGPS, 20, ',');
					line_stream.getline(checksum, 20, ',');

					RowGPGGA* row = new RowGPGGA(time, lat, latHeading, lng, lngHeading, gpsQuality, numOfSV, HDOP, alt, altUnit, heightWGS84, heightWGS84Unit, DGPS, checksum);
					
					qGPGGA.push(row);
					qGPGGA_Det.push(row);
				}
				else if (strcmp(lineHeader, "$PASHR") == 0)
				{
					char* time = new char[20];
					char* heading = new char[20];
					char* headingTrue = new char[20];
					char* roll = new char[20];
					char* pitch = new char[20];
					char* heave = new char[20];
					char* rollAccuracy = new char[20];
					char* pitchAccuracy = new char[20];
					char* headingAccuracy = new char[20];
					char* aidingStatus = new char[20];
					char* IMUStatus = new char[20];

					line_stream.getline(time, 20, ',');
					line_stream.getline(heading, 20, ',');
					line_stream.getline(headingTrue, 20, ',');
					line_stream.getline(roll, 20, ',');
					line_stream.getline(pitch, 20, ',');
					line_stream.getline(heave, 20, ',');
					line_stream.getline(rollAccuracy, 20, ',');
					line_stream.getline(pitchAccuracy, 20, ',');
					line_stream.getline(headingAccuracy, 20, ',');
					line_stream.getline(aidingStatus, 20, ',');
					line_stream.getline(IMUStatus, 20, ',');

					RowPASHR* row = new RowPASHR(time, heading, headingTrue, roll, pitch, heave, rollAccuracy, pitchAccuracy, headingAccuracy, aidingStatus, IMUStatus);
					
					qPASHR.push(row);
				}
				else if (strcmp(lineHeader, "$PTNL") == 0)
				{
					char* type = new char[20];
					char* time = new char[20];
					char* field4 = new char[20];
					char* field5 = new char[20];
					char* field6 = new char[20];
					char* field7 = new char[20];
					char* field8 = new char[20];

					line_stream.getline(type, 20, ',');
					line_stream.getline(time, 20, ',');
					line_stream.getline(field4, 20, ',');
					line_stream.getline(field5, 20, ',');
					line_stream.getline(field6, 20, ',');
					line_stream.getline(field7, 20, ',');
					line_stream.getline(field8, 20, ',');

					RowPTNL* row = new RowPTNL(type, time, field4, field5, field6, field7, field8);

					qPTNL.push(row);
				}
			}
		}
		cout << "OK" << endl;

		cout << "# of GPGGA(Location): " << qGPGGA.size() << endl
			<< "# of PASHR(Attitude): " << qPASHR.size() << endl
			<< "# of PTNL(Event Time): " << qPTNL.size() << endl << endl;
	}

}

//Convert Geodetic coordinate to Geocentric coordinate
void convertWGS84toXYZ(double* x, double* y, double* z)
{
	double a = 6378137.0; //Semi-major axis of earth (m)
	double b = 6356752.314245; //Semi-minor axis of earth (m) 
	double e_sq = (a*a - b*b) / (a*a);

	double k = 1 - e_sq * sin(*y) * sin(*y);
	double nu = a / sqrt(k);

	double X = (nu + *z)*cos(*y)*cos(*x);
	double Y = (nu + *z)*cos(*y)*sin(*x);
	double Z = ((1 - e_sq)*nu + *z)*sin(*y);

	*x = X;
	*y = Y;
	*z = Z;
}

bool ApxModifier::detData()
{
	queue<double> qDistance;
	
	queue<double> qx;
	queue<double> qy;

	double averageDist = 0;
	double averageFLDist = 0;

	int n = size(qGPGGA_Det);

	double x_first;
	double y_first;
	double x_last;
	double y_last;

	//Average distance between the points
	for (int i = 0; i < n - 1; i++)
	{
		RowGPGGA* rowA = qGPGGA_Det.front();
		qGPGGA_Det.pop();
		RowGPGGA* rowB = qGPGGA_Det.front();
		
		double x_a = atof(rowA->lng);
		double y_a = atof(rowA->lat);

		double x_b = atof(rowB->lng);
		double y_b = atof(rowB->lat);

		//Split weighted values into Degree and Minute
		double x_a_min = fmod(x_a, 100);
		double x_a_deg = ((x_a - x_a_min) / 100);

		double x_b_min = fmod(x_b, 100);
		double x_b_deg = ((x_b - x_b_min) / 100);

		double y_a_min = fmod(y_a, 100);
		double y_a_deg = ((y_a - y_a_min) / 100);

		double y_b_min = fmod(y_b, 100);
		double y_b_deg = ((y_b - y_b_min) / 100);

		double z_a = atof(rowA->alt);
		double z_b = atof(rowB->alt);

		//Convert Deg, Min values to Radian
		x_a = (x_a_deg + x_a_min / 60) * pi / 180; //Longitude of point A
		x_b = (x_b_deg + x_b_min / 60) * pi / 180; //Longitude of point B

		y_a = (y_a_deg + y_a_min / 60) * pi / 180; //Latitude of point A
		y_b = (y_b_deg + y_b_min / 60) * pi / 180; //Latitude of point B

		convertWGS84toXYZ(&x_a, &y_a, &z_a);
		convertWGS84toXYZ(&x_b, &y_b, &z_b);
	
		double distance = sqrt(pow((x_b - x_a), 2) + pow((y_b - y_a), 2) + pow((z_b - z_a), 2));

		qDistance.push(distance);

		if (i != 0)
		{
			qx.push(x_a);
			qy.push(y_a);
		}

		if (i == 0)
		{
			x_first = x_a;
			y_first = y_a;
		}
		else if (i == n - 2)
		{
			x_last = x_b;
			y_last = y_b;
		}
	}

	int n1 = size(qDistance);

	for (int i = 0; i < n1; i++)
	{
		averageDist += qDistance.front();
		//cout << qDistance.front() << endl;
		qDistance.pop();
	}

	int n2 = size(qx);

	//Average distance between points and FL line (FL line: First-Last Line; a line connecting the first point and the last point)
	for (int i = 0; i < n2; i++)
	{
		double x = qx.front();
		double y = qy.front();

		qx.pop();
		qy.pop();

		double a = (y_last - y_first) / (x_last - x_first);
		double b = -1;
		double c = y_first - a*x_first;

		double d = abs(a*x + b*y + c) / sqrt(pow(a, 2) + pow(b, 2));

		averageFLDist += d;
	}

	averageDist = averageDist / n1;
	averageFLDist = averageFLDist / n2;

	//Determination whether to use data or not
	if (averageDist > DET_RUNNING)
	{
		if (averageFLDist < DET_CORNERING)
		{
			return true;
		}
		else
		{
			cout << "UAV was cornering" << endl;
			return false;
		}
	}
	else
	{
		cout << "UAV was too slow" << endl;
		return false;
	}	
}

void ApxModifier::matchData(bool det_option)
{
	bool det = true;
	if (det_option == true)
	{
		det = detData();
	}

	if (det == true)
	{
		//Find GPS data and INS data with same time
		cout << "Matching Data...";

		while (!(qGPGGA.empty()) && !(qPASHR.empty()))
		{
			double time_GPGGA;
			double time_PASHR;
			//double time_GPHDT;

			RowGPGGA* currRowGPGGA = qGPGGA.front();
			RowPASHR* currRowPASHR = qPASHR.front();
			RowGPHDT* currRowGPHDT = NULL;

			time_GPGGA = atof(currRowGPGGA->time);
			time_PASHR = atof(currRowPASHR->time);
			//time_GPHDT = atof(currRowGPHDT->time);

			//Pop queue with lower time value
			if (time_GPGGA < time_PASHR)
			{
				qGPGGA.pop();
			}
			else if (time_GPGGA > time_PASHR)
			{
				qPASHR.pop();
			}
			//If time data of each queue are same, store them, and pop both queues
			else if (time_GPGGA == time_PASHR)
			{
				Row* matchedRow = new Row(currRowGPGGA, currRowPASHR, currRowGPHDT);
				qResult.push(matchedRow);
				qGPGGA.pop();
				qPASHR.pop();
			}
		}

		cout << "OK" << endl;
		cout << "# of Result Queue: " << qResult.size() << endl << endl;
	}
	else
	{
		cout << "Determined not to use this data" << endl;
	}

}

void ApxModifier::interpolateData()
{
	cout << "Finding adjacent data...";

	if (qPTNL.size() == 0)
	{
		cout << "No event data" << endl << endl;
	}
	else
	{
		double takenTime = atof(qPTNL.front()->time);
		double diffA;
		double diffB;

		int q_size = qResult.size();

		//Find Location/Attitude data adjacent to the event
		for (int i = 0; i < q_size - 1; i++)
		{
			rowBefore = qResult.front();
			qResult.pop();
			rowAfter = qResult.front();

			diffA = atof(rowBefore->rowGPGGA->time) - takenTime;
			diffB = atof(rowAfter->rowGPGGA->time) - takenTime;

			//if diffA is negative and diffB is positive, the photo was taken between A and B
			if (diffA * diffB < 0)
			{
				break;
			}
		}

		cout << "OK" << endl;

		if (rowBefore == nullptr || rowAfter == nullptr)
		{
			cout << "Row before/after the event is NULL" << endl;
			rowInterpolated = nullptr;
		}
		else
		{
			cout << "The photo was taken between " << rowBefore->rowGPGGA->time << " and " << rowAfter->rowGPGGA->time << endl << endl;
			cout << "Interpolation...";

			diffA = abs(diffA);
			diffB = abs(diffB);

			//Interpolate by time difference
			double weightA = 1 / diffA;
			double weightB = 1 / diffB;

			double weightedLat;
			double weightedLng;
			double weightedHeightWGS84;
			double weightedHeading;
			double weightedRoll;
			double weightedPitch;

			weightedLat = (atof(rowBefore->rowGPGGA->lat)*weightA + atof(rowAfter->rowGPGGA->lat)*weightB) / (weightA + weightB);
			weightedLng = (atof(rowBefore->rowGPGGA->lng)*weightA + atof(rowAfter->rowGPGGA->lng)*weightB) / (weightA + weightB);
			weightedHeightWGS84 = (atof(rowBefore->rowGPGGA->alt)*weightA + atof(rowAfter->rowGPGGA->alt)*weightB) / (weightA + weightB);

			//Select Attitude data by priority: 1-INS, 2-GPS Heading, 3-Arctangent
			if ((atof(rowBefore->rowPASHR->heading) == 0 || atof(rowAfter->rowPASHR->heading) == 0) || priority_option == false)
			{
				//Priority #3: Arctangent
				double beforeX = atof(rowBefore->rowGPGGA->lng);
				double beforeY = atof(rowBefore->rowGPGGA->lat);
				double afterX = atof(rowAfter->rowGPGGA->lng);
				double afterY = atof(rowAfter->rowGPGGA->lat);

				double beforeX_min = fmod(beforeX, 100);
				double beforeY_min = fmod(beforeY, 100);
				double afterX_min = fmod(afterX, 100);
				double afterY_min = fmod(afterY, 100);

				double beforeX_deg = (beforeX - beforeX_min) / 100;
				double beforeY_deg = (beforeY - beforeY_min) / 100;
				double afterX_deg = (afterX - afterX_min) / 100;
				double afterY_deg = (afterY - afterY_min) / 100;

				beforeX = (beforeX_deg + beforeX_min / 60)*pi / 180;
				beforeY = (beforeY_deg + beforeY_min / 60)*pi / 180;
				afterX = (afterX_deg + afterX_min / 60)*pi / 180;
				afterY = (afterY_deg + afterY_min / 60)*pi / 180;

				//convertWGS84_to_TM(&beforeX, &beforeY);
				//convertWGS84_to_TM(&afterX, &afterY);

				weightedHeading = atan2((afterY - beforeY), (afterX - beforeX)) * 180 / pi;
				weightedRoll = 0;
				weightedPitch = 0;
			}
			else
			{
				//Priority #1: INS
				weightedHeading = (atof(rowBefore->rowPASHR->heading)*weightA + atof(rowAfter->rowPASHR->heading)*weightB) / (weightA + weightB);
				weightedRoll = (atof(rowBefore->rowPASHR->roll)*weightA + atof(rowAfter->rowPASHR->roll)*weightB) / (weightA + weightB);
				weightedPitch = (atof(rowBefore->rowPASHR->pitch)*weightA + atof(rowAfter->rowPASHR->pitch)*weightB) / (weightA + weightB);
			}

			//Split weighted values into Degree and Minute
			double wLat_min = fmod(weightedLat, 100);
			double wLat_deg = ((weightedLat - wLat_min) / 100);

			double wLng_min = fmod(weightedLng, 100);
			double wLng_deg = ((weightedLng - wLng_min) / 100);

			//Convert Deg, Min values to Radian
			weightedLat = (wLat_deg + wLat_min / 60);
			weightedLng = (wLng_deg + wLng_min / 60);

			//convertWGS84_to_TM(&weightedLng, &weightedLat);

			//Store interpolated data
			rowInterpolated = new RowInterpolated(weightedLng, weightedLat, weightedHeightWGS84, weightedHeading, weightedRoll, weightedPitch);

			cout << "OK" << endl << endl;

			f.close();
		}
	}

}


void ApxModifier::writeNewFile(char* txt_filename)
{
	if (rowInterpolated == NULL)
	{
		cout << "Data was not interpolated" << endl;
	}
	else
	{
		//Get the name of .txt file from full directory (filename)
		filename = txt_filename;

		int dotIdx;
		int slIdx;

		for (int i = strlen(filename); i >= 0; i--)
		{
			if (filename[i] == '.')
			{
				dotIdx = i;
			}
			else if (filename[i] == '/')
			{
				slIdx = i;
				break;
			}
		}

		string jpgName = filename;
		jpgName = jpgName.substr(slIdx + 1, dotIdx - slIdx - 1); //.t

		fnew.open(filename);
		fnew.precision(15);
		fnew.setf(ios::fixed);
		fnew.setf(ios::showpoint);

		cout << "Writing a new file (" << filename << ") ...";

		if (fnew.is_open())
		{
			fnew << jpgName << ".jpg" << '\t' << rowInterpolated->X << '\t' << rowInterpolated->Y << '\t' << rowInterpolated->Z << '\t' << rowInterpolated->roll*pi/180 << '\t' << rowInterpolated->pitch*pi / 180 << '\t' << rowInterpolated->heading*pi / 180;
		}

		fnew.close();

		cout << "OK" << endl;

	}

}