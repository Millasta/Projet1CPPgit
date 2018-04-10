// Projet1CPP.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "CLecteurMatrice.hpp"

int main()
{
	CMatrice<int>* pIMATmatrice = new CMatrice<int>();
	CLecteurMatrice* pLEClecteur = new CLecteurMatrice("Data/matrice1.txt");
	try {
		pIMATmatrice = pLEClecteur->LEClecture<int>();
	}
	catch (CException e) {
		e.EXCAfficher();
	}
	system("pause");
    return 0;
}

