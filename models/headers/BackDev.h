#ifndef CSVPARSER_BACKDEV_H
#define CSVPARSER_BACKDEV_H
 

#include "Software.h"

class BackDev : virtual public Software{

public: 

    BackDev(const Persona& persona, const DatiLavoratore& dati_lavoratore, const DatiDeveloping& dati_developing, const DatiLatoServer& dati_lato_server);
    
    /*      PRODUTTIVO                      (metodo che eredita l'obbiettivo della classe base)*/
    virtual bool produttivo() const override;

    /*      BOUNS STIPENDIO                 (metodo che eredita l'obbiettivo della classe base)*/
    virtual float bonusStipendio() const override;

    /*      VELOCITÀ SCRITTURA              (metodo che eredita l'obbiettivo della classe base)*/
    virtual double velocitaScrittura() const override;



    void setPercCapoProgetto(double value);

    void setLivelloAstrazione(unsigned int value);

    void setProveCorrettezza(bool value);

    void setOrientatoOrtogonalita(bool value);


    DatiLatoServer getDatiLatoServer() const;
    void setDatiLatoServer(const DatiLatoServer& d);

protected:

    /*      VALORE LAVORO                   (metodo che eredita l'obbiettivo della classe base)*/
    virtual float valoreLavoro() const override;

    /*      INFLUENZA PROGETTO              (metodo che eredita l'obbiettivo della classe base)*/
    virtual double influenzaProgetto() const override;

    /*      RIUTILIZZABILITÀ                (metodo che eredita l'obbiettivo della classe base)*/
    virtual unsigned int riutilizzabilita() const override;

    bool isOrientatoOrtogonalita() const;

    double getPercCapoProgetto() const;

private:

    double perc_capo_progetto;          // SLIDE ( da 0 a 1, cifre_approx = 2)

    unsigned int livello_astrazione;    // SLIDE ( da 1 a 5, cifre_approx = 0)

    bool prove_correttezza;             // FLAG
    bool orientato_ortogonalita;        // FLAG
    
};


#endif //CSVPARSER_BACKDEV_H
