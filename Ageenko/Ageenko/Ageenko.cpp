#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Pipe.h"
#include "Compressor.h"
#include "utils.h"
#include "GTS.h"





using namespace std;


void save_to_file(const unordered_map<int, Pipe>& p, const unordered_map<int, CompressorStation>& c) {
	ofstream fout;
	string filename;
	cout << "Vvedite filename:" << std::endl;
	cin.ignore(256, '\n');
	getline(cin, filename, '\n');
	fout.open(filename, ios::out);
	if (fout.is_open()) {
		fout << p.size() << endl << c.size() << endl; 
		for (const auto& it : p)
		{
			fout << it.second;
		}
		for (const auto& it : c)
		{
			fout << it.second;
		}
		fout.close();
	}
}

void load_from_file(unordered_map <int, Pipe>& p,unordered_map <int, CompressorStation>& c) {
	ifstream fin;
	int countP, countC;
	string filename;
	cout << "Vvedite filename:" << std::endl;
	cin.ignore(256, '\n');
	getline(cin, filename, '\n');
	fin.open(filename, ios::in);
	if (fin.is_open()) {
		fin >> countP >> countC;
		p.reserve(countP);
		c.reserve(countC);
		for (int i = 0; i < countP; i++)
		{
			Pipe LoadedPipe;
			fin >> LoadedPipe;
			p.insert({ LoadedPipe.Getid(),LoadedPipe });
		}
		for (int i = 0; i < countC; i++)
		{
			CompressorStation LoadedCompressor;
			fin >> LoadedCompressor;
			c.insert({ LoadedCompressor.Getid(), LoadedCompressor });
		}
		fin.close();
	}
 }

void PrintMenu() {
	cout << "1. Load  from file" << endl;
	cout << "2. Create pipe" << endl;
	cout << "3. Create compressor" << endl;
	cout << "4. Change pipe status" << endl;
	cout << "5. Print info" << endl; 
	cout << "6. Save  to file" << endl;
	cout << "7. Change compressor" << endl;
	cout << "8. Find pipes by Name" << endl;
	cout << "9. Find pipes by Status" << endl;
	cout << "10. Find compressors by Name" << endl;
	cout << "11. Find compressors by percent" << endl;
	cout << "12. Paketnoe redaktirovanie trub" << endl;
	cout << "13. Ydalenie trub" << endl;
	cout << "14. Ydalenie KS" << endl;
	cout << "15. Add CS to GTS" << endl;
	cout << "16. Add Pipe to GTS" << endl;
	cout << "17. Connect CSs" << endl;
	cout << "18. Topological Sort" << endl;
	cout << "19. Shortest path " << endl;
	cout << "20. Max flow " << endl;
	cout << "0. Exit" << endl;
}


template<typename T>
using FilterP = bool(*)(const Pipe& p, T param);

bool CheckByName(const Pipe& p, string param) {
	return p.GetName() == param;
}
bool CheckByStatus(const Pipe& p, bool param) {
	return p.GetStatus() == param;
}

template <typename T>
vector<int> FindPipeByFilter(const unordered_map<int, Pipe>& map, FilterP<T> f, T param) {
	vector<int> res;
	for (const auto& it: map) {
		if (f(it.second, param)) {
			res.push_back(it.first);
		}
	}
	return res;
}

template<typename T>
using FilterC = bool(*)(const CompressorStation& c, T param);

bool CheckByName(const CompressorStation& c, string param) {
	return c.GetName() == param;
}
bool CheckByPercent(const CompressorStation& c, double param) {
	return (c.GetPercentWorkingWorkshops() >= param);  
}

template <typename T>
vector<int> FindCompressorByFilter(const unordered_map<int, CompressorStation>& map, FilterC<T> f, T param) {
	vector<int> res;
	for (const auto& it : map) {
		if (f(it.second, param)) {
			res.push_back(it.first);
		}
	}
	return res;
}

void PacketRedactTrub(unordered_map<int, Pipe>& map) {
	cout << "\tViberete redaktiruemie trubi: " << endl;
			cout << "\t1. Po statusu v remonte" << endl;
			cout << "\t2. Po statusu ne v remonte" << endl;
			cout << "\t3. Po viboru polzovatelya" << endl;
			cout << "\t0. Back" << endl;
			switch (get_value(0,3))
			{
			case 1:
			{
				for (int i : FindPipeByFilter(map, CheckByStatus, true))
					map.find(i)->second.change_status();
				break;
			}
			case 2:
			{
				for (int i : FindPipeByFilter(map, CheckByStatus, false))
					map.find(i)->second.change_status();
				break;
			}
			case 3: {
				vector<int> vec;
				while (1) {
					cout << "Vvedite ID" << endl;
					vec.push_back(get_value(0, Pipe::GetMaxid()));
					cout << "dobavit eshe?" << endl << "\t 0. Net" << endl << "\t 1. Da" << endl;
					if (get_value(0, 1) == 0)
						break;
				}
				for (auto i : vec) {
					if (map.find(i) != map.end())
						map.find(i)->second.change_status();
				}
				break;
			}
			case 0: {
				return;
			}
			}
}


template<typename T>
bool del(unordered_map<int, T>& map, int id) {
	return map.erase(id);
}

int main(){
	GTS GTS;
	unordered_map <int, Pipe> pipes;
	unordered_map <int, CompressorStation> compressors;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		switch (get_value(0, 20))
		{
		case 1:
		{
			load_from_file(pipes, compressors);
			break;
		}
			
		case 2: 
		{
			while (1) {
				Pipe pipe;
				cin >> pipe;
				pipes.insert({ pipe.Getid(), pipe });
				cout << "dobavit eshe?" << endl << "\t 0. Net" << endl << "\t 1. Da" << endl;
				if (get_value(0, 1) == 0) 
					break;
			}
			break;
		}
			
		case 3:
		{
			while (1) {
				CompressorStation comp;
				cin >> comp;
				compressors.insert({comp.Getid(), comp });
				cout << "dobavit eshe?" << endl << "\t 0. Net" << endl << "\t 1. Da" << endl;
				if (get_value(0, 1) == 0)
					break;
			}
			break;
		}
		case 4:	
		{
			cout << "Pipe id: " << endl;
			unordered_map<int, Pipe>::iterator iter = pipes.find(get_value(0, Pipe::GetMaxid()));
			if (iter == pipes.end())
				cout << "Truba is not found" << endl;
			else
				iter->second.change_status();
			break;
		}
		case 5:
		{
			for (const auto& it : pipes) {
				cout << it.second;
			}
			for (const auto& it : compressors) {
				cout << it.second;
			}
			break;
		}
		case 6:
		{
			save_to_file(pipes, compressors);
			break;
		}
		case 7: 
		{
			cout << "Compressor id: " << endl;
			unordered_map<int, CompressorStation>::iterator iter = compressors.find(get_value(0, CompressorStation::GetMaxid()));
			if (iter == compressors.end()) {
				cout << "Compressor doesnt exist" << endl;
			}
			else {
				cout << "\t Select action:" << endl;
				cout << "\t 1. Start work" << endl;
				cout << "\t 2. Stop work" << endl;
				switch (get_value(1, 2))
				{
				case 1:
					iter->second.RunStation();
					break;
				case 2:
					iter->second.StopStation();
					break;
				default:
					cout << "Select valid action " << endl;
					break;
				}
			}
			break;
		}
		case 8: {
			cout << "Vvedite name " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i:FindPipeByFilter<string>(pipes,CheckByName,name)) {
				cout << pipes.find(i)->second << endl;
			}
			break;
		}
		case 9: {
			for (int i : FindPipeByFilter(pipes, CheckByStatus, true)) {
				cout << pipes.find(i)->second << endl;
			}
			break;
		}
		case 10: {
			cout << "Vvedite name " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i : FindCompressorByFilter<string>(compressors, CheckByName, name)) {
				cout << compressors.find(i)->second << endl;
			}
			break;
		}
		case 11: {
			cout << "Vvedite percent ne rabot cehov:  " << endl;
			for (int i : FindCompressorByFilter(compressors, CheckByPercent, get_value(0.0,100.0))) {
				cout << compressors.find(i)->second << endl;
			}
			break;
		}
		case 12: {
			PacketRedactTrub(pipes);
			break;
		}
		case 13: {//сделать удаление сразу множества
			while (1) {
				cout << "Enter the id " << endl;
				int id = get_value(0, Pipe::GetMaxid());
				if (del(pipes, id)) {
					GTS.DeleteVertex(id);
					cout << "Truba ydalena" << endl;
				}
				else
					cout << "Deletion not executed" << endl;
				cout << "Udalit eshe?" << endl << "\t 0. Net" << endl << "\t 1. Da" << endl;
				if (get_value(0, 1) == 0)
					break;
			}
			break;
		}
		case 14: {
			while (1) {
				cout << "Id to delete" << endl;
				int id = get_value(0, CompressorStation::GetMaxid());
				if (del(compressors, id)) {
					GTS.DeleteEdge(id, pipes);
					cout << "KS ydalena" << endl;
				}
				else
					cout << "KS is not found" << endl;
				cout << "Udalit eshe?" << endl << "\t 0. Net" << endl << "\t 1. Da" << endl;
				if (get_value(0, 1) == 0)
					break;
			}
			break;
		}
		case 15: {
			cout << "Enter CS id" << endl;
			GTS.AddCS(compressors, get_value(0, CompressorStation::GetMaxid()));
			break;
		}
		case 16: {
			cout << "Enter Pipe id" << endl;
			GTS.AddPipe(pipes, get_value(0, Pipe::GetMaxid()));
			break;
		}
		case 17: {
			GTS.ConnectEdges(compressors, pipes);
			break;
		}
		case 18: {
			GTS.CreateAdjacencyMatrix(compressors, pipes);
			GTS.TopSort();
			break;
		}
		case 19: {
			GTS.CreateVesMatrix(compressors, pipes);
			cout << "enter first cs" << endl;
			int id1 = get_value(0, CompressorStation::GetMaxid());
			cout << "enter second cs" << endl;
			int id2 = get_value(0, CompressorStation::GetMaxid());
			GTS.MaxFlow(id1,id2);

			break;
		}
		case 20: {
			//макс поток
			break;
		}
		case 0:
		{
			return 0;
			break;
		}
		}
	}
}

