#ifndef CMATRICE_H
#define CMATRICE_H

#include "stdafx.h"
#include "CException.hpp"

template <typename T>
class CMatrice {

private:
	T * * pptMATelements;
	unsigned int uiMATnbLignes;
	unsigned int uiMATnbColonnes;

public:
	CMatrice();
	CMatrice(const unsigned int uiNbLignes, const unsigned int uiNbColonnes);
	CMatrice(const CMatrice<T> &matObj);
	~CMatrice();

	unsigned int MATlireNbLignes() const;
	unsigned int MATlireNbColonnes() const;
	T MATlireValeur(const unsigned int uiLigne, const unsigned int uiColonne) const;
	void MATdefinirValeur(const T tElement, const unsigned int uiLigne, const unsigned int uiColonne);

	void MATafficher() const;
	void MATafficherElement(const int iElement) const;
	void MATafficherElement(const char iElement) const;
	void MATafficherElement(const double iElement) const;

	CMatrice<T> MATtransposer();

	CMatrice<T> operator+(const CMatrice<T> &matObj);
	CMatrice<T> operator-(const CMatrice<T> &matObj);
	CMatrice<T> operator*(const CMatrice<T> &matObj);

	CMatrice<T> operator*(const T &tConstante);
	CMatrice<T> operator/(const T &tConstante);
};

template <typename T> CMatrice<T>::CMatrice() {
	pptMATelements = (T**)malloc(sizeof(T*));
	pptMATelements[0] = (T*)malloc(sizeof(T));

	uiMATnbLignes = 1;
	uiMATnbColonnes = 1;
}

template <typename T> CMatrice<T>::CMatrice(const unsigned int uiNbLignes, const unsigned int uiNbColonnes) {
	unsigned int uiLigne;

	uiMATnbLignes = uiNbLignes;
	uiMATnbColonnes = uiNbColonnes;

	pptMATelements = (T**)malloc(sizeof(T*) * uiNbLignes);
	for (uiLigne = 0; uiLigne < uiNbLignes; uiLigne++) {
		pptMATelements[uiLigne] = (T*)malloc(sizeof(T) * uiNbColonnes);
	}
}

template <typename T> CMatrice<T>::CMatrice(const CMatrice& matObj) {
	unsigned int uiLigne, uiColonne;

	uiMATnbLignes = matObj.MATlireNbLignes();
	uiMATnbColonnes = matObj.MATlireNbColonnes();

	pptMATelements = (T**)malloc(sizeof(T*) * uiMATnbLignes);

	for (uiLigne = 0; uiLigne < uiMATnbLignes; uiLigne++) {
		pptMATelements[uiLigne] = (T*)malloc(sizeof(T) * uiMATnbColonnes);

		for (uiColonne = 0; uiColonne < uiMATnbColonnes; uiColonne++) {
			MATdefinirValeur(matObj.MATlireValeur(uiLigne, uiColonne), uiLigne, uiColonne);
		}
	}
}

template <typename T> CMatrice<T>::~CMatrice() {
	unsigned int uiLigne;

	for (uiLigne = 0; uiLigne < uiMATnbLignes; uiLigne++) {
		free(pptMATelements[uiLigne]);
	}

	free(pptMATelements);

	pptMATelements = nullptr;
	uiMATnbLignes = 0;
	uiMATnbColonnes = 0;
}

template <typename T> unsigned int CMatrice<T>::MATlireNbLignes() const {
	return uiMATnbLignes;
}

template <typename T> unsigned int CMatrice<T>::MATlireNbColonnes() const {
	return uiMATnbColonnes;
}

template <typename T> void CMatrice<T>::MATdefinirValeur(const T tElement, const unsigned int uiLigne, const unsigned int uiColonne) {
	if (uiLigne < uiMATnbLignes && uiColonne < uiMATnbColonnes) {
		pptMATelements[uiLigne][uiColonne] = tElement;
	}
	else {
		throw CException(/*ERR_DIMENSION, "Dimension(s) non cohérente(s)."*/);
	}
}

template <typename T> T CMatrice<T>::MATlireValeur(const unsigned int uiLigne, const unsigned int uiColonne) const {
	if (uiLigne < uiMATnbLignes && uiColonne < uiMATnbColonnes) {
		return pptMATelements[uiLigne][uiColonne];
	}
	else {
		throw CException(/*ERR_DIMENSION, "Dimension(s) non cohérente(s)."*/);
	}
}

template <typename T> void CMatrice<T>::MATafficher() const {
	unsigned int uiLigne, uiColonne;

	for (uiLigne = 0; uiLigne < uiMATnbLignes; uiLigne++) {
		printf("\n|");
		for (uiColonne = 0; uiColonne < uiMATnbColonnes; uiColonne++) {
			MATafficherElement(pptMATelements[uiLigne][uiColonne]);
		}
		printf("|");
	}
	printf("\n\n");
}

template <typename T> CMatrice<T> CMatrice<T>::MATtransposer() {
	CMatrice<T> * matrix = new CMatrice<T>(uiMATnbColonnes, uiMATnbLignes);
	unsigned int uiLigneIdx, uiColonneIdx;

	for (uiLigneIdx = 0; uiLigneIdx < uiMATnbLignes; uiLigneIdx++) {
		for (uiColonneIdx = 0; uiColonneIdx < uiMATnbColonnes; uiColonneIdx++) {
			matrix->MATdefinirValeur(MATlireValeur(uiLigneIdx, uiColonneIdx), uiColonneIdx, uiLigneIdx);
		}
	}

	return *matrix;
}

/*---------------------------------------------*/
/*		Surcharge d'opérateurs (+, -, *, /)		*/
/*---------------------------------------------*/


template <typename T> CMatrice<T> CMatrice<T>::operator+(const CMatrice<T> &matObj) {
	if (uiMATnbLignes == matObj.MATlireNbLignes() && uiMATnbColonnes == matObj.MATlireNbColonnes()) {
		CMatrice<T> * matrix = new CMatrice<T>(uiMATnbLignes, uiMATnbColonnes);
		unsigned int uiLigne, uiColonne;

		for (uiLigne = 0; uiLigne < uiMATnbLignes; uiLigne++) {
			for (uiColonne = 0; uiColonne < uiMATnbColonnes; uiColonne++) {
				matrix->MATdefinirValeur(MATlireValeur(uiLigne, uiColonne) + matObj.MATlireValeur(uiLigne, uiColonne), uiLigne, uiColonne);
			}
		}

		return *matrix;
	}
	else {
		throw CException(/*ERR_OPERATION, "Addition impossible : dimensions non cohérentes."*/);
	}
}

template <typename T> CMatrice<T> CMatrice<T>::operator-(const CMatrice<T> &matObj) {
	if (uiMATnbLignes == matObj.MATlireNbLignes() && uiMATnbColonnes == matObj.MATlireNbColonnes()) {
		CMatrice<T> * matrix = new CMatrice<T>(uiMATnbLignes, uiMATnbColonnes);
		unsigned int uiLigne, uiColonne;

		for (uiLigne = 0; uiLigne < uiMATnbLignes; uiLigne++) {
			for (uiColonne = 0; uiColonne < uiMATnbColonnes; uiColonne++) {
				matrix->MATdefinirValeur(MATlireValeur(uiLigne, uiColonne) - matObj.MATlireValeur(uiLigne, uiColonne), uiLigne, uiColonne);
			}
		}

		return *matrix;
	}
	else {
		throw CException(/*ERR_OPERATION, "Soustraction impossible : dimensions non cohérentes."*/);
	}
}

template <typename T> CMatrice<T> CMatrice<T>::operator*(const CMatrice<T> &matObj) {
	CMatrice<T> M1 = *this;
	const CMatrice<T> M2 = matObj;

	if (uiMATnbColonnes == M2.MATlireNbLignes()) {
		CMatrice<T> * matrix = new CMatrice<T>(uiMATnbLignes, M2.MATlireNbColonnes());
		unsigned int uiLigneM1Idx, uiColonneM1Idx, uiColonneM2Idx;
		T somme;

		for (uiLigneM1Idx = 0; uiLigneM1Idx < uiMATnbLignes; uiLigneM1Idx++) {
			for (uiColonneM2Idx = 0; uiColonneM2Idx < M2.MATlireNbColonnes(); uiColonneM2Idx++) {
				somme = (T)0;
				for (uiColonneM1Idx = 0; uiColonneM1Idx < uiMATnbLignes; uiColonneM1Idx++) {
					somme += MATlireValeur(uiLigneM1Idx, uiColonneM1Idx) * matObj.MATlireValeur(uiColonneM1Idx, uiColonneM2Idx);
				}
				matrix->MATdefinirValeur(somme, uiLigneM1Idx, uiColonneM2Idx);
			}
		}
		return *matrix;
	}
	else {
		throw CException(/*ERR_OPERATION, "Multiplication impossible : dimensions non cohérentes."*/);
	}
}

template <typename T> CMatrice<T> CMatrice<T>::operator*(const T &tConstante) {
	unsigned int uiLigneIdx, uiColonneIdx;
	CMatrice<T> * matrix = new CMatrice<T>(uiMATnbLignes, uiMATnbColonnes);

	for (uiLigneIdx = 0; uiLigneIdx < uiMATnbLignes; uiLigneIdx++) {
		for (uiColonneIdx = 0; uiColonneIdx < uiMATnbColonnes; uiColonneIdx++) {
			matrix->MATdefinirValeur(MATlireValeur(uiLigneIdx, uiColonneIdx) * tConstante, uiLigneIdx, uiColonneIdx);
		}
	}
	return *matrix;
}

template <typename T> CMatrice<T> CMatrice<T>::operator/(const T &tConstante) {
	unsigned int uiLigneIdx, uiColonneIdx;
	CMatrice<T> * matrix = new CMatrice<T>(uiMATnbLignes, uiMATnbColonnes);

	for (uiLigneIdx = 0; uiLigneIdx < uiMATnbLignes; uiLigneIdx++) {
		for (uiColonneIdx = 0; uiColonneIdx < uiMATnbColonnes; uiColonneIdx++) {
			matrix->MATdefinirValeur(MATlireValeur(uiLigneIdx, uiColonneIdx) / tConstante, uiLigneIdx, uiColonneIdx);
		}
	}
	return *matrix;
}

#endif