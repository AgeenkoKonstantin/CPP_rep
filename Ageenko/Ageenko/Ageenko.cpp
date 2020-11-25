#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Pipe.h"
#include "Compressor.h"
#include "utils.h"

using namespace std;


void save_to_file(const vector<Pipe>& p, const vector<Compressor>& c) {
	ofstream fout;
	string filename;
	cout << "Vvedite filename:" << std::endl;
	cin.ignore(256, '\n');
	getline(cin, filename, '\n');
	fout.open(filename, ios::out);
	if (fout.is_open()) {
		fout << p.size() << endl << c.size() << endl; 
		for (const Pipe& it : p)
		{
			fout << it;
		}
		for (const Compressor& it : c)
		{
			fout << it;
		}
		fout.close();
	}
}

void load_from_file(vector <Pipe>& p,vector <Compressor>& c) {
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
			p.push_back(LoadedPipe);
		}
		for (int i = 0; i < countC; i++)
		{
			Compressor LoadedCompressor;
			fin >> LoadedCompressor;
			c.push_back(LoadedCompressor);
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
	cout << "0. Exit" << endl;
}

template <typename T>
T& SelecetObject(vector<T>& vec) {
	cout << "Type index:" << endl;
	unsigned int index = get_value(1u, vec.size());
	return vec[index-1];
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
vector<int> FindPipeByFilter(const vector<Pipe>& vec, FilterP<T> f, T param) {
	vector<int> res;
	int i = 0;
	for (auto it: vec) {
		if (f(it, param)) {
			res.push_back(i);
		}
		i++;
	}
	return res;
}

template<typename T>
using FilterC = bool(*)(const Compressor& c, T param);

bool CheckByName(const Compressor& c, string param) {
	return c.GetName() == param;
}
bool CheckByPercent(const Compressor& c, double param) {
	return (100.0*(c.GetWorkshops() - c.GetInWork())/c.GetWorkshops() >= param);
}

template <typename T>
vector<int> FindCompressorByFilter(const vector<Compressor>& vec, FilterC<T> f, T param) {
	vector<int> res;
	int i = 0;
	for (auto it : vec) {
		if (f(it, param)) {
			res.push_back(i);
		}
		i++;
	}
	return res;
}

int main(){
	vector <Pipe> pipes;
	vector <Compressor> compressors;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		switch (get_value(0, 11))
		{
		case 1:
		{
			load_from_file(pipes, compressors);
			break;
		}
			
		case 2: 
		{
			Pipe pipe;
			cin >> pipe;
			pipes.push_back(pipe);
			break;
		}
			
		case 3:
		{
			Compressor comp;
			cin >> comp;
			compressors.push_back(comp);
			break;
		}
		case 4:	
		{
			Pipe p = SelecetObject(pipes);
			if (p.Getid() == -1) {
				p.change_status();
			}
			else {
				cout << "Pipe doesnt exist" << endl;
			}
			break;
		}
		case 5:
		{
			for (auto& it : pipes) {
				cout << it;
			}
			for (auto& it : compressors) {
				cout << it;
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
			Compressor comp = SelecetObject(compressors);
			if (comp.Getid() == -1) {
				cout << "\t Select action:" << endl;
				cout << "\t 1. Start work" << endl;
				cout << "\t 2. Stop work" << endl;
				switch (get_value(1, 2))
				{
				case 1:
					comp.continue_work();
					break;
				case 2:
					comp.stop_work();
					break;
				default:
					cout << "Select valid action " << endl;
					break;
				}
			}
			else {
				cout << "Compressor doesnt exist" << endl;
			}
			break;
		}
		case 8: {
			cout << "Vvedite name " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i:FindPipeByFilter<string>(pipes,CheckByName,name)) {
				cout << pipes[i] << endl;
			}
			break;
		}
		case 9: {
			for (int i : FindPipeByFilter(pipes, CheckByStatus, true)) {
				cout << pipes[i] << endl;
			}
			break;
		}
		case 10: {
			cout << "Vvedite name " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i : FindCompressorByFilter<string>(compressors, CheckByName, name)) {
				cout << compressors[i] << endl;
			}
			break;
		}
		case 11: {
			cout << "Vvedite percent ne rabot cehov:  " << endl;
			for (int i : FindCompressorByFilter(compressors, CheckByPercent, get_value(0.0,100.0))) {
				cout << compressors[i] << endl;
			}
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

