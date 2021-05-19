#pragma once
#include "cases.h"
 class grille
{
protected:
    int taille;
    int tableau[32];
    cases a[8][8];
public:


    grille(int a=4)
    {
        taille = a;
    }

    void printGrille();
    int getTaille()
    {
        return taille;
    }
    void setTaille(int a)
    {
        taille = a;
    }
    void deleteGrille();
    void initializeGrillequartquart();
    void initializeGrillesixsix();
    void initializeGrillehuithuit();
    //int  inittableau();
    ~grille(){}
};
