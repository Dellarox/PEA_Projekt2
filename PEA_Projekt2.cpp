﻿#include <iostream>
#include "Algorithm.h"
#include "TimeTests.h"
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

void showWeightMatrix(int numberOfCities, vector<vector<int>> weightMatrix) { // funkcja wyświetlająca macierz

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

void tests() { // funkcja, w której odpalane są wszystkie testy, domyślne zakomentowana, aby nie resetować programu podczas przypadkowego jej uruchomienia.
    /*cout << "Programowanie dynamiczne:" << endl;
    tt.timeTestsForDynamicProggraming(gtt, "18_miast.txt", 18, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "19_miast.txt", 19, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "20_miast.txt", 20, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "21_miast.txt", 21, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "22_miast.txt", 22, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "23_miast.txt", 23, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "24_miast.txt", 24, weightMatrixGlobal);
    cout << "Brute force:" << endl;
    tt.timeTestsForBruteForce(gtt, "8_miast.txt", 8, weightMatrixGlobal, 100);
    tt.timeTestsForBruteForce(gtt, "9_miast.txt", 9, weightMatrixGlobal, 100);
    tt.timeTestsForBruteForce(gtt, "10_miast.txt", 10, weightMatrixGlobal, 100);
    tt.timeTestsForBruteForce(gtt, "11_miast.txt", 11, weightMatrixGlobal, 100);
    tt.timeTestsForBruteForce(gtt, "12_miast.txt", 12, weightMatrixGlobal, 100);
    tt.timeTestsForBruteForce(gtt, "13_miast.txt", 13, weightMatrixGlobal, 30);*/
    cout << "KONIEC TESTÓW" << endl;
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

    cout << "Projekt PEA    Kajetan Krasoń    252767" << endl << endl;

    do {
        cout << "1. Wczytaj strukturę z pliku i ją pokaż." << endl;
        cout << "2. Pokaż wczytaną strukturę." << endl;
        cout << "3. Rozwiąż problem komiwojażera na wczytanej strukturze  - symulowane wyżarzanie." << endl;
        cout << "4. Rozwiąż problem komiwojażera na wczytanej strukturze  - tabu search." << endl;
        cout << "5. Testy. " << endl;
        cout << "6. Opuść program. " << endl;
        cin >> menuOperation;

        switch (menuOperation)
        {
        case 1:
            cout << "Podaj nazwę pliku (plik txt, bez rozszerzenia): " << endl;
            cin >> fileName;
            fileName.append(".txt");
            //checker = g.fileReadGraph(fileName, false, numberOfCitiesGlobal, weightMatrixGlobal);
            break;
        case 2:
            cout << "Odległości między miastami:" << endl << endl;
            showWeightMatrix(numberOfCitiesGlobal, weightMatrixGlobal);
            break;
        case 3:
            break;
        case 4:
            cout << endl;
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