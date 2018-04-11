#include "stdafx.h"
#include "CException.hpp"
#include "CMatrice.hpp"
#include "CLecteurMatrice.hpp"

CLecteurMatrice::CLecteurMatrice() {
	sLECcheminFichier = std::string();
}

CLecteurMatrice::CLecteurMatrice(std::string chemin) {
	sLECcheminFichier = std::string(chemin);
}

CLecteurMatrice::~CLecteurMatrice() {
}

void CLecteurMatrice::LECchangeChemin(const std::string chemin) {
	sLECcheminFichier = std::string(chemin);
}
