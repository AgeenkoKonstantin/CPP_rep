#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Pipe.h"
#include "Compressor.h"
#include "utils.h"

using namespace std;



void save_to_fileP(const Pipe& p, ofstream& fout) {
		fout << p.Getid() << endl << p.GetName() << endl << p.GetDiametr() << endl << p.GetLength() << endl << p.GetStatus() << endl;
}

void save_to_fileC(const Compressor& c, ofstream& fout) {
		fout <<  c.Getid() <<endl << c.GetName() << endl << c.GetWorkshops() << endl << c.GetInWork() << endl << c.GetEfficiency() << endl;
}

void save_to_file(const vector<Pipe>& p, const vector<Compressor>& c) {
	ofstream fout;
	fout.open("Data.txt", ios::out);
	if (fout.is_open()) {
		fout << p.size() << endl << c.size() << endl; //сколько в след раз считывать труб и компрессоров 
		for (const Pipe& it : p)
		{
			save_to_fileP(it, fout);
		}
		for (const Compressor& it : c)
		{
			save_to_fileC(it, fout);
		}
		fout.close();
	}
}

//Pipe load_from_fileP(ifstream& fin) {
//	Pipe p;
//	fin >> p.id;
//	fin.ignore(256, '\n');
//	getline(fin, p.name);
//	fin >> p.diametr >> p.length >> p.under_repair;
//
//		return p;
//}

//Compressor load_from_fileC(ifstream& fin) {
//	Compressor c;
//	
//	fin >> c.id;
//	fin.ignore(256,'\n');
//	getline(fin, c.name);
//	 fin >> c.number_workshops >> c.number_inwork >> c.efficiency;
//		return c;
//}

//void load_from_file(vector <Pipe>& p,vector <Compressor>& c) {
//	ifstream fin;
//	int countP, countC;
//	fin.open("Data.txt", ios::in);
//	if (fin.is_open()) {
//		fin >> countP >> countC;
//		p.reserve(countP);
//		c.reserve(countC);
//		for (int i = 0; i < countP; i++)
//		{
//			p.push_back(load_from_fileP(fin));
//		}
//		for (int i = 0; i < countC; i++)
//		{
//			c.push_back(load_from_fileC(fin));
//		}
//		fin.close();
//	}
// }



void PrintMenu() {
	cout << "1. Load  from file" << endl;
	cout << "2. Create pipe" << endl;
	cout << "3. Create compressor" << endl;
	cout << "4. Change pipe status" << endl;
	cout << "5. Print info" << endl; 
	cout << "6. Save  to file" << endl;
	cout << "7. Update compressor" << endl;
	cout << "0. Exit" << endl;
}

template <typename T>
T& SelecetObject(vector<T>& vec) {
	cout << "Type index:" << endl;
	unsigned int index = get_value(1u, vec.size());
	return vec[index-1];
}

int main(){
	vector <Pipe> pipes;
	vector <Compressor> compressors;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		switch (get_value(0, 7))
		{
		case 1:
		{
			//load_from_file(pipes, compressors);
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
			cout << SelecetObject(pipes);
			cout << SelecetObject(compressors);
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
		case 0:
		{
			return 0;
			break;
		}
		}
	}
}

