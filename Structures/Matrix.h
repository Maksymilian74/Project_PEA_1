#ifndef PROJEKT_PEA_1_MATRIX_H
#define PROJEKT_PEA_1_MATRIX_H

#include <iostream>
#include <iomanip>
#include <stdexcept>

class Matrix {
private:
    int size;        // Liczba miast (rozmiar macierzy)
    int** matrix;    // Macierz kosztów

public:
    // Konstruktor
    Matrix(int n);

    // Destruktor
    ~Matrix();

    // Metoda do wyświetlania macierzy
    void display() const;

    // Metoda do pobierania wartości z macierzy
    int getCost(int i, int j) const;

    // Metoda do ustawiania wartości w macierzy
    void setCost(int i, int j, int cost);

    // Getter zwracający rozmiar macierzy
    int getSize() const;
};

#endif
