#include "GenerateMatrix.h"
#include <cstdlib>  // Dla funkcji rand()
#include <ctime>    // Dla funkcji time()

void GenerateMatrix::fillRandom(Matrix& matrix) {
    int size = matrix.getSize();  // Pobieramy rozmiar macierzy
    const int maxCost = 100;  // Stała wartosc maksymalnego kosztu

    // Ustawiamy seed dla generatora losowego (raz na start programu)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

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
