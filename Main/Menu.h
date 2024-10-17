/*
 * Klasa Menu odpowiedzialna jest za pobranie danych z pliku konfiguracyjnego,
 *
 *
 */

#ifndef PROJEKT_PEA_1_MENU_H
#define PROJEKT_PEA_1_MENU_H

#include <string>
using namespace std;

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

    string extractValue(const string& line); // Pomocnicza metoda do wyciagania wartosci po "="
};

#endif

