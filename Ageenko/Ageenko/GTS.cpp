#pragma once
#include "GTS.h"
#include "utils.h"
#include <queue>
#include <vector>
#include <set>





void GTS::ShortDist(int id1, int id2)
{
	const double INF = 100000.0;
	vector<bool> visited(edges.size());
	vector<double>  distance(edges.size());
	vector<int> parent(edges.size());
	for (int i = 0; i < edges.size(); i++) {
		visited[i] = false;
		distance[i] = INF;
	}
	int index, u;
	int index1 = GetCsIndex(id1);
	distance[index1] = 0;

	for (int count = 0; count < edges.size() - 1; count++) {
		int min = INF;
		for (int i = 0; i < edges.size(); i++) {
			if (!visited[i] && distance[i] <= min) {
				min = distance[i];
				index = i;
			}
		}
		
		visited[index] = true;
		for (int i = 0; i < edges.size();i++) {
			if (!visited[i] && VesMatrix[index][i] && distance[index]!=INF && distance[index]+VesMatrix[index][i]<distance[i]) {
				distance[i] = distance[index] + VesMatrix[index][i];
				parent.at(i) = index;
			}
		}
	}
	int index2 = GetCsIndex(id2);
	vector<int> temp;

	if (distance[index2] == INF) {
		cout << "pyti net" << endl;
			return;
	}

	int i = index2;
	while (1) {
		temp.push_back(i);
		if (i == index1) break;
		i = parent[i];
	}
	reverse(temp.begin(), temp.end());
	cout << "Path form " << id1 << " to " << id2 << " = " << distance[index2] << endl;
	cout << GetCsId(temp.at(0));
	for (int i = 1; i < temp.size(); ++i)
		cout << " -> " << GetCsId(temp.at(i)) ;
	cout << endl;
	
}

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
}

void GTS::AddCS(const unordered_map<int, CompressorStation>& map, int id) 
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
	int pipeId = get_value(0, Pipe::GetMaxid()); 
	cout << "Enter end CS: " << endl;
	int CSId2 = get_value(0, CompressorStation::GetMaxid());
	mapPipe.find(pipeId)->second.SetStart(CSId1);
	mapPipe.find(pipeId)->second.SetEnd(CSId2);
	cout << "CS: " << CSId1 << " was connected with CS: " << CSId2 << "by Pipe with id: "<< pipeId << endl;
	is_changed = true;
}


void GTS::CreateAdjacencyMatrix(unordered_map<int, CompressorStation>& mapCS, unordered_map<int, Pipe>& mapPipe) 
{
	int n = edges.size();
	if (AdjacencyMatrix.size() != n) {
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

void GTS::CreateProdMatrix(unordered_map<int, CompressorStation>& mapCS, unordered_map<int, Pipe>& mapPipe)
{
	int n = edges.size();
	if (ProdMatrix.size() != n) {
		UpdateIndex();
		ProdMatrix.clear();
		ProdMatrix.resize(n);
		for (int i = 0; i < n; i++) {
			ProdMatrix[i].resize(n);
		}
		is_changed = false;
	}
	for (auto itr = mapPipe.begin(); itr != mapPipe.end(); itr++) {
		if (itr->second.GetStart() != -1) {
			ProdMatrix[GetCsIndex(itr->second.GetStart())][GetCsIndex(itr->second.GetEnd())] = itr->second.GetProd();
		}
	}
	for (int i = 0; i < n; i++) {  //вывод матрицы, можно закоментить
		for (int j = 0; j < n; j++) {
			cout << ProdMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void GTS::CreateVesMatrix(unordered_map<int, CompressorStation>& mapCS, unordered_map<int, Pipe>& mapPipe)
{
	int n = edges.size();
	if (VesMatrix.size() != n) {
		UpdateIndex();
		VesMatrix.clear();
		VesMatrix.resize(n);
		for (int i = 0; i < n; i++) {
			VesMatrix[i].resize(n);
		}
		is_changed = false;
	}
	for (auto itr = mapPipe.begin(); itr != mapPipe.end(); itr++) {
		if (itr->second.GetStart() != -1) {
			VesMatrix[GetCsIndex(itr->second.GetStart())][GetCsIndex(itr->second.GetEnd())] = itr->second.GetWeight();
		}
	}
	for (int i = 0; i < n; i++) {  //вывод матрицы, можно закоментить
		for (int j = 0; j < n; j++) {
			cout << VesMatrix[i][j] << " ";
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
	

double min(double x, double y)
{
	if (x < y)
		return x;
	else
		return y;
}


void Enque(int x, vector<int>& q, int& tail, vector<int>& color)
{
	q[tail] = x;
	tail++;
	color[x] = 1;
}

int bfs(int start, int end, vector<int>& color, vector<double>& pred, vector<int>& q, vector<vector<double>>& capacity, vector<vector<double>>& flow, int n, int& head, int& tail)
{
	for (int u = 0; u < n; u++)
		color[u] = 0;

	head = 0;
	tail = 0;
	Enque(start, q, tail, color);
	pred[start] = -1;
	while (head != tail)
	{
		int u = q[head];
		head++;
		color[u] = 2;
		for (int v = 0; v < n; v++)
		{
			if (color[v] == 0 && (capacity[u][v] - flow[u][v]) > 0) {
				Enque(v, q, tail, color);
				pred[v] = u;
			}
		}
	}
	if (color[end] == 2)
		return 0;
	else return 1;
}

void GTS::MaxFlow(int id1, int id2)
{
	int start = GetCsIndex(id1);
	int end = GetCsIndex(id2);
	int n = edges.size();
	int head, tail;
	vector<vector<double>> flow;
	vector<int> color, q;
	vector<double> pred;
	double maxflow = 0.0;
	flow.resize(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			flow[i].push_back(0);
		color.push_back(-1);
		pred.push_back(-1);
		q.push_back(0);
	}
	q.push_back(0); 
	q.push_back(0);
	while (bfs(start, end, color, pred, q, ProdMatrix, flow, n, head, tail) == 0)
	{
		double delta = 10000.0;
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			delta = min(delta, (ProdMatrix[pred[u]][u] - flow[pred[u]][u]));
		}
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			flow[pred[u]][u] += delta;
			flow[u][pred[u]] -= delta;
		}
		maxflow += delta;
	}
	cout <<  "Max potok: " << maxflow << endl;
}
	







