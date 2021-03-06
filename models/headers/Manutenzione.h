#ifndef CSVPARSER_MANUTENZIONE_H
#define CSVPARSER_MANUTENZIONE_H
 
 
#include "Employee.h" 
 
class Manutenzione: virtual public Employee{
 
public:

    Manutenzione(const Persona& persona, const DatiLavoratore& dati_lavoratore, const DatiManutenzione& dati_manutenzione);

    /*      PERCENTUALE RIPRISTINO                  (metodo reale  da 0 a 1)
     * Il metodo indica con una percentuale il grado di ripristino della situazione di normalita sulla base del lavoro svolto
     * a partire da inizio mese fin ora. 
     *          La situazione di normalita è uno stato del sistema produttivo dove non sono più necessari gli interventi
     *          di manutanzione dell'impiegato (è pertanto riferita alla tipoligia specifica del suo lavoro)
     */
    virtual double percRipristino() const = 0;

    /*      PRODUTTIVO                      (metodo che eredita l'obbiettivo della classe base)*/
    virtual bool produttivo() const override;

    /*      BOUNS STIPENDIO                 (metodo che eredita l'obbiettivo della classe base)*/
    virtual float bonusStipendio() const override;

    /*      AGGIORNA MESE                   (metodo che eredita l'obbiettivo della classe base)*/
    virtual void aggiornaMese() override;


    void setPercRiparazioniInefficaci(double value);

    void setNRiparazioniMese(unsigned int value);

    void setPercRipristinoMedio(double value);


    DatiManutenzione getDatiManutenzione() const;
    void setDatiManutenzione(const DatiManutenzione& d);


protected:

    /*      VALORE LAVORO                   (metodo che eredita l'obbiettivo della classe base)*/
    virtual float valoreLavoro() const override;

    /*      VALORE MEDIO RIPARAZIONE
     * Il metodo restituisce il valore medio che da all'azionda 1 riparazione
     */
    virtual float valoreMedioRiparazione() const = 0;

    /*      QUANTITa CONSIDEREVOLE RIPARAZIONI
     * Il metodo ritorna la quantita di manutenzioni che è considerata necessaria (per il tipo di mansione che svolge)
     * in un mese per aggiudicarsi il bonus: bonus_n_riparazioni_considerevole (convenzione)
     */
    virtual unsigned int quantitaConsiderevoleRiparazioni() const = 0;

    double getPercRiparazioniInefficaci() const;
    unsigned int getNRiparazioniMese() const;




private:

    double perc_riparazioni_inefficaci;       // SLIDE (da 0 a 1, approx =2)

    unsigned int n_riparazioni_mese;                // LINE_EDIT ( val minimo = 0, solo integer)

    double perc_ripristino_medio;                   // SLIDE (da 0 a 1, approx = 2)

};



#endif //CSVPARSER_MANUTENZIONE_H
