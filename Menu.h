#ifndef PROJEKT_PEA_1_MENU_H
#define PROJEKT_PEA_1_MENU_H

#include <iostream>

using namespace std;

class Menu {
public:
    // Metoda odpowiedzialna za uruchomienie glownego menu
    void runMainMenu();

private:
    // Metoda wyswietlajaca menu glowne
    int displayMainMenu();

    // Metoda wyswietlajaca menu dla trybu testowego
    int displayTestingMenu();

    // Metoda wyswietlajaca menu dla wyboru algorytmu
    int displayAlgorithmMenu();

    // Metoda wyswietlajaca menu dla trybu badawczego
    int displaySimulationMenu();
};

#endif
