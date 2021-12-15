#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <windows.h>

using namespace std;

class Algorithm {
public:


	bool fileReadLine(ifstream& file, int tab[], int size);

	bool fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix);

	void simulatedAnnealing(vector<vector<int>> weightMatrix, int& result, vector<int>& path, float time);
};