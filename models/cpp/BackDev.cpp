//
// Created by Alberto Sinigaglia on 09/04/2020.
//

#include "../headers/BackDev.h"

 
BackDev::BackDev(Persona persona, DatiLavoratore dati_lavoratore, DatiDeveloping dati_developing, DatiLatoServer dati_server):
            Software(persona, dati_lavoratore, dati_developing),
            perc_capo_progetto(dati_server.perc_capo_progetto),
            livello_astrazione(dati_server.livello_astrazione),
            prove_correttezza(dati_server.prove_correttezza),
            orientato_ortogonalita(dati_server.orientato_ortogonalita){}
};


double BackDev::velocitaScrittura() const{
    // più un programmatore lavora ad un livello di astrazione maggiore più si prospetta una scrittura più lenta 
    double speed_up_astrazione = 1 - calcoloBonusLineare(0 , (livello_astrazione)/5.0 , 1 - Conv::perc_velocita_astrazione_5);

    //se li programmatore aggiunge al suo lavoro anche le prove di correttezza la velocita di scrittura del codice diminuisce
    double malus_prove_correttezza = 1 - (prove_correttezza)? Conv::malus_velocita_prove_corettezza : 0;

    return Software::velocitaScrittura() * speed_up_astrazione * malus_prove_correttezza;
}


unsigned int BackDev::riutilizzabilita() const{

    int num_ricicli_per_astrazione = static_cast<int>(Conv::riutilizzo_astrazione_5 * livello_astrazione/5);
    int num_ricicli_per_qualita_codice = Software::riutilizzabilita();

    if(num_ricicli_per_astrazione > num_ricicli_per_qualita_codice)
        return num_ricicli_per_astrazione;   else   return num_ricicli_per_qualita_codice;
}


bool BackDev::isOrientatoOrtogonalita() const{
    return orientato_ortogonalita;
}






bool BackDev::produttivo() const{

    bool prestazione_sufficiente = perc_capo_progetto >= Conv::perc_media_capo_progetto * 2/3;

    return prestazione_sufficiente && Software::produttivo() ;
}


float BackDev::bonusStipendio() const {

    float bonus_capo_progetti = calcoloBonusLineare( Conv::perc_media_capo_progetto, perc_capo_progetto, Conv::bonus_sempre_capo_progetto );
    float bonus_correttezza = (prove_correttezza)? Conv::bonus_prove_correttezza : 0;

    return Software::bonusStipendio() + bonus_capo_progetti + bonus_correttezza;
}
 

float BackDev::valoreLavoro() const {

    float valore_influenza_architettura = getNProgettiConclusiMese() * Conv::valore_astrazione_5_un_progetto * livello_astrazione/5;
    float valore_leadership_nel_mese = getNProgettiConclusiMese() * perc_capo_progetto * Conv::valore_capo_un_progetto;

    return Software::valoreLavoro() + valore_influenza_architettura + valore_leadership_nel_mese;
}
