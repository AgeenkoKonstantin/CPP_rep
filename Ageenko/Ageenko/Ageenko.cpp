#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct compressor {
	int id;
	string Name;
	int number_workshops;
	int number_inwork;
	double efficiency;
};

struct pipe {
	int id;
	double length;
	int diameter;
	bool under_repair;
};
template <typename T>
T get_value(T left_border, T right_border) {
	int i;
	cin >> i;
	while (cin.fail() || i > right_border || i < left_border ) {
		cout << "Vvedite udovl znachenie " <<"(" << left_border <<" - " << right_border << ")" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> i;
	}
	return i;
}

pipe create_pipe() {
	pipe new_pipe;
	cout << "Vvedite diametr: " << endl;
	new_pipe.diameter = get_value(1, 3000);
	cout << "Vvedite dlinny: " << endl;
	new_pipe.length = get_value(1, 10000);
	new_pipe.under_repair = false;
	new_pipe.id = -1;
	return new_pipe;
}

compressor create_compressor() {
	compressor new_compressor;
	cout << "Vvedite name: " << endl;
	cin >> new_compressor.Name;
	cout << "Vvedite chislo  cehov: " << endl;
	new_compressor.number_workshops= get_value(1, 100);
	cout << "Vvedite chislo rabot cehov: " << endl;
	new_compressor.number_inwork = get_value(0, new_compressor.number_workshops);
	cout << "Vvedite effect: " << endl;
	new_compressor.efficiency = get_value(0, 100);
	new_compressor.id = -1;
	return new_compressor;
}

void write_pipe_info(const pipe& p) {
	if(p.id == -1){
		cout << "\t PIPE info: " << endl;
		cout << "Diameter: " << p.diameter << endl;
		cout << "Length: " << p.length << endl;
		cout << "id: " << p.id << endl;
		cout << (p.under_repair ? "V remonte" : "Ne v remonte") << endl;
	}
	else {
		cout << "Pipe doesnt exist" << endl;
	}
}

void write_compressor_info(const compressor& comp) {
	if(comp.id == -1){
		cout << "\t COMPRESSOR info: " << endl;
		cout << "Name: " << comp.Name << endl;
		cout << "id: " << comp.id << endl;
		cout << "Number of workshops: " << comp.number_workshops << endl;
		cout << "Number of working workshops: " << comp.number_inwork << endl;
		cout << "Efficienty: " << comp.efficiency << endl;
	}
	else {
		cout << "Compressor doesnt exist" << endl;
	}
		
}

void change_status(bool& status) {
	status = !status;
}

void save_to_fileP(const pipe& p, ofstream& fout) {
		fout << p.id << endl << p.diameter << endl << p.length << endl << p.under_repair << endl;
}
void save_to_fileC(const compressor& c, ofstream& fout) {
		fout << c.id << endl << c.Name << endl << c.number_workshops << endl << c.number_inwork << endl << c.efficiency << endl;
}
void save_to_file(const pipe& p,const compressor& c) {
	ofstream fout;
	fout.open("Data.txt", ios::out);
	if (fout.is_open()) {
		save_to_fileP(p, fout);
		save_to_fileC(c, fout);
		fout.close();
	}
}

pipe load_from_fileP(ifstream& fin) {
	pipe p;
		fin >> p.id >> p.diameter >> p.length >> p.under_repair;
		return p;
}
compressor load_from_fileC(ifstream& fin) {
	compressor c;
	fin >> c.id  >> c.Name >> c.number_workshops >> c.number_inwork >> c.efficiency;
		return c;
}
void load_from_file(pipe& p, compressor& c) {
	ifstream fin;
	fin.open("Data.txt", ios::in);
	if (fin.is_open()) {
		p = load_from_fileP(fin);
		c = load_from_fileC(fin);
		fin.close();
	}
 }

void stop_work(compressor& comp) {
	 if (comp.number_inwork > 0) {
		comp.number_inwork--;
	}
	else {
		cout << "Chislo rabot cehov = 0" << endl;
	}
}
void continue_work(compressor& comp) {
	 if (comp.number_inwork < comp.number_workshops) {
		comp.number_inwork++;
	}
	else {
		cout << "Vse  ceha rabotaut" << endl;
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

int main(){
	compressor comp;
	pipe p;
	int i,k;
	while (1) {
		cout << "Select action:" << endl;
		PrintMenu();
		i = get_value(0, 7);
		switch (i)
		{
		case 1:
			load_from_file(p, comp);
			break;
		case 2: 
			p = create_pipe();
			break;
		case 3:
			comp = create_compressor();
			break;
		case 4:	
			if (p.id == -1) {
				change_status(p.under_repair);
			}
			else {
				cout << "Pipe doesnt exist" << endl;
			}
			break;
		case 5:
			write_pipe_info(p);
			write_compressor_info(comp);
			break;
		case 6:
			save_to_file(p, comp);
			break;
		case 7: if (comp.id == -1){
					cout << "\t Select action:" << endl;
					cout << "\t 1. Start work" << endl;
					cout << "\t 2. Stop work" << endl;
					k = get_value(1, 2);
					switch (k)
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
		case 0:
			return 0;
			break;
		}
	}
}

