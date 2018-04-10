#include <iostream>
#include <string.h>
#include "stdafx.h"
#include "CException.hpp"

// Constructeur par défaut
CException::CException() {
    iEXCId = 0;
    sEXCDescription = (char*)"Exception";
}

// Constructeur prenant en paramètre l'id de l'exception
CException::CException(int id) {
    iEXCId = id;
    sEXCDescription = (char*)"Exception";
}


// Constructeur prenant en paramètre l'id
// et la chaine de caractère décrivant l'exception levée
CException::CException(int id, char* description) {
    iEXCId = id;

    int iTaille = 0;
    char *pcCompteur = &description[0];
    while(*pcCompteur != '\0') {
        iTaille++;
        pcCompteur++;
    }
    sEXCDescription = new char[iTaille+1];

    int iCompteur;
    for(iCompteur = 0 ; iCompteur < iTaille ; iCompteur++)
        sEXCDescription[iCompteur] = description[iCompteur];
    sEXCDescription[iCompteur] = '\0';
}

// Destructeur
CException::~CException() {}

// Affiche l'id et la description de l'exception dans la sortie tandard de la console
// sous la forme Exception id : description
void CException::EXCAfficher() const {
    std::cout << "CException " << iEXCId << " : " << sEXCDescription << std::endl;
}

// Retourne l'id de l'exception
int CException::EXCRetourneId() const {
    return iEXCId;
}

// Retourne la description de l'exception (500 caracères max)
char* CException::EXCRetourneDescription() const {
    char *sChaine = new char[500];
    memset(sChaine, '\0', 500);
    char *cCompteur = &sEXCDescription[0];
    int iCompteur = 0;
    while(*cCompteur != '\0') {
        sChaine[iCompteur] = sEXCDescription[iCompteur];
        cCompteur++;
        iCompteur++;
    }
    return sChaine;
}
