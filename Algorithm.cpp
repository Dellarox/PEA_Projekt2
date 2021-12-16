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

			numberOfCities = tabNumberOfCities[0]; // przypisanie ilosci miast z pierwszej linijki pliku

			if (!isTest)
				cout << endl << "Ilosc miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie wartosci do vectora
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

int pathLenght(vector<vector<int>> weightMatrix, vector<int> path) { // funkcja obliczajaca dlugosc sciezki
	int lenght = 0;

	for (int i = 0; i < path.size() - 1; i++)
		lenght += weightMatrix[path[i]][path[i + 1]];

	lenght += weightMatrix[path[path.size() - 1]][path[0]];
	return lenght;
}

void Algorithm::simulatedAnnealing(vector<vector<int>> weightMatrix, int& result, vector<int>& path, float timeAlg){ // funkcja odpowiedzialna za wykonanie algorytmu symulowanego wyzarzania
	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();
	srand(unsigned(time(NULL)));
	
	vector<int> pathHelp, bestPath;
	double temperature = 1000.0;
	int vertex1, vertex2;
	int bestPathLenght;

	for (int i = 0; i < weightMatrix.size(); i++) // stworzenie domyslnej sciezki po wszystkich wierzcholkach
		pathHelp.push_back(i);

	bestPath = pathHelp;

	for (int i = 0; i < 1000; i++) { // petla, ktora losuje 1000 rozwiazan i wybiera najlepsze
		random_shuffle(pathHelp.begin(), pathHelp.end());
		if (pathLenght(weightMatrix, pathHelp) < pathLenght(weightMatrix, bestPath))
			bestPath = pathHelp;
	}

	pathHelp = bestPath;

	temperature = 0.5 * pathLenght(weightMatrix, bestPath);	// ustawienie temperatury na okolo polowe dlugosci najlepszej drogi - okolo, poniewaz bierzemy jedno z tysiaca losowych rozwiazan
															

	if (temperature > 1000) // jednak jezeli temperatura jest wieksza niz 1000 ustawiamy ja na 1000, aby nie wydluzac za bardzo dzialania algorytmu
		temperature = 1000;
	
	bestPathLenght = pathLenght(weightMatrix, bestPath);
	double energy = pathLenght(weightMatrix, pathHelp);

	while (temperature > 0.00000001 && ((float)elapsed / frequency) < timeAlg) { // petla dziala dopoki nie osiagniemy za niskiej temperatury lub nie minie wyznaczony przez nas czas (kryterium stopu)
		vector<int> neighbour = pathHelp;

		vertex1 = rand() % pathHelp.size(); // losujemy pierwszy wierzcholek
		vertex2 = (vertex1 + rand() % pathHelp.size()) % pathHelp.size(); // losujemy drugi wierzcholek

		swap(neighbour[vertex1], neighbour[vertex2]); // zamieniamy kolejnosc wierzcholkow, zeby miec 2 rozne tablice

		double deltaEnergy = pathLenght(weightMatrix, neighbour);
		double resultHelp;

		if (deltaEnergy < energy) // jezeli dlugosc drogi sasiada jest lepsza to if w linijce 123 zawsze sie wykona
			resultHelp = 1;
		else					// w przeciwnym razie liczymi szanse na przyjecie gorszego rozwiazania (if w 123 nie zawsze sie wtedy wykona)
			resultHelp = exp(-(deltaEnergy - energy) / temperature);


		if (resultHelp > (double)rand() / RAND_MAX) {
			pathHelp = neighbour;
			energy = deltaEnergy;
		}
		
			
		if (deltaEnergy < bestPathLenght) { // sprawdzenie czy dlugosc sciezki jest lepsza
			bestPath = pathHelp;
			bestPathLenght = pathLenght(weightMatrix, bestPath);
		}

		temperature *= 0.999999;

		elapsed = read_QPC() - start;
	}

	path = bestPath;
	result = pathLenght(weightMatrix, bestPath);

	cout << "Czas: " << ((float)elapsed / frequency) << endl;
}
