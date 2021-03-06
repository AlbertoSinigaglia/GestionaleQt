#ifndef CSVPARSER_FRONTDEV_H
#define CSVPARSER_FRONTDEV_H
  

#include "Software.h"

class FrontDev : virtual public Software{
public:

    FrontDev(const Persona & persona, const DatiLavoratore & dati_lavoratore, const DatiDeveloping & dati_developing, const DatiLatoClient & dati_lato_client);
    
    /*      PRODUTTIVO                      (metodo che eredita l'obbiettivo della classe base)*/
    virtual bool produttivo() const override;

    /*      BOUNS STIPENDIO                 (metodo che eredita l'obbiettivo della classe base)*/
    virtual float bonusStipendio() const override;

    /*      VELOCITÀ SCRITTURA              (metodo che eredita l'obbiettivo della classe base)*/
    virtual double velocitaScrittura() const override;




    void setLibreria(const Conv::Libreria &value);

    void setOrientatoProfessionalita(bool value);

    void setPercCodicePerfezionato(double value);



    DatiLatoClient getDatiLatoClient() const;
    void setDatiLatoClient(const DatiLatoClient& d);


protected:

    /*      RIUTILIZZABILITÀ                (metodo che eredita l'obbiettivo della classe base)*/
    virtual unsigned int riutilizzabilita() const override;

    bool isOrientatoProfessionalita() const;

private:

    Conv::Libreria libreria;                // COMBO BOX (scelta tutte le librerie)

    bool orientato_professionalita;         // FLAG

    double perc_codice_perfezionato;        // SLIDE (da 0 a 1 , approx =2)
    // percentuale di codice esterno (derivante da cut&paste) adattato per il progetto

};
 

#endif //CSVPARSER_FRONTDEV_H
