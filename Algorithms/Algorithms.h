/*
 * Klasa Algorithms odpowiedzialna jest za implementacje trzech
 * algorytmow rozwiazywania problemu komiwojazera oraz metod pomocniczych
 * do obliczania kosztu podanej trasy oraz generowania permutacji
 */

#ifndef PROJEKT_PEA_1_ALGORITHMS_H
#define PROJEKT_PEA_1_ALGORITHMS_H

#include "../Structures/Matrix.h"
#include <vector>

using namespace std;

class Algorithms {
public:
    // Metoda bruteForce odpowiedzialna za znajdowanie najkrotszej trasy
    int bruteForce(const Matrix& matrix, vector<int>& bestPath);

    // Metoda algorytmu najblizszych sasiadow
    int nearestNeighbor(const Matrix& matrix, vector<int>& bestPath);

    // Metoda losowego algorytmu
    int randomAlgorithm(const Matrix& matrix, vector<int>& bestPath, int iterations);

private:
    // Pomocnicza metoda do obliczenia sumy kosztow dla danej permutacji trasy
    int calculatePathCost(const Matrix& matrix, const vector<int>& path);

    // Rekurencyjna funkcja odpowiedzialna za generowanie wszystkich permutacji
    void generatePermutations(int n, vector<int>& cities, const Matrix& matrix, vector<int>& bestPath, int& minCost);
};

#endif

