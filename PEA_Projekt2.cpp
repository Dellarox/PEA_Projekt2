#include <iostream>
#include "Algorithm.h"
#include <vector>

using namespace std;

vector<vector<int>> weightMatrixGlobal;
int numberOfCitiesGlobal;

void showRow(vector<int> weightMatrix) { // funkcja pomocnicza w wyświetlaniu macierzy
    for (int i = 0; i < (int)weightMatrix.size(); i++) {
        cout << weightMatrix[i];
        if (weightMatrix[i] > 9) {
            if (weightMatrix[i] < 100) {
                cout << "  ";
            }
            else {
                cout << " ";
            }
        }
        else {
            cout << "   ";
        }
    }
}

void showWeightMatrix(int numberOfCities, vector<vector<int>> weightMatrix) { // funkcja wyświetlajaca macierz

    if (numberOfCities == 0) {
        cout << "Nie wczytano struktury lub liczba miast wynosi 0!" << endl;
    }
    else {
        for (int i = 0; i < numberOfCities; i++) {
            showRow(weightMatrix[i]);
            cout << endl;
        }
        cout << endl;
    }
}

void doSA(float time) {
    Algorithm a;
    /*cout << "Odległości miedzy miastami:" << endl << endl;
    showWeightMatrix(numberOfCitiesGlobal, weightMatrixGlobal);
    cout << endl;*/
    int result;
    vector<int> path;
    a.simulatedAnnealing(weightMatrixGlobal, result, path, time);
    cout << "\nMinimalna długośc drogi: " << result << endl;
    cout << "\nŚciezka, ktora jest obierana: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << "--->";
    }
    cout << path[0];
}

void tests() { // funkcja, w ktorej odpalane sa wszystkie testy
    
    cout << "KONIEC TESToW" << endl;
}

int main()
{
    srand(time(NULL));
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    setlocale(LC_ALL, "polish");

    int menuOperation;
    char menuContinue;
    string fileName;
    bool checker;
    bool endProgram = false;
    Algorithm a;
    float time = 60;

    cout << "Projekt PEA    Kajetan Krason    252767" << endl << endl;

    do {
        cout << "1. Wczytaj strukture z pliku i ja pokaz." << endl;
        cout << "2. Pokaz wczytana strukture." << endl;
        cout << "3. Ustaw parametry." << endl;
        cout << "4. Rozwiaz problem komiwojazera na wczytanej strukturze  - symulowane wyzarzanie. (max czas trwania algorytmu: " << time << " sekund)" << endl;
        //cout << "5. Testy. " << endl;
        cout << "6. Opuśc program. " << endl;
        cin >> menuOperation;

        switch (menuOperation)
        {
        case 1:
            cout << "Podaj nazwe pliku (plik txt, bez rozszerzenia): " << endl;
            cin >> fileName;
            fileName.append(".txt");
            checker = a.fileReadGraph(fileName, false, numberOfCitiesGlobal, weightMatrixGlobal);
            break;
        case 2:
            cout << "Odległości miedzy miastami:" << endl << endl;
            showWeightMatrix(numberOfCitiesGlobal, weightMatrixGlobal);
            break;
        case 3:
            cout << "Podaj czas wykonania algorytmu:" << endl;
            cin >> time;
            break;
        case 4:
            if (time < 0)
                cout << "Nie wprowadzono parametru." << endl;
            else
                doSA(time);
            break;
        case 5:
            tests();
            break;
        case 6:
            endProgram = true;
            break;
        }
        cout << endl << endl;
        
    } while (!endProgram);
}