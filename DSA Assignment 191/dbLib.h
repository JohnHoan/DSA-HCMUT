/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct TCity {
    // The structure to store city information
	int id;
	string name;
};

struct TLine {
    // The structure to store line information
	int id;
	int city_id;
	string name;
};

struct TTrack {
    // The structure to store track information
	int track_id;
	int city_id;
	string geometry;
};

struct Station {
	int id;
	string name;
	string geometry;
	string buildstart;
	string opening;
	string closure;
	int city_id;
};

struct Station_line {
	int id;
	int station_id;
	int line_id;
	int city_id;
};

struct Track_line {
	int id;
	int selection_id;
	int line_id;
	int city_id;
};

class TDataset {
    // This class can be a container that help you manage your tables
public:
	L1List<TCity> theCity;
	L1List<TLine> theLine;
	L1List<TTrack> theTrack;
	L1List<Station> theStation;
	L1List<Station_line> theStation_line;
	L1List<Track_line> theTrack_line;
	L1List<TLine> Systems;

};

// Please add more or modify as needed

void LoadData(void* &);
void ReleaseData(void* &);

void ReadDatafromfileCities(L1List<TCity>& theCity);
void ReadDatafromfileLines(L1List<TLine>& theLine);
void ReadDatafromfileStationLines(L1List<Station_line>& theStation_line);
void ReadDatafromfileStation(L1List<Station>& theStation);
void ReadDatafromfileSystems(L1List<TLine>& theSystem);
void ReadDatafromfileTrack(L1List<TTrack>& theTrack);
void ReadDatafromfileTrack_line(L1List<Track_line>& theTrack_line);

#endif //DSA191_A1_DBLIB_H
