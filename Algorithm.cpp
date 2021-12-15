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

			numberOfCities = tabNumberOfCities[0]; // przypisanie ilo�ci miast z pierwszej linijki pliku

			if (!isTest)
				cout << endl << "Ilo�� miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie warto�ci do vectora
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

int pathLenght(vector<vector<int>> weightMatrix, vector<int> path) { // funkcja obliczaj�ca d�ugo�� �cie�ki
	int lenght = 0;

	for (int i = 0; i < path.size() - 1; i++)
		lenght += weightMatrix[path[i]][path[i + 1]];

	lenght += weightMatrix[path[path.size() - 1]][path[0]];
	return lenght;
}

void Algorithm::simulatedAnnealing(vector<vector<int>> weightMatrix, int& result, vector<int>& path, float timeAlg){ // funkcja odpowiedzialna za wykonanie algorytmu symulowanego wy�arzania
	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();
	srand(unsigned(time(NULL)));
	
	vector<int> pathHelp, bestPath;
	double temperature = 1000.0;
	int vertex1, vertex2;

	for (int i = 0; i < weightMatrix.size(); i++) // stworzenie domy�lnej �cie�ki po wszystkich wierzcho�kach
		pathHelp.push_back(i);

	bestPath = pathHelp;

	for (int i = 0; i < 1000; i++) { // p�tla, kt�ra losuje 1000 rozwi�za� i wybiera najlepsze
		random_shuffle(pathHelp.begin(), pathHelp.end());
		if (pathLenght(weightMatrix, pathHelp) < pathLenght(weightMatrix, bestPath))
			bestPath = pathHelp;
	}

	pathHelp = bestPath;

	temperature = 0.5 * pathLenght(weightMatrix, bestPath);	// ustawienie temperatury na oko�o po�ow� d�ugo�ci najlepszej drogi - oko�o, poniewa� bierzemy jedno z tysi�ca losowych rozwi�za�
															// taka warto�� temperatury to poprawna teoretyczna warto��

	if (temperature > 1000) // jednak je�eli temperatura jest wi�ksza ni� 1000 ustawiamy j� na 1000, aby nie by�a za du�a
		temperature = 1000;
	

	while (temperature > 0.00000001 && ((float)elapsed / frequency) < timeAlg) { // p�tla dzia�a dop�ki nie osi�gniemy za niskiej temperatury lub nie minie wyznaczony przez nas czas (kryterium stopu)
		vector<int> neighbour = pathHelp;

		vertex1 = rand() % pathHelp.size(); // losujemy pierwszy wierzcho�ek
		vertex2 = (vertex1 + rand() % pathHelp.size()) % pathHelp.size(); // losujemy drugi wierzcho�ek

		swap(neighbour[vertex1], neighbour[vertex2]); // zamieniamy kolejno�� wierzcho�k�w, �eby mie� 2 r�ne tablice

		double energy = pathLenght(weightMatrix, pathHelp); 
		double deltaEnergy = pathLenght(weightMatrix, neighbour);
		int resultHelp;

		if (deltaEnergy < energy) // je�eli d�ugo�� drogi s�siada jest lepsza to if w linijce 121 zawsze si� wykona
			resultHelp = 1;
		else					// w przeciwnym razie liczymi szanse na przyj�cie gorszego rozwi�zania (if w 121 nie zawsze si� wtedy wykona)
			resultHelp = exp(-(deltaEnergy - energy) / temperature);


		if (resultHelp > (double)rand() / RAND_MAX)
			pathHelp = neighbour;

		if (pathLenght(weightMatrix, pathHelp) < pathLenght(weightMatrix, bestPath)) // sprawdzenie czy d�ugo�� �cie�ki jest lepsza
			bestPath = pathHelp;

		temperature *= 0.999999;

		elapsed = read_QPC() - start;
	}

	path = bestPath;
	result = pathLenght(weightMatrix, bestPath);

	cout << "Czas: " << ((float)elapsed / frequency) << endl;
}
