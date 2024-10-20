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
    timer = 0;
}

void Menu::run() {
    // Wczytanie konfiguracji z pliku config.txt
    loadConfig("config.txt");

    srand(time(nullptr));

    // Algorytm przechodzi przez iterations głównych pętli
    timer = 0;
    for (int i = 0; i < iterations; ++i) {
        Matrix matrix(instanceSize);  // Tworzymy macierz o rozmiarze instance_size

        if (generateData) {
            // Wypełniamy macierz losowymi danymi
            GenerateMatrix generator;
            generator.fillRandom(matrix);  // Generujemy losowe dane
            cout << "Wygenerowano losowe dane dla macierzy." << endl;
        } else {
            // Wczytanie danych do macierzy z pliku
            ReadFile fileReader;
            try {
                fileReader.loadData(inputFile, matrix);
                cout << "Wczytano dane z pliku: " << inputFile << endl;
            } catch (const std::runtime_error& e) {
                cerr << e.what() << endl;
                return;  // Zakoncz program, jesli nie uda sie wczytac danych
            }
        }

        // Wyświetlanie macierzy, jeśli display_matrix jest ustawione na 1
        if (displayMatrix) {
            matrix.display();
        }

        // Pętla zależna od instance_iterations (dla tej samej macierzy)
        for (int j = 0; j < instanceIterations; ++j) {
            vector<int> bestPath;
            int minCost = 0;

            Algorithms algorithms;

            // Wybrany algorytm na podstawie parametru algorithm
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
                minCost = algorithms.randomAlgorithm(matrix, bestPath, 100);  // Przykladowo 100 iteracji w algorytmie losowym
                stop = high_resolution_clock::now();
                cout << "Algorytm losowy." << endl;
            } else {
                cerr << "Blad: Nieznany algorytm!" << endl;
                return;  // Zakonczenie programu, jesli algorytm jest nieznany
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
