#ifndef DEF_CEXCEPTION
#define DEF_CEXCEPTION

//***********************************
//**           CException          **
//***********************************
// Exception personnalisée
// Renseigne :
//      - l'id de l'exception
//      - sa description (facultatif, "Exception" par défaut)

#define ERR_DIMENSION 1
#define ERR_OPERATION 2
#define ERR_FICHIER   3

class CException {

private:

    int iEXCId;
    char *sEXCDescription;

public:

    CException();
    // Constructeur prenant en paramètre l'id de l'exception
    CException(int id);
    // Constructeur prenant en paramètre l'id
    // et la chaine de caractère décrivant l'exception levée
    CException(int id, char *description);

    ~CException();

    // Affiche la description de l'exception dans la sortie tandard de la console
    void EXCAfficher() const;

    // Retourne l'id de l'exception
    int EXCRetourneId() const;

    // Retourne la description de l'exception
    char *EXCRetourneDescription() const;

};

#endif // DEF_CEXCEPTION
