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
    instanceIterations = 0;
    progressBar = false;
    timer = 0;
}

// Glowna metoda odpowiedzialna za wykonanie programu na podstawie wczytanej konfiguracji
void Menu::run() {
    loadConfig("config.txt");  // Wczytanie konfiguracji z pliku config.txt

    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych

    timer = 0;
    for (int i = 0; i < iterations; ++i) {
        Matrix matrix(instanceSize);  // Tworzebie macierzy o rozmiarze instanceSize

        if (generateData) {
            GenerateMatrix generator;
            generator.fillRandom(matrix);  // Generowanie losowych danych
            cout << "Wygenerowano losowe dane dla macierzy." << endl;
        } else {
            ReadFile fileReader;
            try {
                fileReader.loadData(inputFile, matrix);  // Wczytanie danych do macierzy z pliku
                cout << "Wczytano dane z pliku: " << inputFile << endl;
            } catch (const std::runtime_error& e) {
                cerr << e.what() << endl;
                return;
            }
        }

        // Wyświetlanie macierzy, jeśli display_matrix jest ustawione na 1
        if (displayMatrix) {
            matrix.display();
        }

        for (int j = 0; j < instanceIterations; ++j) {
            vector<int> bestPath;
            int minCost = 0;

            Algorithms algorithms;

            // Uruchomienie wybranego algorytmu na podstawie parametru algorithm
            if (algorithm == "brute_force") {
                start = high_resolution_clock::now();
                minCost = algorithms.bruteForce(matrix, bestPath);
                stop = high_resolution_clock::now();
                cout << "Algorytm przegladu zupelnego." << endl;

            } else if (algorithm == "nearest_neighbor") {
                start = high_resolution_clock::now();
                minCost = algorithms.nearestNeighbor(matrix, bestPath);
                stop = high_resolution_clock::now();
                cout << "Algorytm najblizszych sasiadow." << endl;

            } else if (algorithm == "random") {
                start = high_resolution_clock::now();
                minCost = algorithms.randomAlgorithm(matrix, bestPath, 100);
                stop = high_resolution_clock::now();
                cout << "Algorytm losowy." << endl;

            } else {
                cerr << "Blad: Nieznany algorytm!" << endl;
                return;
            }

            timer += duration_cast<duration<double, milli>>(stop - start).count();

            // Wyświetlenie wyników
            cout << "Minimalny koszt trasy: " << minCost << endl;
            cout << "Najlepsza trasa: ";
            for (int city : bestPath) {
                cout << city << " ";
            }
            cout << endl << endl << endl;
        }
    }
    cout << "Algorytm " << algorithm << " sredni czas: " << timer / iterations << " ms\n";

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
        return line.substr(tmp + 2);
    }
    return "";
}
