#include "Menu.h"
#include "../Structures/Matrix.h"
#include "../Utils/ReadFile.h"
#include "../Utils/GenerateMatrix.h"
#include "../Algorithms/Algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Konstruktor odpowiedzialny za inicjalizacje domyslnych wartosci zmiennych
Menu::Menu() {
    generateData = false;
    inputFile = "";
    instanceSize = 0;
    displayMatrix = false;
    iterations = 0;
    algorithm = "";
    outputFile = "";
    randomIterations = 0;
    progressBar = false;
    showResults = 0;
    timer = 0;
}

// Glowna metoda odpowiedzialna za wykonanie programu na podstawie wczytanej konfiguracji
void Menu::run() {
    loadConfig("config.txt");  // Wczytanie konfiguracji z pliku config.txt

    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych

    Matrix matrix(instanceSize);  // Tworzenie macierzy o rozmiarze instanceSize

    if (!generateData) {
        ReadFile fileReader;
        try {
            fileReader.loadData(inputFile, matrix);  // Wczytanie danych do macierzy z pliku
        } catch (const runtime_error& e) {
            cerr << e.what() << endl;
            return;
        }
    }

    GenerateMatrix generator;  // Tworzenie obiektu generatora losowych danych

    Algorithms algorithms;  // Tworzenie obiektu klasy z algorytmami

    timer = 0;
    for (int i = 0; i < iterations; ++i) {

        // Wypelnienie macierzy losowymi danymi dla kazdej iteracji
        if (generateData) {
            generator.fillRandom(matrix);
        }

        // Wyswietlanie macierzy
        if (displayMatrix) {
            matrix.display();
        }
            vector<int> bestPath;
            int minCost = 0;

            // Uruchomienie wybranego algorytmu na podstawie parametru algorithm
            if (algorithm == "brute_force") {
                start = high_resolution_clock::now();
                minCost = algorithms.bruteForce(matrix, bestPath);
                stop = high_resolution_clock::now();

            } else if (algorithm == "nearest_neighbor") {
                start = high_resolution_clock::now();
                minCost = algorithms.nearestNeighbor(matrix, bestPath);
                stop = high_resolution_clock::now();

            } else if (algorithm == "random") {
                start = high_resolution_clock::now();
                minCost = algorithms.randomAlgorithm(matrix, bestPath, randomIterations);
                stop = high_resolution_clock::now();

            } else {
                cerr << "Blad: Nieznany algorytm!" << endl;
                return;
            }

            timer += duration_cast<duration<double, milli>>(stop - start).count();

        if (showResults) {
            // Wyswietlenie wynikow
            cout << "Minimalny koszt trasy: " << minCost << endl;
            cout << "Najlepsza trasa: ";
            for (int city: bestPath) {
                cout << city << " ";
            }
            cout << endl << endl << endl;
        }
    }
    cout << "Algorytm " << algorithm << ", dla macierzy o rozmiarze: " << instanceSize << ", sredni czas: " << timer / iterations << " ms\n";

}

// Metoda odpowiedzialna za wczytywanie konfiguracji z pliku konfiguracyjnego
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

        string value = extractValue(line);  // Wyciąganie wartosci po znaku "="

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
                if (!value.empty()) {
                    randomIterations = stoi(value);
                }
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
            case 9:
                showResults = (value == "1");
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
        return line.substr(tmp + 1);
    }
    return "";
}
