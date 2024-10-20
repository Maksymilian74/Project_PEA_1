/*
 * Klasa ReadFile odpowiedzialna jest za wczytywanie danych
 * z pliku tekstowego do macierzy, zapisuje dane
 * do odpowiednich komorek macierzy.
 */

#ifndef PROJEKT_PEA_1_READFILE_H
#define PROJEKT_PEA_1_READFILE_H

#include <string>
#include "../Structures/Matrix.h"

class ReadFile {
public:
    // Metoda odpowiedzialna za wczytywanie danych z pliku do macierzy
    void loadData(const std::string& filename, Matrix& matrix);
};

#endif
