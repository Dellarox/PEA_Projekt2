#include "Algorithm.h"

long long int read_QPC() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

bool Algorithm::fileReadLine(ifstream& file, int tab[], int size) {
	string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return(false);

	istringstream in_ss(s);

	for (int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
			return(false);
	}
	return(true);
}

bool Algorithm::fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix) {
	ifstream file;
	int tabNumberOfCities[1];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (fileReadLine(file, tabNumberOfCities, 1))
		{
			weightMatrix.clear();
			weightMatrix.resize(0);

			numberOfCities = tabNumberOfCities[0]; // przypisanie iloœci miast z pierwszej linijki pliku

			if (!isTest)
				cout << endl << "Iloœæ miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie wartoœci do vectora
				}
			}
		}
		else
			cout << "File error - READ INFO" << endl;
		file.close();
		return false;
	}
	else
		cout << "File error - OPEN" << endl;

	return false;
}

int pathLenght(vector<vector<int>> weightMatrix, vector<int> path) { // funkcja obliczaj¹ca d³ugoœæ œcie¿ki
	int lenght = 0;

	for (int i = 0; i < path.size() - 1; i++)
		lenght += weightMatrix[path[i]][path[i + 1]];

	lenght += weightMatrix[path[path.size() - 1]][path[0]];
	return lenght;
}

void Algorithm::simulatedAnnealing(vector<vector<int>> weightMatrix, int& result, vector<int>& path, float timeAlg){ // funkcja odpowiedzialna za wykonanie algorytmu symulowanego wy¿arzania
	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();
	srand(unsigned(time(NULL)));
	
	vector<int> pathHelp, bestPath;
	double temperature = 1000.0;
	int vertex1, vertex2;

	for (int i = 0; i < weightMatrix.size(); i++) // stworzenie domyœlnej œcie¿ki po wszystkich wierzcho³kach
		pathHelp.push_back(i);

	bestPath = pathHelp;

	for (int i = 0; i < 1000; i++) { // pêtla, która losuje 1000 rozwi¹zañ i wybiera najlepsze
		random_shuffle(pathHelp.begin(), pathHelp.end());
		if (pathLenght(weightMatrix, pathHelp) < pathLenght(weightMatrix, bestPath))
			bestPath = pathHelp;
	}

	pathHelp = bestPath;

	temperature = 0.5 * pathLenght(weightMatrix, bestPath);	// ustawienie temperatury na oko³o po³owê d³ugoœci najlepszej drogi - oko³o, poniewa¿ bierzemy jedno z tysi¹ca losowych rozwi¹zañ
															// taka wartoœæ temperatury to poprawna teoretyczna wartoœæ

	if (temperature > 1000) // jednak je¿eli temperatura jest wiêksza ni¿ 1000 ustawiamy j¹ na 1000, aby nie by³a za du¿a
		temperature = 1000;
	

	while (temperature > 0.00000001 && ((float)elapsed / frequency) < timeAlg) { // pêtla dzia³a dopóki nie osi¹gniemy za niskiej temperatury lub nie minie wyznaczony przez nas czas (kryterium stopu)
		vector<int> neighbour = pathHelp;

		vertex1 = rand() % pathHelp.size(); // losujemy pierwszy wierzcho³ek
		vertex2 = (vertex1 + rand() % pathHelp.size()) % pathHelp.size(); // losujemy drugi wierzcho³ek

		swap(neighbour[vertex1], neighbour[vertex2]); // zamieniamy kolejnoœæ wierzcho³ków, ¿eby mieæ 2 ró¿ne tablice

		double energy = pathLenght(weightMatrix, pathHelp); 
		double deltaEnergy = pathLenght(weightMatrix, neighbour);
		int resultHelp;

		if (deltaEnergy < energy) // je¿eli d³ugoœæ drogi s¹siada jest lepsza to if w linijce 121 zawsze siê wykona
			resultHelp = 1;
		else					// w przeciwnym razie liczymi szanse na przyjêcie gorszego rozwi¹zania (if w 121 nie zawsze siê wtedy wykona)
			resultHelp = exp(-(deltaEnergy - energy) / temperature);


		if (resultHelp > (double)rand() / RAND_MAX)
			pathHelp = neighbour;

		if (pathLenght(weightMatrix, pathHelp) < pathLenght(weightMatrix, bestPath)) // sprawdzenie czy d³ugoœæ œcie¿ki jest lepsza
			bestPath = pathHelp;

		temperature *= 0.999999;

		elapsed = read_QPC() - start;
	}

	path = bestPath;
	result = pathLenght(weightMatrix, bestPath);

	cout << "Czas: " << ((float)elapsed / frequency) << endl;
}
