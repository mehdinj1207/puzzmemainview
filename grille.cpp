#include "grille.h"
#include "grille.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <cmath>
#include"cases.h"
#include <windows.h>
#define RAND_MAX srand
using namespace std;

void grille::deleteGrille()
{
    int i = 0;
    do
    {
        int p, q;
      //  srand(time(NULL));
        p = rand() % taille;
        q = rand() % taille;
        if ((a[p][q].getValue() == 1) || (a[p][q].getValue() == 0))
        {
            a[p][q].setValue(2);
            i++;
        }
    }     while (i < pow(taille, 2) / 2);
}
 /*int   grille::inittableau()
{

    int k = 0;
    for (int i = 0; i < taille; i++)
        for (int j = 0; j < taille; j++)
            if (a[i][j].getcaseValue() == 2)
            {
                tableau[k] = a[i][j].getIdValue();
                k++;
            }
    return(k);
}*/
void grille::printGrille()
{
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            cout << "+---";
        }
        cout << "+" << endl;
        for (int j = 0; j < taille; j++)
        {
            if (a[i][j].getValue() == 1)
            {
                cout << "| 1 ";
            }
            else if (a[i][j].getValue() == 0)
            {
                cout << "| 0 ";
            }
            else
            {
                cout << "|   ";
            }
        }
        cout << "|" << endl;
    }
    for (int j = 0; j < taille; j++)
    {
        cout << "+---";
    }
    cout << "+" << endl;
}
void grille::initializeGrillequartquart()
{
    int table[3][4] = { {3,5,10,12},{5,6,9,10},{6,3,9,12} };
    int alea;
    alea = rand() % 3;
    int casestab[4];
    for (int i = 0; i < 4; i++)
    {
        casestab[i] = table[alea][i];
    }

    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        srand(time(NULL));
        int ons = rand() % (4 - i);
        int hello = casestab[ons];
        int k = 0;
        for (int j = 0; j < 4; j++)
        {
            a[i][j].setXy(x++,y++);

            a[i][j].setValue((hello >> k) % 2);
            k++;
        }//>> 9adah decalage
        int inc = 0;
        for (int j = 0; j < 4; j++)
        {
            if (j != ons)
            {
                casestab[inc] = casestab[j];
                inc++;
            }
        }
    }
 deleteGrille();
 {
     int k = 0;
     for (int i = 0; i < taille; i++)
         for (int j = 0; j < taille; j++)
             if (a[i][j].getValue() == 2)
             {
                 tableau[k] = a[i][j].getIdValue();
                 k++;
             }
 }
}
//--------------------------------taille6*6 ---------------------------------------------------
void grille::initializeGrillesixsix()
{
    int table[37][6] = { {22,37,25,38,41,26},
        {22,37,25,38,26,41},
        {22,37,25,42,52,11},
        {22,37,25,50,13,42},
        {22,37,25,50,44,11},
        {50,11,13,52,19,44},
        {50,11,13,52,42,21},
        {50,11,13,52,26,37},
        {50,11,44,19,13,52},
        {50,11,44,19,52,13},
        {50,11,44,22,41,21},
        {50,11,44,22,25,37},
        {50,11,44,52,19,13},
        {37,11,22,44,25,50},
        {37,11,22,52,41,26},
        {37,11,22,41,26,52},
        {37,11,22,41,52,26},
        {37,11,26,52,13,50},
        {37,11,26,52,41,22},
        {37,11,50,13,26,52},
        {37,11,50,13,52,26},
        {25,19,38,13,50,44},
        {25,19,38,41,22,44},
        {25,19,44,22,41,38},
        {25,19,44,50,13,38},
        {25,19,44,13,50,38},
        {25,19,44,41,22,38},
        {25,22,42,37,19,44},
        {25,22,42,13,50,37},
        {37,38,25,22,41,26},
        {37,38,25,42,21,26},
        {37,38,25,50,13,26},
        {37,38,25,13,50,26},
        {37,38,25,41,22,26},
        {37,38,25,21,42,26},
        {37,38,26,13,50,25},
        {37,38,26,41,22,25}
    };
    int alea;
    alea = rand() % 37;
    int casestab[6];
    for (int i = 0; i < 6; i++)
    {
        casestab[i] = table[alea][i];
    }

    int x = 0;
     int y = 0;
    for (int i = 0; i < 6; i++)
    {
        int k = 0;
        for (int j = 0; j < 6; j++)
        {
            a[i][j].setXy(x++,y++);
            {
                a[i][j].setValue((casestab[i] >> k) % 2);
                k++;
            }
        }

    }
    deleteGrille();
    {
        int k = 0;
        for (int i = 0; i < taille; i++)
            for (int j = 0; j < taille; j++)
                if (a[i][j].getValue() == 2)
                {
                    tableau[k] = a[i][j].getIdValue();
                    k++;
                }
    }
}
//------------------------------   grille 8*8 ----------------------------------------------------
void grille::initializeGrillehuithuit()
{
    int table[25][8] = { {153,54,202,77,178,108,147,101},
        {153,54,202,77,178,147,108,101},
        {153,54,202,101,178,77,108,147},
        {153,54,202,101,178,77,147,108},
        {153,54,202,101,147,108,77,178},
        {178,53,75,150,108,83,169,204},
        {178,53,75,150,108,169,83,204},
        {178,53,204,83,169,150,75,108},
        {178,53,204,83,169,150,108,75},
        {178,53,204,83,169,108,150,75},
        {150,108,169,83,204,178,53,75},
        {150,108,169,83,204,178,75,53},
        {150,108,169,83,204,53,178,75},
        {150,108,169,83,204,53,75,178},
        {150,108,75,178,53,204,83,169},
        {108,83,169,150,75,53,204,178},
        {108,83,169,150,75,53,178,204},
        {108,83,178,204,53,75,150,169},
        {108,169,83,204,178,53,75,150},
        {108,169,83,204,178,75,53,150},
        {54,202,77,178,153,108,147,101},
        {54,202,153,101,178,77,108,147},
        {54,202,153,101,178,77,147,108},
        {54,202,101,178,77,108,147,153},
        {54,202,101,178,77,147,108,153}
    };
    int alea;
    alea = rand() % 25;
    int casestab[8];
    for (int i = 0; i < 8; i++)
    {
        casestab[i] = table[alea][i];
    }

    int x = 0;
    int y=0 ;
    for (int i = 0; i < 8; i++)
    {
        int k = 0;
        for (int j = 0; j < 8; j++)
        {
            a[i][j].setXy(x++,y++);
            {
                a[i][j].setValue((casestab[i] >> k) % 2);
                k++;
            }
        }

    }
    deleteGrille();
    {
        int k = 0;
        for (int i = 0; i < taille; i++)
            for (int j = 0; j < taille; j++)
                if (a[i][j].getValue() == 2)
                {
                    tableau[k] = a[i][j].getIdValue();
                    k++;
                }
    }
}
