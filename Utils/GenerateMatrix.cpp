#include "GenerateMatrix.h"
#include <cstdlib>

void GenerateMatrix::fillRandom(Matrix& matrix) {
    int size = matrix.getSize();  // Pobieramy rozmiar macierzy
    const int maxCost = 100;  // Stala wartosc maksymalnego kosztu

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                matrix.setCost(i, j, -1);  // Na przekątnej ustawiamy -1
            } else {
                int cost = std::rand() % maxCost + 1;  // Losujemy wartosc z zakresu [1, maxCost]
                matrix.setCost(i, j, cost);  // Ustawiamy koszt
            }
        }
    }
}
