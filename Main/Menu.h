/*
 * Klasa Menu odpowiedzialna jest za pobranie danych z pliku konfiguracyjnego,
 *
 *
 */

#ifndef PROJEKT_PEA_1_MENU_H
#define PROJEKT_PEA_1_MENU_H

#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Menu {
public:
    Menu();  // Konstruktor
    void run();  // Glowna metoda uruchamiajaca dzialanie klasy
    void loadConfig(const string& configFile);  // Wczytuje dane z pliku konfiguracyjnego

private:
    // Zmienne przechowujące dane z pliku konfiguracyjnego
    bool generateData;
    string inputFile;
    int instanceSize;
    bool displayMatrix;
    int iterations;
    int instanceIterations;
    string algorithm;
    string outputFile;
    bool progressBar;
    high_resolution_clock::time_point start, stop;  // Punkty czasowe do mierzenia czasu wykonania
    double timer;  // Zmienna do przechowywania zmierzonego czasu

    string extractValue(const string& line); // Pomocnicza metoda do wyciagania wartosci po "="
};

#endif

