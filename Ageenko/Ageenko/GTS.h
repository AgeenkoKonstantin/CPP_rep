#pragma once
#include "Pipe.h"
#include "Compressor.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>


using namespace std;

class GTS
{
	unordered_set<int> edges; //id вершин
	unordered_set<int> vertex; //id ребер

	unordered_map<int,int> IdIndexCS;
	unordered_map<int, int> IdIndexPipe;

	vector<vector<int>> AdjacencyMatrix; 
	vector<vector<int>> IncidenceMatrix;

public:
	int GetCsIndex(int) const;

	void AddCS(const unordered_map<int, CompressorStation>&, int);

	void AddPipe(const unordered_map<int, Pipe>&, int);
	
	void ConnectEdges( unordered_map<int, CompressorStation>&,  unordered_map<int, Pipe>&);


	void CreateAdjacencyMatrix(unordered_map<int, CompressorStation>&, unordered_map<int, Pipe>&);

		
	
};

