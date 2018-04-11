#ifndef DEF_CEXCEPTION
#define DEF_CEXCEPTION

//***********************************
//**           CException          **
//***********************************
// Exception personnalis�e
// Renseigne :
//      - l'id de l'exception
//      - sa description (facultatif, "Exception" par d�faut)

#define ERR_DIMENSION 1
#define ERR_OPERATION 2
#define ERR_FICHIER   3

class CException {

private:

    int iEXCId;
    char *sEXCDescription;

public:

    CException();
    // Constructeur prenant en param�tre l'id de l'exception
    CException(int id);
    // Constructeur prenant en param�tre l'id
    // et la chaine de caract�re d�crivant l'exception lev�e
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
