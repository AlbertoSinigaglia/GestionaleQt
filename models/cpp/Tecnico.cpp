#include "../headers/Tecnico.h"


Tecnico::Tecnico(const Persona& persona, const DatiLavoratore& dati_lavoratore, const DatiManutenzione& dati_manutenzione, const DatiSistemi& dati_sistemi, const DatiRiparazioneSistemi& dati_riparazione_sistemi):
                Employee(persona, dati_lavoratore), Manutenzione(persona, dati_lavoratore, dati_manutenzione), Hardware(persona, dati_lavoratore, dati_sistemi),
                perc_riparazioni_sussistenti(dati_riparazione_sistemi.perc_riparazioni_sussistenti),
                ore_stallo_mensili(dati_riparazione_sistemi.ore_stallo_mensili),
                ore_straordinari(dati_riparazione_sistemi.ore_straordinari){}


float Tecnico::remunerazioneOraRoutine() const{
    return Conv::remunerazione_ora_routine_tecnico;
}


void Tecnico::aggiornaMese(){
    
    Manutenzione::aggiornaMese();
    Hardware::aggiornaMese();

    ore_stallo_mensili = 0;
    ore_straordinari = 0;
}

unsigned int Tecnico::oreLavoroNelMese() const{
    return Employee::oreLavoroNelMese() + ore_straordinari;
}


unsigned int Tecnico::orePiccolaRiparazione() const{
     // ottengo le ore che ha dedicato fin ora per le piccole riparazioni togliendo le ore di stallo
    int ore_piccole_riparazioni = oreLavoroNelMese() - ore_stallo_mensili;
    int riparazioni_non_sussistenti = static_cast<int>( getNRiparazioniMese() * (1 - perc_riparazioni_sussistenti) );
    unsigned int result = riparazioni_non_sussistenti==0? Conv::ore_ripristino_stallo/2: ore_piccole_riparazioni / riparazioni_non_sussistenti;
    return (result<Conv::ore_ripristino_stallo/2)? Conv::ore_ripristino_stallo/2 : result;
}


float Tecnico::valoreMedioRiparazione() const{

    return UFMath::mediaPonderata( orePiccolaRiparazione(), Conv::valore_piccola_riparazione, Conv::ore_ripristino_stallo, Conv::valore_riparazione_sussistente ) ;
}


unsigned int Tecnico::quantitaConsiderevoleRiparazioni() const{
    return Conv::n_riparazioni_considervole_tecnico;
}


double Tecnico::percRipristino() const{

    // Ogni tipo di manutenzione (con o senza stallo) e pesata per il numero di ore che quel tipo di manutenzione comporta
    double peso_stallo = Conv::ore_ripristino_stallo;
    double peso_piccola_riparazione = orePiccolaRiparazione();

    // calcolo il peso in ore della manutenzione prevista fino alla fine del mese, (perc_riparazioni_sussistenti mi da una stima di che tipo di manutenzioni posso aspettarmi )
    double peso_manutenzione_prevista = (getNSistemiMalfunzionanti()<=getNSistemiGestiti()?getNSistemiMalfunzionanti():getNSistemiGestiti())
                                       *( perc_riparazioni_sussistenti * peso_stallo + (1 - perc_riparazioni_sussistenti) * peso_piccola_riparazione );

    // la situazione di manutenzione totale (percRipristino() == 0) e quella in cui il tecnico deve riparare tutti i sistemi che gestisce
    // nel peggiore dei casi (cioe solo con il tipo di manutenzione più ponderante)
    double peso_manutenzione_totale = getNSistemiGestiti() * ( (peso_stallo > peso_piccola_riparazione)? peso_stallo : peso_piccola_riparazione );

    return 1- peso_manutenzione_prevista / peso_manutenzione_totale;
}


bool Tecnico::produttivo() const{

    unsigned int n_riparazioni_considerevole_nel_mese = quantitaConsiderevoleRiparazioni() * Data::oggi().getGiorno() / 31 ;

    return ( Manutenzione::produttivo() && Hardware::produttivo() ) ||
                // un altro modo per dimostrare la produttivita e richiedere straordinari mantenendo una velocita apprezzabile di riparazioni
                ( ( ore_straordinari > 0 ) && ( getNRiparazioniMese() > n_riparazioni_considerevole_nel_mese /2) );

}


float Tecnico::valoreLavoro() const{
    // il valore riparazione stalli e il valore che l'azienda ha risparmiato  (perdita_di_sussistenza = perdita all'ora dell'azienda in stallo)
    float valore_risparmiato_stalli = ore_straordinari * Conv::perdita_di_sussistenza;

    return Manutenzione::valoreLavoro() + valore_risparmiato_stalli;

}


float Tecnico::bonusStipendio() const{

    float bonus_quantita_sussistenti_gestiti = calcoloBonusLineare(0.5, perc_riparazioni_sussistenti, Conv::bonus_solo_sussistenza); 

    return bonus_quantita_sussistenti_gestiti + Manutenzione::bonusStipendio() + Hardware::bonusStipendio() - Employee::bonusStipendio() ;
}





void Tecnico::setOreStraordinari(unsigned int value)
{
    ore_straordinari = value;
}

void Tecnico::setOreStalloMensili(unsigned int value)
{
    ore_stallo_mensili = value;
}

void Tecnico::setPercRiparazioniSussistenti(double value)
{
    perc_riparazioni_sussistenti = value;
}



DatiRiparazioneSistemi Tecnico::getDatiRiparazioneSistemi() const{
    return DatiRiparazioneSistemi{perc_riparazioni_sussistenti, ore_stallo_mensili, ore_straordinari};
}

void Tecnico::setDatiRiparazioneSistemi(const DatiRiparazioneSistemi& d){
    ore_straordinari=d.ore_straordinari;
    ore_stallo_mensili=d.ore_stallo_mensili;
    perc_riparazioni_sussistenti=d.perc_riparazioni_sussistenti;
}
