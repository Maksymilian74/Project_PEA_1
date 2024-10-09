#include "Menu.h"
#include "Simulation.h"
#include "Test.h"

#include <iostream>

using namespace std;

void Menu::runMainMenu() { // Implementacja glownego menu
    int number;
    int testNumber;
    int simulationNumber;
    int algorithm;
    int vertices;
    string fileToOpen;
    Test* test = nullptr;
    Simulation* simulation = nullptr;

    do {
        number = displayMainMenu(); // Wyswietlenie glownego menu
        switch (number) {
            case 1:
                cout << "-------------------------------------------\n";
                cout << "Tryb pracy testowej\n";
                test = new Test(); // Utworzenie obiektu klasy Test
                do {
                    testNumber = displayTestingMenu(); // Wyswieltenie menu dla trybu testowania
                    switch (testNumber) {
                        case 1:
                            cout << "-------------------------------------------\n";
                            cout << "Wczytanie danych z pliku\n";
                            cout << "Podaj nazwe pliku z rozszerzeniem\n";
                            cin >> fileToOpen;
                            //test->loadDataFromFile(fileToOpen);
                            break;
                        case 2:
                            cout << "-------------------------------------------\n";
                            cout << "Wygenerowanie losowych danych\n";
                            cout << "Podaj liczbe wierzcholkow\n";
                            cin >> vertices;
                            //test->generateRandomGraph(vertices);
                            break;
                        case 3:
                            cout << "-------------------------------------------\n";
                            cout << "Wyswietlenie macierzy\n";
                            //test->displayGraph();
                            break;
                        case 4:
                            cout << "-------------------------------------------\n";
                            cout << "Algorytm przegladu zupelnego\n";
                            //test->algorithm3();
                            break;
                        case 5:
                            cout << "Algorytm najblizszych sasiadow\n";
                            //test->algorithm2();
                            break;
                        case 6:
                            cout << "-------------------------------------------\n";
                            cout << "Algorytm losowy\n";
                            //test->algorithm1();
                            break;
                        case 7:
                            cout << "-------------------------------------------\n";
                            cout << "Wyjscie do wyboru trybu pracy  \n";
                            break;
                        default:
                            cout << "-------------------------------------------\n";
                            cout << "Bledny numer, podaj prawidlowa wartosc\n";
                            break;
                    }
                } while(testNumber != 7);
                delete test;  // Zwolnieni pamieci po obiekcie Test
                test = nullptr; // Ustawienie wskaznika na nullptr
                break;
            case 2:
                cout << "-------------------------------------------\n";
                cout << "Tryb pracy badawczej\n";
                simulation = new Simulation(); // Utworzenie obiektu klasy Simulation
                do {
                    simulationNumber = displaySimulationMenu(); // Wyswietlenie menu dla trybu badawczego
                    switch (simulationNumber) {
                        case 1:
                            cout << "-------------------------------------------\n";
                            cout << "Wybor algorytmu\n";
                            algorithm = displayAlgorithmMenu(); // Wyswietlenie menu do wyboru problemu badawczego
                            //simulation->testAlgorithm(algorithm);
                            break;
                        case 2:
                            cout << "-------------------------------------------\n";
                            cout << "Wyjscie do wyboru trybu pracy  \n";
                            break;
                        default:
                            cout << "-------------------------------------------\n";
                            cout << "Bledny numer, podaj prawidlowa wartosc\n";
                            break;
                    }
                } while(simulationNumber != 2);
                delete simulation;  // Zwolnieni pamieci po obiekcie Simulation
                simulation = nullptr; // Ustawienie wskaznika na nullptr
                break;
            case 3:
                cout << "-------------------------------------------\n";
                cout << "Zakonczenie dzialania programu\n";
                break;
            default:
                cout << "-------------------------------------------\n";
                cout << "Bledny numer, podaj prawidlowa wartosc\n";
                break;
        }
    } while (number != 3);


}

int Menu::displayMainMenu() { // Implementacja wyswietlania glownego menu
    int task;
    cout << "---------------------------\n";
    cout << "     --- Main Menu ---     \n";
    cout << "1. Tryb pracy testowej     \n";
    cout << "2. Tryb pracy badawczej    \n";
    cout << "3. Wyjscie                 \n";
    cout << "Wpisz numer zadania:";
    cin >> task;
    return task;
}

int Menu::displayTestingMenu() { // Implementacja wyswietlania menu dla trybu testowego
    int task;
    cout << "------------------------------------------------\n";
    cout << "            --- Testing Menu ---                \n";
    cout << "1. Wczytanie danych z pliku                     \n";
    cout << "2. Wygenerowanie losowych danych                \n";
    cout << "3. Wyswietlenie macierzy                        \n";
    cout << "4. Uruchom algorytm przegladu zupelnego         \n";
    cout << "5. Uruchom algorytm najblizszych sasiadow       \n";
    cout << "6. Uruchom algorytm losowy                      \n";
    cout << "7. Wyjscie do wyboru trybu pracy                \n";
    cout << "Wpisz numer zadania:";
    cin >> task;
    return task;
}

int Menu::displaySimulationMenu() { // Implementacja wyswietlania menu dla trybu badawczego
    int task;
    cout << "---------------------------------- \n";
    cout << "      --- Simulation Menu ---      \n";
    cout << "1. Wybor algorytmu                 \n";
    cout << "2. Wyjscie do wyboru trybu pracy   \n";
    cout << "Wpisz numer zadania:";
    cin >> task;
    return task;
}

int Menu::displayAlgorithmMenu() { // Implementacja wyswietlania menu do wyboru algorytmu
    int task;
    cout << "------------------------------------------------\n";
    cout << "           --- Algorithm Menu ---               \n";
    cout << "1. Uruchom algorytm przegladu zupelnego         \n";
    cout << "2. Uruchom algorytm najblizszych sasiadow       \n";
    cout << "3. Uruchom algorytm losowy                      \n";
    cout << "Wpisz numer zadania:";
    cin >> task;
    return task;
}
