#include "ReadFile.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Metoda odpowiedzialna za wczytywanie danych z pliku
void ReadFile::loadData(const string& filename, Matrix& matrix) {
    ifstream file(filename);  // Otwarcie pliku do odczytu
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << filename << endl;  // Wyswietlenie bledu, jesli pliku nie mozna otworzyc
        throw runtime_error("Blad: Nie mozna otworzyc pliku");
    }

    int size;
    file >> size;  // Wczytanie rozmiaru macierzy z pliku

    // Sprawdzenie, czy rozmiar macierzy z pliku pasuje do rozmiaru macierzy w programie
    if (size != matrix.getSize()) {
        cerr << "Blad: Rozmiar macierzy z pliku nie pasuje do rozmiaru macierzy w programie" << endl;
        throw runtime_error("Blad: Nieprawidlowy rozmiar macierzy");
    }

    // Wczytanie danych z pliku do macierzy
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int cost;
            file >> cost;  // Wczytanie kosztu z pliku
            matrix.setCost(i, j, cost);  // Ustawienie kosztu w macierzy
        }
    }

    file.close();  // Zamkniecie pliku po wczytaniu danych
}
