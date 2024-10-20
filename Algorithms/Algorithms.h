#ifndef PROJEKT_PEA_1_ALGORITHMS_H
#define PROJEKT_PEA_1_ALGORITHMS_H

#include "../Structures/Matrix.h"
#include <vector>

class Algorithms {
public:
    // Metoda przeglądu zupelnego (brute force) dla problemu TSP
    int bruteForce(const Matrix& matrix, std::vector<int>& bestPath);

    // Metoda algorytmu najbliższych sasiadow dla problemu TSP
    int nearestNeighbor(const Matrix& matrix, std::vector<int>& bestPath);

private:
    // Pomocnicza metoda do obliczenia sumy kosztow dla danej permutacji trasy
    int calculatePathCost(const Matrix& matrix, const std::vector<int>& path);

    // Rekurencyjna funkcja do generowania wszystkich permutacji
    void generatePermutations(int n, std::vector<int>& cities, const Matrix& matrix, std::vector<int>& bestPath, int& minCost);
};

#endif

