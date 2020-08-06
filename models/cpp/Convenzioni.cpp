#include "models/support/Convenzioni.h"
namespace Conv{         // CONVENZIONI

// ------------------------------------------------------------------
//                          EXTRA AZIENDALI
// ------------------------------------------------------------------

   enum Linguaggio :short {
        PYTHON = 0,
        JAVA = 1,
        PHP = 2,
        CPP = 3,
        SWIFT = 4,
        JAVASCRIPT = 5,
        RUBY = 6,
        SQL =7,
        TYPESCRIPT =8
   };
   enum Libreria : short{
       BOOTSTRAP = 0,
       JQUERY = 1,
       TREEJS = 2,
       ANGULAR = 3,
       VUEJS = 4
   };
   const double coeff_liquidazione{0.889};
   const double perc_remunerazione{0.8};
   const unsigned int soglia_anni_esperto{20};
   const DifferenzaDate durata_progetto_medio{DifferenzaDate{1,0,0}};
   const unsigned int n_righe_progetto_medio{10000};
   const unsigned int n_impiegati_progetto_medio{5};
   const float valore_annuo_progetto_medio{100000.};
   const double perc_codice_scritto{0.2};
   const double velocita_cpp{100};
   const unsigned int soglia_n_righe_senior{1000000};
   const float complessita_linguaggio[8]{0.3f, 0.5f, 0.6f, 1.0f, 0.4f, 0.8f, 0.2f, 0.3f};
   const double status_accettabile{0.9};
   const unsigned int soglia_sistemi_gestiti_esperto{1000};
   const unsigned int media_n_nuovi_sistemi_mese{10};
   const float remunerazione_ora_routine_tecnico{10};
   const unsigned int n_riparazioni_considervole_tecnico = 10;
   const float valore_piccola_riparazione = 10;
   const float valore_riparazione_sussistente = 10;
   const float perdita_di_sussistenza = 10;
   const unsigned int ore_ripristino_stallo_pessimo = 10;
   const float remunerazione_ora_routine_ITSecurityDev = 10;
   const unsigned int n_riparazioni_considervole_ITSecurityDev = 10;
   const float perdita_breccia = 10;
   const float valore_manutenzione_non_critica = 10;
   const float valore_manutenzione_critica = 10;
   const double perc_pessimistica_manutenzioni_critiche = 100;
   const unsigned int media_n_righe_manutenzione_critica = 23;
   const unsigned int tolleranza_n_problemi_aperti_mese = 5;
   const double perc_media_capo_progetto = 0.4;
   const double perc_velocita_astrazione_5 = 0.8;
   const double malus_velocita_prove_corettezza = 0.8;
   const unsigned int riutilizzo_astrazione_5 = 50;
   const float valore_capo_progetto = 10;
   const float remunerazione_ora_routine_DBDev = 10;
   const double media_attributi_ridondanti_per_entita = 0.2;
   const double moltiplicatore_ricicli_ortogonalita_10 = 2;
   const double speed_up_notevole_indicizzazioni = 2.0;
   const float esaustivita_libreria[5] = { 0.8 , 1.2 , 0.9 , 1 , 0.5};
   const float evolvibilita_libreria[5] = { 0.9 , 1.1 , 0.7 , 1 , 0.9};
   const float speed_up_angular = 2.0;
   const unsigned int riutilizzo_codice_angular = 10;
   const unsigned int righe_progetto_perfezionate_media = 100;
   const float remunerazione_ora_routine_GUIDev = 10;
   const float valore_rispetto_orientamento = 100;
   const float remunerazione_ora_routine_FullStack = 10;                                           // se modellazione, prove correttezza ecc..
   const double perc_minima_capo_progetti_FullStack = 0.4;
   const double malus_velocita_separazione_interfacce = 0.8;
   const float bonus_status_ottimo = 100;
   const float bonus_n_riparazioni_considerevole = 10;
   const float bonus_dei_20_sistemi = 100;
   const float bonus_solo_sussistenza = 100;
   const float bonus_delle_50_criticita = 100;
   const float bonus_orientamento_ortogonalita = 100;
   const float bonus_prove_correttezza = 100;
   const float bonus_performance_DB_ottime = 100;
   const float bonus_orientamento_professionalita = 100;
   const float bonus_meta_codice_adattato = 100;
   const float bonus_stile_GUI = 100;
   const float bonus_intuitivita_ottima = 100;
   const float bonus_professionalita_ottima = 100;
   const float bonus_separazione_interfaccie = 100;
}