#include "Matrix.h"

// Konstruktor
Matrix::Matrix(int n) : size(n) {
    // Alokacja pamięci dla macierzy
    matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = -1; // Domyślna wartość dla macierzy kosztów
        }
    }
}

// Destruktor
Matrix::~Matrix() {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Metoda do wyświetlania macierzy
void Matrix::display() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == -1) {
                std::cout << " -1 ";
            } else {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Metoda do pobierania wartości z macierzy
int Matrix::getCost(int i, int j) const {
    if (i < 0 || i >= size || j < 0 || j >= size) {
        throw std::out_of_range("Indeks poza zakresem macierzy");
    }
    return matrix[i][j];
}

// Metoda do ustawiania wartości w macierzy
void Matrix::setCost(int i, int j, int cost) {
    if (i < 0 || i >= size || j < 0 || j >= size) {
        throw std::out_of_range("Indeks poza zakresem macierzy");
    }
    matrix[i][j] = cost;
}

// Getter zwracający rozmiar macierzy
int Matrix::getSize() const {
    return size;
}
