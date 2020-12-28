#pragma once
#include "GTS.h"
#include "utils.h"
#include <queue>
#include <vector>

void GTS::UpdateIndex()
{
	int i = 0;
	for (auto iter = IdIndexCS.begin(); iter != IdIndexCS.end(); iter++) {
		iter->second = i;
		++i;
	}
	i = 0;
		for (auto iter = IdIndexPipe.begin(); iter != IdIndexPipe.end(); iter++) {
			iter->second = i;
			++i;
	}
}

int GTS::GetCsIndex(int id) const
{
	return IdIndexCS.find(id)->second;
}

int GTS::GetCsId(int index) const
{
	for (auto iter = IdIndexCS.begin(); iter != IdIndexCS.end(); iter++) {
		if (iter->second == index)
			return iter->first;
	}
	//return 0;
}

void GTS::AddCS(const unordered_map<int, CompressorStation>& map, int id) //добавления 
{
	edges.insert(map.find(id)->first);
	IdIndexCS.insert({ id, edges.size() - 1 });
	cout << "CS added ID: " << IdIndexCS.find(id)->first << " Index: " << IdIndexCS.find(id)->second << endl;
	is_changed = true;

}

void GTS::AddPipe(const unordered_map<int, Pipe>& map, int id)
{

	vertex.insert(map.find(id)->first);
	IdIndexPipe.insert({id, vertex.size()-1});
	cout << "Pipe added ID: " << IdIndexPipe.find(id)->first << " Index: " << IdIndexPipe.find(id)->second << endl;
	is_changed = true;
}

void GTS::ConnectEdges(unordered_map<int, CompressorStation>& mapCS,unordered_map<int, Pipe>& mapPipe)
{
	cout << "Enter start CS: " << endl;
	int CSId1 = get_value(0, CompressorStation::GetMaxid());
	cout << "Enter pipe" << endl;
	int pipeId = get_value(0, Pipe::GetMaxid()); //чекнуть не используется ли уже труба
	cout << "Enter end CS: " << endl;
	int CSId2 = get_value(0, CompressorStation::GetMaxid());
	mapPipe.find(pipeId)->second.SetStart(CSId1);
	mapPipe.find(pipeId)->second.SetEnd(CSId2);
	cout << "CS: " << CSId1 << " was connected with CS: " << CSId2 << "by Pipe with id: "<< pipeId << endl;
	//mapPipe.find(pipeId)->second.ChangeUsed();// мб не нужно
	is_changed = true;
}


void GTS::CreateAdjacencyMatrix(unordered_map<int, CompressorStation>& mapCS, unordered_map<int, Pipe>& mapPipe) 
{
	int n = edges.size();
	if (is_changed) {
		UpdateIndex();
		AdjacencyMatrix.clear();
		AdjacencyMatrix.resize(n);
		for (int i = 0; i < n; i++) { 
			AdjacencyMatrix[i].resize(n); 
			is_changed = false;
		}
	}
	for (auto itr = mapPipe.begin(); itr != mapPipe.end(); itr++) {
		if (itr->second.GetStart() != -1) {
			AdjacencyMatrix[GetCsIndex(itr->second.GetStart())][GetCsIndex(itr->second.GetEnd())] = 1;
		}
	}
	for (int i = 0;i< n ; i++) {  //вывод матрица, можно закоментить
		for (int j = 0; j < n ; j++) {
			cout << AdjacencyMatrix[i][j] << " "; 
		}
		cout << endl;
	 }
}


void GTS::DeleteEdge(int id, unordered_map<int, Pipe>& mapPipe)
{
	is_changed = true;
	edges.erase(id);
	IdIndexCS.erase(id);

	for (auto iter = mapPipe.begin(); iter != mapPipe.end();) {
		if (iter->second.GetStart() == id || iter->second.GetEnd() == id) {
			DeleteVertex(iter->first);
			iter = mapPipe.erase(iter);
		}
		else
			iter++;
	}
}

void GTS::DeleteVertex(int id)
{
	is_changed = true;
	vertex.erase(id);
	IdIndexPipe.erase(id);

}

void GTS::TopologicalSort(int index, vector<int> & colors, bool & cycl, vector<int> & TopSortedVector)
{
	if (colors[index] == 2)
		return;
	if (cycl)
		return;
	if (colors[index] == 1) {
		cycl = true;
		return;
	}
	colors[index] = 1;
	for (int i = 0; i < edges.size(); i++) {
		if(AdjacencyMatrix[index][i] == 1){
			int AdjacencyEdge = i;
			TopologicalSort(AdjacencyEdge, colors, cycl, TopSortedVector);
			if (cycl)
				return;
		}
		
	}
	colors[index] = 2;
	TopSortedVector.push_back(GetCsId(index));
}

void GTS::TopSort()
{
	vector <int> colors;
	colors.resize(edges.size());
	vector<int> TopSortedVector;
	bool cycl = false;
	for (int i = 0; i < edges.size(); i++) {
		TopologicalSort(i, colors, cycl, TopSortedVector);
	}
	if (cycl) {
		cout << "There is cycle" << endl;
	}
	else {
		reverse(TopSortedVector.begin(), TopSortedVector.end());
		cout << "Topological sort: " << endl;
		for (int i = 0; i < TopSortedVector.size();i++) {
			cout << TopSortedVector[i] << " ";
		}
		cout << endl;
	}
}

void GTS::FindPath(int id1, int id2)
{

}
	







