#ifndef CSVPARSER_DBDEV_H
#define CSVPARSER_DBDEV_H

  
#include "BackDev.h"

class DBDev : public BackDev{

public:

    DBDev(const Persona& persona, const DatiLavoratore& dati_lavoratore, const DatiDeveloping& dati_developing, const DatiLatoServer& dati_lato_server, const DatiDatabase& dati_database);

    /*      BOUNS STIPENDIO                 (metodo che eredita l'obbiettivo della classe base)*/
    virtual float bonusStipendio() const override;

    /*      GRADO ORTOGONALITÀ              (metodo intero da 1 a 10)
     * Il metodo restituisce il grado (da 1 a 10) dell'ortogonalita che viene mantenuta nei database progettati 
     * dal DBDev in questione 
     */
    unsigned int gradoOrtogonalita() const;



    void setNumAttributiRidondantiPerEntita(double value);

    void setSpeedUpIndicizzazioni(double value);

    void setPercEntitaFormaNormale(double value);


    DatiDatabase getDatiDatabase() const;
    void setDatiDatabase(const DatiDatabase& d);


protected:

    /*      VALORE LAVORO                   (metodo che eredita l'obbiettivo della classe base)*/
    virtual float valoreLavoro() const override;

    /*      RIUTILIZZABILITÀ                (metodo che eredita l'obbiettivo della classe base)*/
    virtual unsigned int riutilizzabilita() const override;                                                             // sfrutta grado ortogonalita

    /*      REMUNERAZIONE ORA ROUTINE       (metodo che eredita l'obbiettivo della classe: Employee)*/
    virtual float remunerazioneOraRoutine() const override;

private:

    /* s     GRADO PERFORMANCE               (metodo intero da 1 a 10)
     * Il metodo restituisce il grado (da 1 a 10) di efficienza (velocita di risposta dataBase) garantita nel DataBase 
     * dal DBDev in questione 
     */
    unsigned int gradoPerformance() const;

/*
* CAMPI x PROGETTO
*/
    double num_attributi_ridondanti_per_entita;     //LINE_EDIT  (accetta double, non accetta val negativi)

    double speed_up_indicizzazioni;                 //LINE_EDIT  (accetta double, non accetta val negativi)

    double perc_entita_forma_normale;               // SLIDE (da 0 a 1, approx= 2)

};


#endif //CSVPARSER_DBDEV_H
 
