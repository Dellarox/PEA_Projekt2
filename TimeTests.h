#pragma once
#include <iomanip>
#include <windows.h>
#include "Algorithm.h"

using namespace std;

class TimeTests {
public:
	double timeOfTest = 0;

	long long int read_QPC();

	void timeTestsForSimulatedAnnealing(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix);
	void timeTestsForTabuSearch(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix, int howMuchAttempts);
};