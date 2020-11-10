#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//#include "Pipe.h"
//#include "Compressor.h"

using namespace std;

struct Compressor {
	int id;
	string name;
	int number_workshops;
	int number_inwork;
	double efficiency;
};

struct Pipe {
	string name;
	int id;
	double length;
	int diametr;
	bool under_repair;
};

template <typename T>
T get_value(T left_border, T right_border) {
	T i;
	while ((cin >> i).fail() || i > right_border || i < left_border ) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Vvedite udovl znachenie " << "(" << left_border << " - " << right_border << ")" << endl;
	}
	return i;
}


void change_status(bool& status) {
	status = !status;
}

void save_to_fileP(const Pipe& p, ofstream& fout) {
		fout << p.id << endl << p.name << endl << p.diametr << endl << p.length << endl << p.under_repair << endl;
}

void save_to_fileC(const Compressor& c, ofstream& fout) {
		fout <<  c.id <<endl << c.name << endl << c.number_workshops << endl << c.number_inwork << endl << c.efficiency << endl;
}

void save_to_file(const vector<Pipe>& p, const vector<Compressor>& c) {
	ofstream fout;
	fout.open("Data.txt", ios::out);
	if (fout.is_open()) {
		fout << p.size() << endl << c.size() << endl; //сколько в след раз считывать труб и компрессоров 
		for (Pipe it : p)
		{
			save_to_fileP(it, fout);
		}
		for (Compressor it : c)
		{
			save_to_fileC(it, fout);
		}
		fout.close();
	}
}

Pipe load_from_fileP(ifstream& fin) {
	Pipe p;
	fin >> p.id;
	fin.ignore(256, '\n');
	getline(fin, p.name);
	fin >> p.diametr >> p.length >> p.under_repair;

		return p;
}

Compressor load_from_fileC(ifstream& fin) {
	Compressor c;
	
	fin >> c.id;
	fin.ignore(256,'\n');
	getline(fin, c.name);
	 fin >> c.number_workshops >> c.number_inwork >> c.efficiency;
		return c;
}

void load_from_file(vector <Pipe>& p,vector <Compressor>& c) {
	ifstream fin;
	int countP, countC;
	fin.open("Data.txt", ios::in);
	if (fin.is_open()) {
		fin >> countP >> countC;
		for (int i = 0; i < countP; i++)
		{
			p.push_back(load_from_fileP(fin));
		}
		for (int i = 0; i < countC; i++)
		{
			c.push_back(load_from_fileC(fin));
		}
		fin.close();
	}
 }

void stop_work(Compressor& comp) {
	 if (comp.number_inwork > 0) {
		comp.number_inwork--;
	}
	else {
		cout << "Chislo rabot cehov = 0" << endl;
	}
}

void continue_work(Compressor& comp) {
	 if (comp.number_inwork < comp.number_workshops) {
		comp.number_inwork++;
	}
	else {
		cout << "Vse  ceha rabotaut" << endl;
	}
}

ostream& operator << (ostream& out, const Compressor& c) {
	if (c.id == -1) {
		out << "\t COMPRESSOR info: " << endl;
		out << "Name: " << c.name << endl;
		out << "id: " << c.id << endl;
		out << "Number of workshops: " << c.number_workshops << endl;
		out << "Number of working workshops: " << c.number_inwork << endl;
		out << "Efficienty: " << c.efficiency << endl;
	}
	else {
		out << "Compressor doesnt exist" << endl;
	}
	return out;
}

ostream& operator << (ostream& out,const Pipe& p) {
	if (p.id == -1) {
		out << "\t PIPE info: " << endl;
		out << "Name: " << p.name << endl;
		out << "Diameter: " << p.diametr << endl;
		out << "Length: " << p.length << endl;
		out << "id: " << p.id << endl;
		out << (p.under_repair ? "V remonte" : "Ne v remonte") << endl;
	}
	else {
		cout << "Pipe doesnt exist" << endl;
	}
	return out;
}

istream& operator >> (istream& in, Compressor& c) {
	cout << "Vvedite name:" << endl;
	cin.ignore(256, '\n');
	getline(in, c.name, '\n');
	cout << "Vvedite chislo  cehov: " << endl;
	c.number_workshops = get_value(1, 100);
	cout << "Vvedite chislo rabot cehov: " << endl;
	c.number_inwork = get_value(0, c.number_workshops);
	cout << "Vvedite effect: " << endl;
	c.efficiency = get_value(0.0, 100.0);
	c.id = -1;
	return in;
}

istream& operator >> (istream& in, Pipe& p) {
	cout << "Vvedite name:" << endl;
	cin.ignore(256, '\n');
	getline(in, p.name, '\n');
	cout << "Vvedite diametr: " << endl;
	p.diametr = get_value(1, 3000);
	cout << "Vvedite dlinny: " << endl;
	p.length = get_value(1.0, 10000.0);
	p.under_repair = false;
	p.id = -1;
	return in;
}

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
			if (p.id == -1) {
				change_status(p.under_repair);
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
			if (comp.id == -1) {
				cout << "\t Select action:" << endl;
				cout << "\t 1. Start work" << endl;
				cout << "\t 2. Stop work" << endl;
				switch (get_value(1, 2))
				{
				case 1:
					continue_work(comp);
					break;
				case 2:
					stop_work(comp);
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

