#pragma once
#include "GTS.h"
#include "utils.h"

int GTS::GetCsIndex(int id) const
{
	return IdIndexCS.find(id)->second;
}

void GTS::AddCS(const unordered_map<int, CompressorStation>& map, int id)
{
	cout << "Enter CS id" << endl;
	edges.insert(map.find(id)->first);
	IdIndexCS.insert({ id, edges.size() - 1 });
	cout << "CS added ID: " << IdIndexCS.find(id)->first << " Index: " << IdIndexCS.find(id)->second << endl;
}

void GTS::AddPipe(const unordered_map<int, Pipe>& map, int id)
{
	cout << "Enter Pipe id" << endl;
	vertex.insert(map.find(id)->first);
	IdIndexPipe.insert({id, vertex.size()-1});
	cout << "Pipe added ID: " << IdIndexPipe.find(id)->first << " Index: " << IdIndexPipe.find(id)->second << endl;
}

void GTS::ConnectEdges(unordered_map<int, CompressorStation>& mapCS,unordered_map<int, Pipe>& mapPipe)
{
	cout << "Enter start CS: " << endl;
	int CSId1 = get_value(0, CompressorStation::GetMaxid());
	cout << "Enter pipe" << endl;
	int pipeId = get_value(0, Pipe::GetMaxid()); //чекнуть не используется ли уже труба
	cout << "Enter start CS: " << endl;
	int CSId2 = get_value(0, CompressorStation::GetMaxid());
	mapPipe.find(pipeId)->second.SetStart(CSId1);
	mapPipe.find(pipeId)->second.SetEnd(CSId2);
	cout << "CS: " << CSId1 << " was connected with CS: " << CSId2 << endl;
	//mapPipe.find(pipeId)->second.ChangeUsed();// мб не нужно
}


void GTS::CreateAdjacencyMatrix(unordered_map<int, CompressorStation>& mapCS, unordered_map<int, Pipe>& mapPipe) // делаем матрицу смежности
{
	AdjacencyMatrix.clear();
	int n = edges.size();
	AdjacencyMatrix.resize(n);
	for (int i = 0; i < n ; i++) { AdjacencyMatrix[i].resize(n); } 

	for (auto itr = mapPipe.begin(); itr != mapPipe.end(); itr++) {
		if (itr->second.GetStart() != -1) {
			AdjacencyMatrix[GetCsIndex(itr->second.GetStart())][GetCsIndex(itr->second.GetEnd())] = 1;
		}
	}
	// печать 
	for (int i = 0;i< n ; i++) {
		
		for (int j = 0; j < n ; j++) {
			cout << AdjacencyMatrix[i][j] << " ";
		}
		cout << endl;
	 }
}
