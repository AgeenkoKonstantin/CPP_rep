#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct pipe {
	int id;
	double length;
	int diameter;
	bool under_repair;
};
struct compressor {
	int id;
	string Name;
	int number_workshops;
	int number_inwork;
	double efficiency;
};


pipe create_pipe() {
	pipe new_pipe;
	do {
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Vvedite diameter: " << endl;
		cin >> new_pipe.diameter;
	} while (!(new_pipe.diameter > 0) || cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Vvedite dlinny: " << endl;
		cin >> new_pipe.length;
	} while (!(new_pipe.length > 0) || cin.fail());
	new_pipe.under_repair = false;
	new_pipe.id = -1;
	return new_pipe;
}
compressor create_compressor() {
	compressor new_compressor;
		cout << "Vvedite name: " << endl;
		cin >> new_compressor.Name;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Vvedite chislo cehov: " << endl;
		cin >> new_compressor.number_workshops;
	} while (!(new_compressor.number_workshops > 0) || cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Vvedite chislo rabot cehov: " << endl;
		cin >> new_compressor.number_inwork;
	} while (!(new_compressor.number_inwork >= 0) || !(new_compressor.number_inwork <= new_compressor.number_workshops) || cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Vvedite effect: " << endl;
		cin >> new_compressor.efficiency;
	} while (!(new_compressor.efficiency > 0) || cin.fail());
	new_compressor.id = -1;
	return new_compressor;
}

void write_pipe_info(const pipe& p) {
	cout << "PIPE info: " << endl;
	cout << "Diameter: " << p.diameter << endl;
	cout << "Length: " << p.length << endl;
	cout << "id: " << p.id << endl;
	cout << (p.under_repair ? "V remonte" : "Ne v remonte") << endl;
}
void write_compressor_info(const compressor& comp) {
	cout << "COMPRESSOR info: " << endl;
	cout << "Name: " << comp.Name << endl;
	cout << "Number of workshops: " << comp.number_workshops << endl;
	cout << "Number of working workshops: " << comp.number_inwork << endl;
	cout << "Efficienty: " << comp.efficiency << endl;
}

void change_status(bool& status) {
	status = !status;
}


//void save_to_fileP(pipe p) {
//	ofstream fout; 
//	fout.open("dataP.txt", ios::out);
//	if (fout.is_open()) {
//		fout << p.id << endl << p.diameter << endl << p.length << endl << p.under_repair;
//		fout.close();
//	}
//}
//void save_to_fileC(compressor c) {
//	ofstream fout;
//	fout.open("dataC.txt", ios::out);
//	if (fout.is_open()) {
//		fout << c.id << endl << c.Name << endl << c.number_workshops << endl << c.number_inwork << endl << c.efficiency;
//		fout.close();
//	}
//}

void save_to_file(pipe p, compressor c) {
	ofstream fout;
	fout.open("Data.txt", ios::out);
	if (fout.is_open()) {
		fout << p.id << endl << p.diameter << endl << p.length << endl << p.under_repair <<endl;
		fout << c.id << endl << c.Name << endl << c.number_workshops << endl << c.number_inwork << endl << c.efficiency;
		fout.close();
	}
}

pipe load_from_fileP() {
	ifstream fin;
	fin.open("Data.txt", ios::in);
	pipe p;
	if (fin.is_open()) {
		fin >> p.id;
		fin >> p.diameter;
		fin >> p.length;
		fin >> p.under_repair;
		fin.close();
		return p;
	}
}
compressor load_from_fileC() {
	ifstream fin;
	fin.open("Data.txt", ios::in);
	compressor c;
	if (fin.is_open()) {
		for (int i = 0; i < 4; i++)
		{
			fin.ignore(256, '\n');
		}
		fin >> c.id;
		fin >> c.Name;
		fin >> c.number_workshops;
		fin >> c.number_inwork;
		fin >> c.efficiency;
		return c;
		fin.close();
	}
}
void stop_work(compressor& comp) {
	if (comp.number_inwork > 0) {
		comp.number_inwork--;
	}
	else {
		cout << "Chislo cehov = 0" << endl;
	}
}
void continue_work(compressor& comp) {
	if(comp.number_inwork < comp.number_workshops){
		comp.number_inwork++;
	}
	else {
		cout << "Vse rabotaet" << endl;
	}
	
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

int main()
{
	compressor comp;
	pipe p;
	int i;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		cin >> i;
		switch (i)
		{
		case 1:
			p = load_from_fileP();
			comp = load_from_fileC();
			
			break;
		case 2: p = create_pipe();
			break;
		case 3:
			comp = create_compressor();
			break;
		case 4:
			change_status(p.under_repair);
			break;
		case 5:
			write_pipe_info(p);
			write_compressor_info(comp);
			break;
		case 6:
			
			save_to_file(p, comp);
			break;
		case 7:
				cout << "\t Select action:" << endl;
				cout << "\t 1. Start work" << endl;
				cout << "\t 2. Stop work" << endl;
				cin >> i;
				switch (i)
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
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "Select valid action: " << endl;
			break;
		}
		
	}

}

