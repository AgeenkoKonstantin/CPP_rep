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
	cout << "Vvedite diameter" << endl;
	cin >> new_pipe.diameter;
	cout << "Vvedite dlinny" << endl;
	cin >> new_pipe.length;
	new_pipe.under_repair = false;
	new_pipe.id = -1;
	return new_pipe;
}
compressor create_compressor() {
	compressor new_compressor;
	cout << "Vvedite name" << endl;
	cin >> new_compressor.Name;

	cout << "Vvedite chislo cehov" << endl;
	cin >> new_compressor.number_workshops;

	cout << "Vvedite chislo rabot cehov" << endl;
	cin >> new_compressor.number_inwork;

	cout << "Vvedite effect" << endl;
	cin >> new_compressor.efficiency;
	return new_compressor;
}
void write_pipe_info(pipe p) {
	cout << "Diameter " << p.diameter << endl;
	cout << "Length " << p.length << endl;
	cout << "id " << p.id << endl;
	cout << (p.under_repair ? "V remonte" : "Ne v remonte") << endl;
}
void write_compressor_info(compressor comp) {
	cout << "Name: " << comp.Name << endl;
	cout << "chislo cehov: " << comp.number_workshops << endl;
	cout << "chislo rabot cehov: " << comp.number_inwork << endl;
	cout << "effectivnoct: " << comp.efficiency << endl;
}
void change_status(bool& status) {
	status = !status;
}

void save_to_file(pipe p) {
	ofstream fout; 
	fout.open("f.txt", ios::out);
	if (fout.is_open()) {
		fout << p.id << endl << p.diameter << endl << p.length << endl << p.under_repair;
		fout.close();
	}
}

pipe load_from_file() {
	ifstream fin;
	fin.open("f.txt", ios::in);
	pipe p;
	if (fin.is_open()) {
		fin >> p.id;
		fin >> p.diameter;
		fin >> p.length;
		fin >> p.under_repair;
		return p;
	}
}

int main()
{
	pipe p = create_pipe();
	save_to_file(p);
	write_pipe_info(load_from_file());

}

