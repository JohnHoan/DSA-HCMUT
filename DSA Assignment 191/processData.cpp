/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
	
}

void Finalization() {
    // Release your data before exiting
	
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number

	string pReq = pRequest;
	int index = 0;
	while ((pReq[index] != ' ')&&(index != pReq.length())) {
		index++;
	}
	string pReq1 = pReq.substr(0, index);
	string pReq2="";
	if(index != (pReq.length()))pReq2 = pReq.substr(index + 1, pReq.length() - 1);
	
	TDataset* Data = static_cast<TDataset *>(pData);
	if (pReq1 == "CL") {
		N = 1;
		int* Arr = new int[N];
		if (pReq2 == "") {
			Arr[0] = int(Data->theLine.getSize());
		}
		else {
			int syntax = -1;
			L1Item<TCity>* curCity = Data->theCity.getHead();
			while (curCity != NULL) {
				if (curCity->data.name == pReq2) {
					syntax = curCity->data.id;
					break;
				}
				curCity = curCity->pNext;
			}
			if (syntax == -1) {
				Arr[0] = -1;
			}
			else {
				int count = 0;
				L1Item<TLine>* curLine = Data->theLine.getHead();
				while (curLine != NULL) {
					if (curLine->data.city_id == syntax)count++;
					curLine = curLine->pNext;
				}
				Arr[0] = count;
			}
		}
		pOutput = Arr;
	}

	if (pReq1 == "LSC") {
		N = 0;
		int* Arr;
		int syntax = -1;
		L1Item<TCity>* curCity = Data->theCity.getHead();
		while (curCity != NULL) {
			if (curCity->data.name == pReq2) {
				syntax = curCity->data.id;
				break;
			}
			curCity = curCity->pNext;
		}
		if (syntax != -1) {
			L1Item<Station>* curStation = Data->theStation.getHead();
			while (curStation != NULL) {
				if (curStation->data.city_id == syntax)N++;
				curStation = curStation->pNext;
			}
			Arr = new int[N];
			int count = 0;
			curStation = Data->theStation.getHead();
			while (curStation != NULL) {
				if (curStation->data.city_id == syntax) Arr[count++] = curStation->data.id;
				curStation = curStation->pNext;
			}
		}
		else {
			N = 0;
			Arr = new int[1];
			Arr[0] = -1;
		}
		pOutput = Arr;
	}

	if (pReq1 == "LLC") {
		N = 0;
		int* Arr;
		int syntax = -1;
		L1Item<TCity>* curCity = Data->theCity.getHead();
		while (curCity != NULL) {
			if (curCity->data.name == pReq2) {
				syntax = curCity->data.id;
				break;
			}
			curCity = curCity->pNext;
		}
		if (syntax != -1) {
			L1Item<TLine>* curLine = Data->theLine.getHead();
			while (curLine != NULL) {
				if (curLine->data.city_id == syntax)N++;
				curLine = curLine->pNext;
			}
			Arr = new int[N];
			int count = 0;
			curLine = Data->theLine.getHead();
			while (curLine != NULL) {
				if (curLine->data.city_id == syntax)Arr[count++] = curLine->data.id;
				curLine = curLine->pNext;
			}
		}
		else {
			N = 0;
			Arr = new int[1];
			Arr[0] = -1;
		}
		pOutput = Arr;
	}

	if (pReq1 == "LSL") {
		int _line_id = stoi(pReq2);
		N = 0;
		L1Item<Station_line>* curStaLine = Data->theStation_line.getHead();
		while (curStaLine != NULL) {
			if (curStaLine->data.line_id == _line_id)N++;
			curStaLine = curStaLine->pNext;
		}
		int* Arr;
		if (N == 0) {
			Arr = new int[1];
			Arr[0] = -1;
		}
		else {
			Arr = new int[N];
			int count = 0;
			curStaLine = Data->theStation_line.getHead();
			while (curStaLine != NULL) {
				if (curStaLine->data.line_id == _line_id)Arr[count++] = curStaLine->data.station_id;
				curStaLine = curStaLine->pNext;
			}
		}
		pOutput = Arr;
	}
	if (pReq1 == "FC") {
		N = 0;
		int* Arr = new int[1];
		L1Item<TCity>* curCity = Data->theCity.getHead();
		while (curCity != NULL) {
			if (curCity->data.name.find(pReq2) != -1) {
				N = 1;
				Arr[0] = curCity->data.id;
				break;
			}
			curCity = curCity->pNext;
		}
		if (N == 0) {
			N = 1;
			Arr[0] = -1;
		}
		pOutput = Arr;
	}
	
	if (pReq1 == "FS") {
		N = 0;
		int* Arr = new int[1];
		L1Item<Station>* curSta = Data->theStation.getHead();
		while (curSta != NULL) {
			if (curSta->data.name.find(pReq2) != -1) {
				N = 1;
				Arr[0] = curSta->data.id;
				break;
			}
			curSta = curSta->pNext;
		}
		if (N == 0) {
			N = 1;
			Arr[0] = -1;
		}
		pOutput = Arr;
	}
	if (pReq1 == "SLP") {
		N = 1;
		int* Arr = new int[N];
		int index = pReq.find(' ', 4 + 1);
		string request2 = pReq.substr(4, index - 4);
		string request3 = pReq.substr(index, pReq.length() - index);
		string geo = "";
		L1Item<TTrack>* curTrack = Data->theTrack.getHead();
		while (curTrack != NULL) {
			if (curTrack->data.track_id == stoi(request3)) {
				geo = curTrack->data.geometry;
				break;
			}
			curTrack = curTrack->pNext;
		}
		geo = geo.erase(geo.length() - 2, 2);
		geo = geo.erase(0, 12);
		string target = "";
		L1Item<Station>* curSta = Data->theStation.getHead();
		while (curSta != NULL) {
			if (curSta->data.id == stoi(request2)) {
				target = curSta->data.geometry;
				break;
			}
			curSta = curSta->pNext;
		}
		if (target == "") {
			Arr[0] = -1;
			pOutput = Arr;
			return;
		}
		target = target.erase(target.length() - 1, 1);
		target = target.erase(0, 6);
		if (geo.find(target) == -1)Arr[0] = -1;
		else {
			int count = 0;
			int index1 = 0;
			int pos = geo.find(target) - 1;
			while (index1 < pos) {
				index1 = geo.find(',', index1 + 1);
				count++;
			}
			Arr[0] = count;
		}
		pOutput = Arr;
	}
	if (pReq1 == "IS") {
		N = 1;
		int* Arr = new int[N];
		int index = pReq2.find(',', 0);
		int count = 0;
		while (index != -1) {
			count++;
			index = pReq2.find(',', index + 1);
		}
		if (count + 1 != 5) Arr[0] = -1;
		else {
			Station station;
			index = pReq2.find(',', 0);
			station.name = pReq2.substr(0, index);
			int index1 = index;
			index = pReq2.find(',', index + 1);
			station.geometry = pReq2.substr(index1 + 1, index - index1 - 1);
			index1 = index;
			index = pReq2.find(',', index + 1);
			station.buildstart = pReq2.substr(index1 + 1, index - index1 - 1);
			index1 = index;
			index = pReq2.find(',', index + 1);
			station.opening = pReq2.substr(index1 + 1, index - index1 - 1);
			index1 = index;
			station.closure = pReq2.substr(index1 + 1, pReq2.length() - index1 - 1);
			station.city_id = 0;

			int id_max = 0;
			L1Item<Station>* curSta = Data->theStation.getHead();
			while (curSta != NULL) {
				if (id_max < curSta->data.id)id_max = curSta->data.id;
				curSta = curSta->pNext;
			}
			station.id = id_max + 1;
			Arr[0] = Data->theStation.push_back(station);
			if (Arr[0] == 0)Arr[0] = id_max + 1;
		}
		pOutput = Arr;
	}
	if (pReq1 == "RS") {
		N = 1;
		Station sta;
		int _station_id = stoi(pReq2);
		int* Arr = new int[N];
		Arr[0] = -1;
		L1Item<Station>* curSta = Data->theStation.getHead();
		int i = 0;
		while (curSta != NULL) {
			if (curSta->data.id == _station_id) {
				sta = curSta->data;
				Arr[0] = Data->theStation.remove(i);
				break;
			}
			curSta = curSta->pNext;
			i++;
		}
		if (Arr[0] == 0) {
			/*string target = sta.geometry;
			target = target.erase(target.length() - 1, 1);
			target = target.erase(0, 6);
			L1Item<TTrack>* curTrack = Data->theTrack.getHead();
			while (curTrack != NULL) {
				if (curTrack->data.geometry.find(target) != -1) {
					string res = curTrack->data.geometry;
					res = res.erase(res.find(target), target.length() + 1);
					if (res.length() - 2 != ')') {
						res = res.erase(res.length() - 1, 1);
						res += ')"';
					}
					curTrack->data.geometry = res;
				}
				curTrack = curTrack->pNext;
			}*/
			L1Item<Station_line>* curStaLine = Data->theStation_line.getHead();
			i = 0;
			while (curStaLine != NULL) {
				if (curStaLine->data.station_id == _station_id) {
					Data->theStation_line.remove(i);
					break;
				}
				curStaLine = curStaLine->pNext;
				i++;
			}
		}
		pOutput = Arr;
	}
	if (pReq1 == "US") {
		string target;
		string res;
		N = 1;
		int* Arr = new int[N];
		int index = pReq.find(' ', 3);
		int station_id = stoi(pReq.substr(3, index - 3)); //station_id needs to update
		string req3 = pReq.substr(index + 1, pReq.length() - index); //csv_description, information needs to update
		index = req3.find(',', 0);
		int count = 0;
		while (index != -1) {
			count++;
			index = req3.find(',', index + 1);
		}
		if (count + 1 != 5)Arr[0] = -1;
		else {
			L1Item<Station>* curSta = Data->theStation.getHead();
			while (curSta != NULL) {
				if (curSta->data.id == station_id) {
					index = pReq2.find(',', 0);
					curSta->data.name = pReq2.substr(0, index);
					int index1 = index;
					index = pReq2.find(',', index + 1);
					target = curSta->data.geometry;
					res = pReq2.substr(index1 + 1, index - index1 - 1);
					curSta->data.geometry = pReq2.substr(index1 + 1, index - index1 - 1);
					index1 = index;
					index = pReq2.find(',', index + 1);
					curSta->data.buildstart = pReq2.substr(index1 + 1, index - index1 - 1);
					index1 = index;
					index = pReq2.find(',', index + 1);
					curSta->data.opening = pReq2.substr(index1 + 1, index - index1 - 1);
					index1 = index;
					curSta->data.closure = pReq2.substr(index1 + 1, pReq2.length() - index1 - 1);
					break;
				}
				curSta = curSta->pNext;
			}
			Arr[0] = 0;
			
		}
		/*if (Arr[0] == 0) {
			target = target.erase(target.length() - 1, 1);
			target = target.erase(0, 6);
			res = res.erase(res.length() - 1, 1);
			res = res.erase(0, 6);
			L1Item<TTrack>* curTrack = Data->theTrack.getHead();
			while (curTrack != NULL) {
				if (curTrack->data.geometry.find(target) != -1) {
					int pos = curTrack->data.geometry.find(target);
					string temp = curTrack->data.geometry;
					temp = temp.erase(pos, target.length());
					temp.insert(pos, res);
					curTrack->data.geometry = temp;
				}
				curTrack = curTrack->pNext;
			}
		}*/
		pOutput = Arr;
	}
	
	if (pReq1 == "ISL") {
		string req2 = ""; //station_id
		string req3 = ""; //line_id
		string req4 = ""; //p_i
		int index = pReq.find(' ', 5);
		req2 = pReq.substr(4, index - 4);
		index = pReq.find(' ', index + 1);
		req3 = pReq.substr(pReq.find(req2) + req2.length() + 1, index - pReq.find(req2) - req2.length() - 1);
		req4 = pReq.substr(index + 1, pReq.length() - index);
		N = 1;
		int* Arr = new int[1];
		Arr[0] = -1;
		if (stoi(req4) < 0) {
			pOutput = Arr;
			return;
		}
		Station_line station;
		station.station_id = stoi(req2);
		station.line_id = stoi(req3);
		L1Item<Station_line>* curStaLine = Data->theStation_line.getHead();
		int i = 0;
		while (curStaLine != NULL) {
			if (curStaLine->data.line_id == stoi(req3) && curStaLine->data.station_id == stoi(req2)) {
				pOutput = Arr;
				return;
			}
			curStaLine = curStaLine->pNext;
			i++;
		}
		int count = 0;
		i = 0;
		curStaLine = Data->theStation_line.getHead();
		while (curStaLine != NULL) {
			if (curStaLine->data.line_id == stoi(req3)) {
				if (count == stoi(req4)) {
					Arr[0] = Data->theStation_line.insert(i, station);
					break;
				}
				else count++;
			}
			curStaLine = curStaLine->pNext;
			i++;
		}
		pOutput = Arr;
	}

	if (pReq1 == "RSL") {
		string req2 = "";//station_id
		string req3 = "";//line_id
		int index = pReq.find(' ', 5);
		req2 = pReq.substr(4, index - 4);
		req3 = pReq.substr(index + 1, pReq.length() - index);
		N = 1;
		int* Arr = new int[1];
		Arr[0] = -1;
		int i = 0;
		L1Item<Station_line>* curStaLine = Data->theStation_line.getHead();
		while (curStaLine != NULL) {
			if (curStaLine->data.line_id == stoi(req3) && curStaLine->data.station_id == stoi(req2)) {
				Arr[0] = Data->theStation_line.remove(i);
				break;
			}
			curStaLine = curStaLine->pNext;
			i++;
		}
		pOutput = Arr;
	}
}