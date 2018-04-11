// Projet1CPP.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "CException.hpp"
#include "CMatrice.hpp"
#include "CLecteurMatrice.hpp"

int main(int argc, char *argv[])
{
	CMatrice<double>* pDMATmatrice = NULL;
	CLecteurMatrice* pLEClecteur = new CLecteurMatrice();
	CMatrice<double>* pmatTab[10];

	int compteurArg;
	for (compteurArg = 1; compteurArg < argc; compteurArg++) {
		try {
			pLEClecteur->LECchangeChemin(argv[compteurArg]);
			std::cout << "Ouverture du fichier " << argv[compteurArg] << " ..." << std::endl;
			pDMATmatrice = pLEClecteur->LEClecture<double>();
			pDMATmatrice->MATafficher();
			pmatTab[compteurArg - 1] = pDMATmatrice;
		}
		catch (CException const& e) {
			e.EXCAfficher();
		}
		catch (std::exception const& e) {
			std::cerr << "Erreur lors de la lecture du fichier " << argv[compteurArg] << std::endl;
			std::cerr << e.what() << std::endl;
		}
	}

	try {
		(*pmatTab[0] + *pmatTab[1]).MATafficher();
		(*pmatTab[0] + *pmatTab[2]).MATafficher();
	}
	catch (CException const& e) {
		e.EXCAfficher();
	}
	system("pause");
    return 0;
}

