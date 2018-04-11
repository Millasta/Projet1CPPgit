#include "stdafx.h"
#include "CMatrice.hpp"

void CMatrice<int>::MATafficherElement(const int iElement) const {
	printf(" %d ", iElement);
}

void CMatrice<char>::MATafficherElement(const char iElement) const {
	printf(" %c ", iElement);
}

void CMatrice<double>::MATafficherElement(const double iElement) const {
	printf(" %f ", iElement);
}
