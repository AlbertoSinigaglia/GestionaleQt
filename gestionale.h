#ifndef GESTIONALE_H
#define GESTIONALE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QMenuBar>
#include <QMenu>
#include <QTableView>
#include <QGroupBox>
#include <QComboBox>
#include <QFile>
#include <QScrollArea>
#include <QListWidget>
#include "gestionalebutton.h"
#include "widgets/employeelistelement.h"
#include <vector>
#include <QAction>
#include "models/headers/Employee.h"
#include "widgets/employeeslist.h"
#include "collections/DynamicArray.h"
#include "employeesmanagement.h"

class Gestionale : public QWidget{
	Q_OBJECT

public:
	Gestionale(QWidget *parent = nullptr);
    ~Gestionale();
    void setModel(std::shared_ptr<EmployeesManagement> model_);
    void updateList() const;
    bool disableSaveEnableImport();
    void showLiquidation(QString nome, float quota_liquidazione);

private:
    std::shared_ptr<EmployeesManagement> model;
    QLineEdit* name;
    QHBoxLayout* mainLayout;
    QVBoxLayout* layoutFrameFiltri;
	QGroupBox* Visualizzare;
    QVBoxLayout* LayoutVisualizzare;
	QHBoxLayout* Left;
	QVBoxLayout* layoutVisualizza;
    EmployeesList* employeesList;
    QPushButton* modifica;
    QPushButton* inserisci;
    QPushButton* elimina;
    QComboBox* Dipendenti;
    QComboBox* ordine;
    QCheckBox* c_nome;
    QCheckBox* c_cognome;
    QCheckBox* c_sesso;
    QCheckBox* c_dataNascita;
    QCheckBox* c_cf;
    QCheckBox* DataA;
    QCheckBox* DataFineContratto;
    QCheckBox* StipendioBase;
    QCheckBox* OreLavoro;
    QAction* a_import;
    QAction* a_export;
    QAction* a_aboutUs;
    QAction* a_exit;
    QAction* a_open;
    QCheckBox* produttivo;
    QCheckBox* bonus_stipendio;
    QCheckBox* grado_esperienza;
    QCheckBox* numero_righe_totali;
    QCheckBox* linguaggio;
    QCheckBox* percentuale_ripristino;
    QCheckBox* numero_criticita_risolte;
    QCheckBox* ore_straordinari;
    QMenu* aboutUs;

    void addTitleSinistro();
	void addBoxDestro();
	void addBoxSinistro();
	void addEmployeesFilters();
	void addFirstBox();
	void addBoxPersona();
	void addBoxLavoro();
    void addBoxSpecifico();
	void addAzioni();
    void addOrdineBox();
    void addMenu();
	void setStyle();

    /**
     * @brief funzione per filtrare i dipendenti in base se o se non tipano su T
     * @param e: puntatore a Employee su cui verificare se tipa su T
     * @return true sse "e" tipa su T
     */
     template<class T>
    static bool employeesTypeFilter(Employee* e);

signals:
    void employeeListElementDoubleClickedEvent(Employee*);
    void modifyEmployeeEvent(Employee*);
    void deleteEmployeeEvent(Employee *);
    void insertEmployeeEvent();
    void importFileRequestEvent();
    void exportToFileRequestEvent();
    void exitApplicationEvent();

public slots:
    void deleteButtonClicked();
    void insertButtonClicked();
    void modifyButtonClicked();
    void employeeListElementDoubleClicked(EmployeeListElement* e);
    void importFile();
    void exportToFile();
    void exitApplication();
    void changeSelectedElementComboBox(const QString& selected);
    void cambioOrdine(const QString&);
    void filterByKeyword(const QString&);
};

template<class T> bool Gestionale::employeesTypeFilter(Employee* e){
    return dynamic_cast<T*>(e) != nullptr;
}

#endif // GESTIONALE_H
