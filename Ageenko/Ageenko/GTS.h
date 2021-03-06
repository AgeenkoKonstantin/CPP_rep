#pragma once
#include "Pipe.h"
#include "Compressor.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>


using namespace std;

class GTS
{
	unordered_set<int> edges; //id ������
	unordered_set<int> vertex; //id �����

	unordered_map<int,int> IdIndexCS;
	unordered_map<int, int> IdIndexPipe;

	vector<vector<double>> VesMatrix;
	vector<vector<int>> AdjacencyMatrix; 
	vector<vector<double>> ProdMatrix;

	bool is_changed;

public:
	void MaxFlow(int, int);
	void ShortDist(int, int);

	void UpdateIndex();

	int GetCsIndex(int) const;

	int GetCsId(int) const;

	void AddCS(const unordered_map<int, CompressorStation>&, int);

	void AddPipe(const unordered_map<int, Pipe>&, int);
	
	void ConnectEdges( unordered_map<int, CompressorStation>&,  unordered_map<int, Pipe>&);

	void CreateProdMatrix(unordered_map<int, CompressorStation>&, unordered_map<int, Pipe>&);
	void CreateAdjacencyMatrix(unordered_map<int, CompressorStation>&, unordered_map<int, Pipe>&);
	void CreateVesMatrix(unordered_map<int, CompressorStation>&, unordered_map<int, Pipe>&);
		
	void DeleteEdge(int, unordered_map<int, Pipe>& );

	void DeleteVertex(int);

	void TopologicalSort(int, vector<int>&, bool&, vector<int>&);

	void TopSort();


	

};

