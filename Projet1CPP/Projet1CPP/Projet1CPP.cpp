// Projet1CPP.cpp : définit le point d'entrée pour l'application console.

#include "stdafx.h"
#include "CException.hpp"
#include "CMatrice.hpp"
#include "CLecteurMatrice.hpp"

#define TAILLE_BUFFER 256 // taille du tableau des pointeurs de matrice 

void lireFichiers(int argc, char *argv[], CMatrice<double>* pmatTab[TAILLE_BUFFER]);
void tests(CMatrice<double>* pmatTab[TAILLE_BUFFER]);
void algo(CMatrice<double>* pmatTab[TAILLE_BUFFER], int nbMatrices);

int main(int argc, char *argv[])
{
	CMatrice<double>* pmatTab[TAILLE_BUFFER]; // Tableau des matrices
	
	try {
		lireFichiers(argc, argv, pmatTab);
		//tests(pmatTab);
		algo(pmatTab, argc - 1);
	}
	catch (CException const& e) {
		e.EXCAfficher();
	}
	catch (std::exception const& e) {
		std::cout << e.what() << std::endl;
	}

	system("pause");
    return 0;
}

void algo(CMatrice<double>* pmatTab[TAILLE_BUFFER], int nbMatrices) {
	std::cout << "Saisissez une valeur c : ";
	double constante = 0;
	std::cin >> constante;
	int compteur;

	// Multiplications
	for (compteur = 0; compteur < nbMatrices; compteur++) {
		std::cout << "Matrice[" << compteur << "]*" << constante << " = " << std::endl;
		(*pmatTab[compteur] * constante).MATafficher();
	}

	// Divisions
	for (compteur = 0; compteur < nbMatrices; compteur++) {
		std::cout << "Matrice[" << compteur << "]/" << constante << " = " << std::endl;
		(*pmatTab[compteur] / constante).MATafficher();
	}

	// Additions
	CMatrice<double> matrice = CMatrice<double>(*pmatTab[0]);
	for (compteur = 1; compteur < nbMatrices; compteur++) {
		std::cout << "Matrice[" << compteur << "]";
		if (compteur != nbMatrices) std::cout << " + ";
		matrice = matrice + *pmatTab[compteur];
	}
	std::cout << " = " << std::endl;
	matrice.MATafficher();

}


void lireFichiers(int argc, char *argv[], CMatrice<double>* pmatTab[TAILLE_BUFFER]) {
	CMatrice<double>* pDMATmatrice = NULL;
	CLecteurMatrice* pLEClecteur = new CLecteurMatrice();

	int compteurArg;
	for (compteurArg = 1; compteurArg < argc; compteurArg++) {
		try {
			pLEClecteur->LECchangeChemin(argv[compteurArg]);
			std::cout << "Ouverture du fichier " << argv[compteurArg] << " ..." << std::endl;
			pDMATmatrice = pLEClecteur->LEClecture<double>();
			//pDMATmatrice->MATafficher();
			pmatTab[compteurArg - 1] = pDMATmatrice;
		}
		catch (CException const& e) {
			e.EXCAfficher();
		}
		catch (std::exception const& e) {
			std::cerr << "Erreur lors de la lecture du fichier " << argv[compteurArg] << std::endl;
			throw e;
		}
	}
}

void tests(CMatrice<double>* pmatTab[TAILLE_BUFFER]) {
	double dConstante = -1.5;
	int eConstante = 2;

	// Addition
	(*pmatTab[0] + *pmatTab[1]).MATafficher(); // A+B
	(*pmatTab[1] + *pmatTab[0]).MATafficher(); // B+A
	//(*pmatTab[0] + *pmatTab[2]).MATafficher(); // Addition dimensions différentes

	// Soustraction
	(*pmatTab[0] - *pmatTab[1]).MATafficher(); // A-B
	(*pmatTab[1] - *pmatTab[0]).MATafficher(); // B-A
	//(*pmatTab[0] - *pmatTab[2]).MATafficher(); // Soustraction dimensions différentes
	
	// Multiplication
	(*pmatTab[1] * dConstante).MATafficher(); // A * réel
	(*pmatTab[1] * eConstante).MATafficher(); // A * entier
	//(dConstante * *pmatTab[1]).MATafficher(); // réel * A
	//(eConstante * *pmatTab[1]).MATafficher(); // entier * A
	(*pmatTab[0] * *pmatTab[1]).MATafficher(); // A * B
	(*pmatTab[1] * *pmatTab[0]).MATafficher(); // B * A

	// Division
	(*pmatTab[1] / dConstante).MATafficher(); // A / réel
	(*pmatTab[1] / eConstante).MATafficher(); // A / entier

	// Transposée
	(pmatTab[2]->MATtransposer()).MATafficher(); // A'

	std::cout << "TESTS OK !" << std::endl;
}

