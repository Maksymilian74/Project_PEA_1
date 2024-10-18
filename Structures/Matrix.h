#ifndef PROJEKT_PEA_1_MATRIX_H
#define PROJEKT_PEA_1_MATRIX_H

#include <iostream>
#include <iomanip>
#include <stdexcept>

class Matrix {
private:
    int size;        // Rozmiar macierzy
    int** matrix;    // Macierz kosztow

public:
    // Konstruktor
    Matrix(int n);

    // Destruktor
    ~Matrix();

    // Metoda do wyswietlania macierzy
    void display() const;

    // Metoda do pobierania wartosci z macierzy
    int getCost(int i, int j) const;

    // Metoda do ustawiania wartosci w macierzy
    void setCost(int i, int j, int cost);

    // Getter zwracajacy rozmiar macierzy
    int getSize() const;
};

#endif
