/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

//right
void ReadDatafromfileCities(L1List<TCity>& theCity) {
	ifstream file;
	string str;
	TCity city;
	file.open("cities.csv");
	getline(file, str);
	while (file.good()) {
		getline(file, str, ',');
		if (str == "")break;
		city.id = stoi(str);
		getline(file, str, ',');
		city.name = str;
		getline(file, str);
		theCity.push_back(city);
	}
	file.close();
}

//right
void ReadDatafromfileLines(L1List<TLine>& theLine) {
	ifstream file;
	string str;
	TLine line;
	file.open("lines.csv");
	getline(file, str);
	while (file.good()) {
		getline(file, str, ',');
		if (str == "")break;
		line.id = stoi(str);
		getline(file, str, ',');
		line.city_id = stoi(str);
		getline(file, str, ',');
		line.name = str;
		getline(file, str);
		theLine.push_back(line);
	}

	file.close();
}

//right
void ReadDatafromfileStationLines(L1List<Station_line>& theStation_line) {
	ifstream file;
	string str;
	Station_line sta_line;
	file.open("station_lines.csv");
	getline(file, str);
	while (file.good()) {
		getline(file, str, ',');
		if (str == "")break;
		sta_line.id = stoi(str);
		getline(file, str, ',');
		sta_line.station_id = stoi(str);
		getline(file, str, ',');
		sta_line.line_id = stoi(str);
		getline(file, str, ',');
		sta_line.city_id = stoi(str);
		getline(file, str);
		theStation_line.push_back(sta_line);
	}
	file.close();
}

//right
void ReadDatafromfileStation(L1List<Station>& theStation) {
	ifstream file;
	string str;
	Station sta;
	file.open("stations.csv");
	getline(file, str);
	while (file.good()) {
		getline(file, str, ',');
		if (str == "")break;
		sta.id = stoi(str);
		getline(file, str, ',');
		sta.name = str;
		getline(file, str, ',');
		sta.geometry = str;
		getline(file, str, ',');
		sta.buildstart = str;
		getline(file, str, ',');
		sta.opening = str;
		getline(file, str, ',');
		sta.closure = str;
		getline(file, str, '\n');
		sta.city_id = stoi(str);
		theStation.push_back(sta);
	}
	file.close();
}

//right
void ReadDatafromfileSystems(L1List<TLine>& theSystem) {
	ifstream file;
	string str;
	TLine sys;
	file.open("systems.csv");
	getline(file, str);
	while (file.good()) {
		getline(file, str, ',');
		if (str == "")break;
		sys.id = stoi(str);
		getline(file, str, ',');
		sys.city_id = stoi(str);
		getline(file, str, '\n');
		sys.name = str;
		theSystem.push_back(sys);
	}
	file.close();
}

//right
void ReadDatafromfileTrack(L1List<TTrack>& theTrack) {
	ifstream file;
	string str;
	TTrack track;
	file.open("tracks.csv");
	getline(file, str);
	while (file.good()) {
		getline(file, str, ',');
		if (str == "")break;
		track.track_id = stoi(str);
		if (track.track_id == 1474) {
			track.geometry = "";
		}
		else {
			getline(file, str, ')');
			track.geometry = str + ')' + '"';
		}
		getline(file, str, ',');
		getline(file, str, ',');
		getline(file, str, ',');
		getline(file, str, ',');
		getline(file, str, ',');
		getline(file, str, '\n');
		track.city_id = stoi(str);
		theTrack.push_back(track);
	}
	int i = theTrack.getSize();
	file.close();
}

void ReadDatafromfileTrack_line(L1List<Track_line>& theTrack_line) {
	ifstream file;
	string str;
	Track_line track_line;
	file.open("track_lines.csv");
	getline(file, str);
	while (file.good()) {
		getline(file, str, ',');
		if (str == "")break;
		track_line.id = stoi(str);
		getline(file, str, ',');
		track_line.selection_id = stoi(str);
		getline(file, str, ',');
		track_line.line_id = stoi(str);
		getline(file, str, ',');
		getline(file, str, ',');
		getline(file, str, '\n');
		track_line.city_id = stoi(str);
		theTrack_line.push_back(track_line);
	}
	file.close();
}

void LoadData(void*& pData) {
	TDataset* Data=new TDataset;
	ReadDatafromfileCities(Data->theCity);
	ReadDatafromfileLines(Data->theLine);
	ReadDatafromfileStation(Data->theStation);
	ReadDatafromfileStationLines(Data->theStation_line);
	ReadDatafromfileSystems(Data->Systems);
	ReadDatafromfileTrack(Data->theTrack);
	ReadDatafromfileTrack_line(Data->theTrack_line);
	pData = Data;
}

void ReleaseData(void*& pData) {
	pData = NULL;
}