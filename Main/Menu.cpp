#include "Menu.h"
#include "../Structures/Matrix.h"
#include "../Utils/ReadFile.h"
#include "../Utils/GenerateMatrix.h"
#include "../Algorithms/Algorithms.h"
#include <iostream>
#include <fstream>

using namespace std;

Menu::Menu() {
    // Inicjalizacja domyslnych wartosci zmiennych
    generateData = false;
    inputFile = "";
    instanceSize = 0;
    displayMatrix = false;
    iterations = 0;
    algorithm = "";
    outputFile = "";
    instanceIterations = 0;
    progressBar = false;
}

void Menu::run() {
    // Wczytanie konfiguracji z pliku config.txt
    loadConfig("config.txt");

    // Stworzenie macierzy o rozmiarze instanceSize
    Matrix matrix(instanceSize);
//    GenerateMatrix generator;
//    generator.fillRandom(matrix);  // Generujemy losowe dane bez potrzeby podawania maxCost
//    cout << "Wygenerowano losowe dane dla macierzy." << endl;

    // Wczytanie danych do macierzy
    ReadFile fileReader;
    try {
        fileReader.loadData(inputFile, matrix);
    } catch (const std::runtime_error& e) {
        cerr << e.what() << endl;
        return;  // Zakoncz program, jesli nie uda sie wczytac danych
    }

    // Opcjonalne wyswietlenie macierzy, jesli w konfiguracji jest ustawione
    if (displayMatrix) {
        matrix.display();

        // Wywolanie wybranego algorytmu
        Algorithms algorithms;
        vector<int> bestPath;
        int minCost = 0;

        if (algorithm == "brute_force") {
            minCost = algorithms.bruteForce(matrix, bestPath);
            cout << "Algorytm przeglądu zupełnego (Brute Force)." << endl;
        } else if (algorithm == "nearest_neighbor") {
            minCost = algorithms.nearestNeighbor(matrix, bestPath);
            cout << "Algorytm najbliższych sąsiadów." << endl;
        }

        // Wyswietlenie wyników
        cout << "Minimalny koszt trasy: " << minCost << endl;
        cout << "Najlepsza trasa: ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
    }

//    // Wyswietlanie wczytanych wartosci
//    cout << "--- Wczytane dane z pliku konfiguracyjnego ---" << endl;
//    cout << "Generowanie danych: " << (generateData ? "Tak" : "Nie") << endl;
//    cout << "Plik wejsciowy: " << inputFile << endl;
//    cout << "Rozmiar instancji: " << instanceSize << endl;
//    cout << "Wyswietlanie macierzy: " << (displayMatrix ? "Tak" : "Nie") << endl;
//    cout << "Liczba iteracji: " << iterations << endl;
//    cout << "Algorytm: " << algorithm << endl;
//    cout << "Plik wyjsciowy: " << outputFile << endl;
//    cout << "Liczba iteracji dla instancji: " << instanceIterations << endl;
//    cout << "Pasek postepu: " << (progressBar ? "Tak" : "Nie") << endl;
}

void Menu::loadConfig(const string& configFile) {
    ifstream file(configFile);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku konfiguracyjnego: " << configFile << endl;
        return;
    }

    string line;
    int lineCount = 0;

    while (getline(file, line)) {
        // Pomijanie komentarzy i pustych linii
        if (line.empty() || line[0] == '#') {
            continue;
        }

        string value = extractValue(line);  // Wyciągamy wartosc po znaku "="

        // Przypisanie wartosci na podstawie numeru linii
        switch (lineCount) {
            case 0:
                generateData = (value == "1");
                break;
            case 1:
                inputFile = value;
                break;
            case 2:
                instanceSize = stoi(value);
                break;
            case 3:
                displayMatrix = (value == "1");
                break;
            case 4:
                iterations = stoi(value);
                break;
            case 5:
                instanceIterations = stoi(value);
                break;
            case 6:
                algorithm = value;
                break;
            case 7:
                outputFile = value;
                break;
            case 8:
                progressBar = (value == "1");
                break;
        }

        lineCount++;
    }

    file.close();
}

// Pomocnicza metoda do wyciagania wartosci po znaku "="
string Menu::extractValue(const string& line) {
    size_t tmp = line.find("=");
    if (tmp != string::npos) {
        return line.substr(tmp + 2);  // Zwracamy to, co po "="
    }
    return "";  // W przypadku bledu
}
