#ifndef CLECTEURMATRICE_H
#define CLECTEURMATRICE_H

/**
*	Classe permettant la construction d'un objet CMatrice
*	� partir d'un fichier r�f�renc� par son chemin d'acc�s.
*
*	Ne g�re que les matrices de type double, l�vre une exception sinon.
*
*	Permet la construction de plusieurs objets CMatrice diff�rents
*	en modifiant l'attribut pcLECcheminFichier.
*
*	Les fichiers sont au format texte et suivent un mod�le particulier.
*/
class CLecteurMatrice
{
private:
	std::string sLECcheminFichier;

public:
	CLecteurMatrice();
	CLecteurMatrice(std::string chemin);
	~CLecteurMatrice();
	template<typename T> CMatrice<T>* LEClecture();
	void LECchangeChemin(const std::string chemin);
};

/**
*	Ouvre le fichier en lecture.
*	
*	R�cup�re les diff�rents param�tres via lecture des diff�rentes balises.
*	Si une balise est mal orthographi�e ou mal plac�e, l�ve une erreur de syntaxe
*	(ne prend pas en compte les espaces/tabulations/retours chariots).
*
*	Cr�� et renvoit un pointeur sur un objet CMatrice<double> initialis�e avec les valeurs lues.	
*/
template <typename T>
CMatrice<T>* CLecteurMatrice::LEClecture() {
	std::ifstream isFichier(sLECcheminFichier);  // Ouverture du fichier en lecture

	if (isFichier)  // si l'ouverture a r�ussi
	{
		// Lecture du fichier
		std::string ligne;
		getline(isFichier, ligne);

		// Type
		// Atteint la balise TypeMatrice
		while (ligne.substr(0, 13).compare("TypeMatrice=<") != 0) {
			getline(isFichier, ligne);
			if (isFichier.eof())
				throw CException(1, (char*)"Erreur syntaxe.");
		}
		std::string type = ligne.substr(ligne.find("<") + 1);
		type = type.substr(0, type.length() - 1);
		if (type.compare("double") != 0)
			throw CException(ERR_FICHIER, (char*)"Type invalide.");

		// NBLignes
		// Atteint la balise NBLignes
		getline(isFichier, ligne);
		while (ligne.substr(0, 9).compare("NBLignes=")) {
			getline(isFichier, ligne);
			if (isFichier.eof())
				throw CException(1, (char*)"Erreur syntaxe.");
		}
		int nbLignes = stoi(ligne.substr(ligne.find("=") + 1), nullptr);
		if (nbLignes < 0)
			throw CException(ERR_FICHIER, (char*)"NBLignes invalide.");

		// NBColonnes
		// Atteint la balise NBColonnes
		getline(isFichier, ligne);
		while (ligne.substr(0, 11).compare("NBColonnes=")) {
			getline(isFichier, ligne);
			if (isFichier.eof())
				throw CException(1, (char*)"Erreur syntaxe.");
		}
		int nbColonnes = stoi(ligne.substr(ligne.find("=") + 1), nullptr);
		if (nbLignes < 0)
			throw CException(ERR_FICHIER, (char*)"NBColonnes invalide.");

		
		// Lecture et cr�ation de la matrice
		CMatrice<double>* pMatrice = new CMatrice<double>(nbLignes, nbColonnes);

		// Matrice
		// Atteint la balise Matrice
		getline(isFichier, ligne);
		while (ligne.substr(0, 9).compare("Matrice=[")) {
			getline(isFichier, ligne);
			if (isFichier.eof())
				throw CException(1, (char*)"Erreur syntaxe.");
		}
		int compteurLignes, compteurColonnes = 0;
		double dElement;
		for (compteurLignes = 0; compteurLignes < nbLignes; compteurLignes++) {
			for (compteurColonnes = 0; compteurColonnes < nbColonnes; compteurColonnes++) {
				isFichier >> dElement;
				pMatrice->MATdefinirValeur(dElement, compteurLignes, compteurColonnes);
			}
		}

		isFichier.close();
		return pMatrice;
	}
	else {
		throw CException(ERR_FICHIER, (char*)(std::string("Impossible d'ouvrir le fichier : ") + sLECcheminFichier).c_str());
		std::cout << std::string("Impossible d'ouvrir le fichier : ") + sLECcheminFichier << std::endl;
	}

	return NULL;
}


#endif