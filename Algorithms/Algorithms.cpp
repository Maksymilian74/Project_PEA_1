#include "Algorithms.h"
#include <climits>
#include <iostream>
#include <cstdlib>

using namespace std;

// Metoda bruteForce odpowiedzialna za znajdowanie najkrotszej trasy
int Algorithms::bruteForce(const Matrix& matrix, vector<int>& bestPath) {
    int size = matrix.getSize();
    vector<int> cities(size);  // Wektor miast
    for (int i = 0; i < size; ++i) {
        cities[i] = i;
    }

    int minCost = INT_MAX;  // Inicjalizacja minimalnego kosztu na najwieksza mozliwa wartosc

    // Generowanie permutacji i sprawdzanie kosztow trasy dla kazdej permutacji
    generatePermutations(size, cities, matrix, bestPath, minCost);

    return minCost;
}

// Metoda algorytmu najblizszych sasiadow
int Algorithms::nearestNeighbor(const Matrix& matrix, vector<int>& bestPath) {
    int size = matrix.getSize();
    vector<bool> visited(size, false);  // Wektor sledzacy odwiedzone miasta
    bestPath.clear();
    int totalCost = 0;

    int currentCity = 0;
    bestPath.push_back(currentCity);
    visited[currentCity] = true;

    // Szukanie najblizszych sasiadow dla wszystkich miast
    for (int step = 1; step < size; ++step) {
        int nearestCity = -1;
        int minCost = INT_MAX;

        // Szukanie najblizszego miasta, ktore nie zostalo jeszcze odwiedzone
        for (int j = 0; j < size; ++j) {
            if (!visited[j]) {
                int cost = matrix.getCost(currentCity, j);
                if (cost != -1 && cost < minCost) {
                    nearestCity = j;
                    minCost = cost;
                }
            }
        }

        // Jesli znaleziono najblizsze miasto, przejscie do niego
        if (nearestCity != -1) {
            bestPath.push_back(nearestCity);
            visited[nearestCity] = true;
            totalCost += minCost;
            currentCity = nearestCity;
        } else {
            cerr << "Blad: Nie znaleziono najbliższego sąsiada!" << endl;
            return INT_MAX;
        }
    }

    // Powrot do miasta poczatkowego
    int returnCost = matrix.getCost(currentCity, bestPath[0]);
    if (returnCost == -1) {
        return INT_MAX;
    }
    totalCost += returnCost;
    bestPath.push_back(bestPath[0]);  // Zakonczenie cyklu

    return totalCost;
}

// Metoda losowego algorytmu
int Algorithms::randomAlgorithm(const Matrix& matrix, vector<int>& bestPath, int randomIterations) {
    int size = matrix.getSize();

    // Obliczenie liczby wszystkich mozliwych permutacji
    int totalPermutations = factorial(size - 1);

    // Obliczenie liczby iteracji jako procent wszystkich mozliwych permutacji
    int iterations = (totalPermutations * randomIterations) / 100;

    int minCost = INT_MAX;  // Inicjalizacja minimalnego kosztu na najwieksza mozliwa wartosc

    for (int i = 0; i < iterations; ++i) {
        vector<int> cities;  // Vector odpowiedzialny za przechowywanie trasy
        vector<bool> visited(size, false);
        int currentCity = rand() % size;;
        cities.push_back(currentCity);
        visited[currentCity] = true;

        // Budowanie losowej trasy, wybierajac kolejne miasta
        for (int step = 1; step < size; ++step) {
            vector<int> remainingCities;  // Miasta jeszcze nieodwiedzone
            for (int i = 0; i < size; ++i) {
                if (!visited[i]) {
                    remainingCities.push_back(i);
                }
            }

            if (remainingCities.empty()) {
                cerr << "Blad: Brak dostepnych miast do odwiedzenia!" << endl;
                return -1;
            }

            int nextCity = remainingCities[rand() % remainingCities.size()];
            cities.push_back(nextCity);
            visited[nextCity] = true;  // Oznaczenie wybranego miasta jako odwiedzone
        }

        // Obliczanie kosztu dla losowej trasy
        int currentCost = calculatePathCost(matrix, cities);

        // Sprawdzenie, czy obliczony koszt trasy jest mniejszy od aktualnego minimalnego kosztu
        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = cities;
        }
    }

    return minCost;
}


// Pomocnicza metoda do obliczania kosztu dla danej permutacji trasy
int Algorithms::calculatePathCost(const Matrix& matrix, const vector<int>& path) {
    int totalCost = 0;
    int size = path.size();

    for (int i = 0; i < size - 1; ++i) {
        int cost = matrix.getCost(path[i], path[i + 1]);
        if (cost == -1) {
            return INT_MAX;
        }
        totalCost += cost;
    }

    int returnCost = matrix.getCost(path[size - 1], path[0]);
    if (returnCost == -1) {
        return INT_MAX;
    }
    totalCost += returnCost;

    return totalCost;
}

// Rekurencyjna funkcja do generowania permutacji
void Algorithms::generatePermutations(int n, vector<int>& cities, const Matrix& matrix, vector<int>& bestPath, int& minCost) {
    // Generowanie permutacji z rekurencja
    if (n == 1) {
        int currentCost = calculatePathCost(matrix, cities);
        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = cities;
        }
    } else {
        // Generowanie permutacji dla n-1 elementow
        for (int i = 0; i < n; ++i) {
            generatePermutations(n - 1, cities, matrix, bestPath, minCost);

            if (n % 2 == 0) {
                swap(cities[i], cities[n - 1]);
            } else {
                swap(cities[0], cities[n - 1]);
            }
        }
    }
}

// Pomocnicza metoda odpowiedzialna za obliczanie silni
int Algorithms::factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
