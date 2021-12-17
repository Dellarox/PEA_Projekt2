#include "TimeTests.h"

long long int read_QPCForTimeTests() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForSA(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	static double timeOfTest;
	int result;
	vector<int> path;

	bool checker = a.fileReadGraph(fileName, true, numberOfCities, weightMatrix);

	timeOfTest = 0;
	start = read_QPCForTimeTests();
	for (int i = 0; i < 100; i++) {
		a.simulatedAnnealing(weightMatrix, result, path, 60);
	}
	elapsed = read_QPCForTimeTests() - start;
	timeOfTest = (1.0 * elapsed) / frequency;
	cout << "Usredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest / 100 << "." << endl;
}
