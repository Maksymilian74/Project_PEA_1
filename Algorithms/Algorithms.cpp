#include "Algorithms.h"
#include <climits>  // Dla INT_MAX
#include <iostream>
#include <cstdlib>

using namespace std;

// Metoda bruteForce do znajdowania najkrotszej trasy
int Algorithms::bruteForce(const Matrix& matrix, vector<int>& bestPath) {
    int size = matrix.getSize();
    vector<int> cities(size);  // Wektor miast
    for (int i = 0; i < size; ++i) {
        cities[i] = i;  // Wypelniamy miastami od 0 do (size - 1)
    }

    int minCost = INT_MAX;  // Inicjalizacja minimalnego kosztu na najwieksza mozliwa wartosc

    // Generowanie permutacji i sprawdzanie kosztow
    generatePermutations(size, cities, matrix, bestPath, minCost);

    return minCost;  // Zwracamy minimalny koszt
}

// Metoda algorytmu najblizszych sasiadow (nearest neighbor)
int Algorithms::nearestNeighbor(const Matrix& matrix, vector<int>& bestPath) {
    int size = matrix.getSize();
    vector<bool> visited(size, false);  // Wektor sledzacy, ktore miasta zostaly odwiedzone
    bestPath.clear();
    int totalCost = 0;

    // Startujemy z miasta o indeksie 0
    int currentCity = 0;
    bestPath.push_back(currentCity);
    visited[currentCity] = true;

    // Szukamy najblizszych sasiadow dla wszystkich miast
    for (int step = 1; step < size; ++step) {
        int nearestCity = -1;
        int minCost = INT_MAX;

        // Szukamy najblizszego miasta, ktore nie zostalo jeszcze odwiedzone
        for (int j = 0; j < size; ++j) {
            if (!visited[j]) {  // Miasto nie zostalo jeszcze odwiedzone
                int cost = matrix.getCost(currentCity, j);
                if (cost != -1 && cost < minCost) {
                    nearestCity = j;
                    minCost = cost;
                }
            }
        }

        // Jesli znalezlismy miasto, przechodzimy do niego
        if (nearestCity != -1) {
            bestPath.push_back(nearestCity);
            visited[nearestCity] = true;
            totalCost += minCost;
            currentCity = nearestCity;
        } else {
            // Jesli nie znalezlismy zadnego miasta, cos poszlo nie tak
            cerr << "Blad: Nie znaleziono najbliższego sąsiada!" << endl;
            return INT_MAX;
        }
    }

    // Powrot do miasta początkowego
    int returnCost = matrix.getCost(currentCity, bestPath[0]);
    if (returnCost == -1) {
        return INT_MAX;
    }
    totalCost += returnCost;
    bestPath.push_back(bestPath[0]);  // Zakonczenie cyklu

    return totalCost;
}

// Metoda losowego algorytmu
int Algorithms::randomAlgorithm(const Matrix& matrix, vector<int>& bestPath, int iterations) {
    int size = matrix.getSize();
    int minCost = INT_MAX;  // Inicjalizacja minimalnego kosztu na najwieksza mozliwa wartosc

    // Seed do generatora losowego
    srand(static_cast<unsigned int>(time(nullptr)));

    // Powtarzamy algorytm losowy przez okreslona liczbe iteracji
    for (int iter = 0; iter < iterations; ++iter) {
        vector<int> cities;  // Przechowuje losowa trase
        vector<bool> visited(size, false);  // Sledzi odwiedzone miasta

        int currentCity = 0;  // Zaczynamy od miasta 0
        cities.push_back(currentCity);
        visited[currentCity] = true;  // Oznaczamy miasto 0 jako odwiedzone

        // Budujemy losowa trase, wybierajac kolejne miasta
        for (int step = 1; step < size; ++step) {
            vector<int> remainingCities;  // Miasta jeszcze nieodwiedzone
            for (int i = 0; i < size; ++i) {
                if (!visited[i]) {
                    remainingCities.push_back(i);
                }
            }

            // Losowo wybieramy jedno z pozostalych nieodwiedzonych miast
            if (remainingCities.empty()) {
                cerr << "Blad: Brak dostepnych miast do odwiedzenia!" << endl;
                return -1;  // Nieprawidlowy stan
            }

            int nextCity = remainingCities[rand() % remainingCities.size()];
            cities.push_back(nextCity);
            visited[nextCity] = true;  // Oznaczamy wybrane miasto jako odwiedzone
        }

        // Obliczanie kosztu dla losowej trasy
        int currentCost = calculatePathCost(matrix, cities);

        // Sprawdzanie, czy obliczony koszt trasy jest mniejszy od aktualnego minimalnego kosztu
        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = cities;  // Zapisujemy najlepsza trase
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
            return INT_MAX;  // Jesli koszt między miastami jest -1, traktujemy to jako brak polaczenia
        }
        totalCost += cost;
    }

    // Dodajemy koszt powrotu do miasta poczatkowego
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
            bestPath = cities;  // Zapisujemy najlepsza trase
        }
    } else {
        for (int i = 0; i < n; ++i) {
            generatePermutations(n - 1, cities, matrix, bestPath, minCost);

            if (n % 2 == 0) {
                swap(cities[i], cities[n - 1]);  // Zamiana dla permutacji
            } else {
                swap(cities[0], cities[n - 1]);  // Zamiana dla permutacji
            }
        }
    }
}
