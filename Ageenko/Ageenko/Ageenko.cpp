#include <iostream>
#include <string>
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
int main()
{
	compressor c = create_compressor();
	write_compressor_info(c);

}

