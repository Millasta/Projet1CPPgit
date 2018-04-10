#ifndef CLECTEURMATRICE_H
#define CLECTEURMATRICE_H

#include "CMatrice.h"
#include "CException.hpp"

/**
*	Classe permettant la construction d'un objet CMatrice
*	à partir d'un fichier référencé par son chein d'accès.
*
*	Permet la construction de plusieurs objets CMatrice différents
*	en modifiant l'attribut pcLECcheminFichier.
*
*	Les fichiers sont au format texte et suivent un modèle particulier.
*/
class CLecteurMatrice
{
private:
	std::string sLECcheminFichier;

public:
	CLecteurMatrice(std::string chemin);
	~CLecteurMatrice();
	template<typename T>
	CMatrice<T>* LEClecture();
	void LECchangeChemin(const std::string chemin);
};

template <class T>
CMatrice<T>* CLecteurMatrice::LEClecture() {
	std::ifstream isFichier(sLECcheminFichier);  // Ouverture du fichier en lecture

	if (isFichier)  // si l'ouverture a réussi
	{
		std::cout << "Ouverture du fichier " << sLECcheminFichier << " réussie ! " << std::endl;

		// Lecture du fichier
		std::string ligne;
		getline(isFichier, ligne);

		// Type
		// Atteint la balise TypeMatrice
		while (ligne.substr(0, 13).compare("TypeMatrice=<") != 0) {
			getline(isFichier, ligne);
			if (isFichier.eof())
				throw new CException(1, (char*)"Erreur syntaxe.");
		}
		std::string type = ligne.substr(ligne.find("<") + 1);
		type = type.substr(0, type.length() - 1);
		std::cout << "Type : " << type << std::endl;
		if (type.compare("double") != 0)
			throw new CException(ERR_FICHIER, (char*)"Type invalide.");

		// NBLignes
		// Atteint la balise NBLignes
		getline(isFichier, ligne);
		while (ligne.substr(0, 9).compare("NBLignes=")) {
			getline(isFichier, ligne);
			if (isFichier.eof())
				throw new CException(1, (char*)"Erreur syntaxe.");
		}
		int nbLignes = stoi(ligne.substr(ligne.find("=") + 1), nullptr);
		std::cout << "nbLignes : " << nbLignes << std::endl;
		if (nbLignes < 0)
			throw new CException(ERR_FICHIER, (char*)"NBLignes invalide.");

		// NBColonnes
		// Atteint la balise NBColonnes
		getline(isFichier, ligne);
		while (ligne.substr(0, 11).compare("NBColonnes=")) {
			getline(isFichier, ligne);
			if (isFichier.eof())
				throw new CException(1, (char*)"Erreur syntaxe.");
		}
		int nbColonness = stoi(ligne.substr(ligne.find("=") + 1), nullptr);
		std::cout << "nbColonnes : " << nbColonness << std::endl;
		if (nbLignes < 0)
			throw new CException(ERR_FICHIER, (char*)"NBColonnes invalide.");


		isFichier.close();
	}
	else {
		throw new CException(ERR_FICHIER, (char*)(std::string("Impossible d'ouvrir le fichier : ") + sLECcheminFichier).c_str());
		std::cout << std::string("Impossible d'ouvrir le fichier : ") + sLECcheminFichier << std::endl;
	}
	return new CMatrice<T>();
}


#endif