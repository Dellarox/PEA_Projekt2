#include "TimeTests.h"

long long int TimeTests::read_QPC() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForSimulatedAnnealing(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	bool checker = a.fileReadGraph(fileName, true, numberOfCities, weightMatrix);

	timeOfTest = 0;
	start = read_QPC();
	for (int i = 0; i < 1; i++) {
		cout << "test symulowane wyżarzanie" << endl;
	}
	elapsed = read_QPC() - start;
	timeOfTest = (1.0 * elapsed) / frequency;
	cout << "Uśredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest / 100 << "." << endl;
}

void TimeTests::timeTestsForTabuSearch(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix, int howMuchAttempts) { // dodane jest howMuchAttempts, aby zbadaæ wyniki dla 13 miast, poniewa¿ dla 100 powtórzonych prób wynik by³by bardzo du¿y
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	bool checker = a.fileReadGraph(fileName, true, numberOfCities, weightMatrix);
	int result;
	vector<int> path;

	timeOfTest = 0;
	start = read_QPC();
	for (int i = 0; i < 1; i++)
		cout << "test tabu search" << endl;
	elapsed = read_QPC() - start;
	timeOfTest = (1.0 * elapsed) / frequency;
	if (howMuchAttempts == 100)
		cout << "Uśredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest / 100 << "." << endl;
	if (howMuchAttempts == 30)
		cout << "Uśredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest / 30 << "." << endl;
}