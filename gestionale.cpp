#include "gestionale.h"
#include "models/headers/BackDev.h"
#include "widgets/employeelistelement.h"
#include "widgets/aboutus.h"
#include <QLineEdit>

Gestionale::Gestionale(QWidget *parent): QWidget(parent), model(nullptr){
    this->setMinimumSize(1280, 800);
    mainLayout = new QHBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    addMenu();
    addBoxSinistro();
    addBoxDestro();
    setLayout(mainLayout);
    connect(
        c_nome,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::Name, state);
        }
    );
    connect(
        c_cognome,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::Surname, state);
        }
    );
    connect(
        c_cf,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::CF, state);
        }
    );
    connect(
        c_dataNascita,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::DateOfBirth, state);
        }
    );

    connect(
        DataA,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::DateOfEmployment, state);
        }
    );
    connect(
        DataFineContratto,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::DateEndOfContract, state);
        }
    );
    connect(
        StipendioBase,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::Salary, state);
        }
    );
    connect(
        OreLavoro,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::WeeklyHours, state);
        }
    );
    connect(
        produttivo,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::Produttivo, state);
        }
    );
    connect(
        bonus_stipendio,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::BonusStipendio, state);
        }
    );
    connect(
        grado_esperienza,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::GradoEsperienza, state);
        }
    );
    connect(
        numero_righe_totali,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::NumeroRigheTotali, state);
        }
    );
    connect(
        linguaggio,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::Linguaggio, state);
        }
    );
    connect(
        percentuale_ripristino,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::PercentualeRipristino, state);
        }
    );
    connect(
        numero_criticita_risolte,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::NumeroCriticitaRisolte, state);
        }
    );
    connect(
        ore_straordinari,&QCheckBox::stateChanged,
        [=](int state){
            employeesList->changeListAttributeVisibility(EmployeeListElement::OreStraordinari, state);
        }
    );
    connect(elimina, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    connect(inserisci, SIGNAL(clicked()), this, SLOT(insertButtonClicked( )));
    connect(modifica, SIGNAL(clicked()), this, SLOT(modifyButtonClicked( )));
    connect(employeesList, SIGNAL(ListElementDoubleClicked(EmployeeListElement*)), this, SLOT(employeeListElementDoubleClicked( EmployeeListElement* )));
    connect(a_import, &QAction::triggered, this, &Gestionale::importFile);
    connect(a_open, &QAction::triggered, this, &Gestionale::importFile);
    connect(a_export, &QAction::triggered, this, &Gestionale::exportToFile);
    connect(a_exit, &QAction::triggered, this, &Gestionale::exitApplication);
    connect(a_aboutUs,&QAction::triggered, [=](){
        AboutUs about;
        about.setModal(true);
        about.exec();
    });
    connect(Dipendenti, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(changeSelectedElementComboBox(const QString&)));
    connect(ordine, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(cambioOrdine(const QString&)));
    connect(name, &QLineEdit::textChanged, this, &Gestionale::filterByKeyword);
    setStyle();
    setEnabled(false);setEnabled(true);
    resize(this->width(), layoutFrameFiltri->sizeHint().height());
}

Gestionale::~Gestionale() = default;

void Gestionale::addBoxSinistro(){
    auto* frameFiltri = new QFrame(this);
    frameFiltri->setFixedWidth(250);
    layoutFrameFiltri = new QVBoxLayout(frameFiltri);
    layoutFrameFiltri->setAlignment(Qt::AlignTop);
    auto scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setObjectName("scroll-left");
    scroll->setFixedWidth(270);
    scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scroll->setWidget(frameFiltri);
    scroll->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(scroll);
    addTitleSinistro();
    addEmployeesFilters();
    addFirstBox();
    addOrdineBox();
    addAzioni();
}

void Gestionale::addTitleSinistro(){
    QLabel* Visualizza = new QLabel("Metriche visualizzazione:", this, Qt::WindowFlags());
    Visualizza->setObjectName("title-left");
    layoutFrameFiltri->addWidget(Visualizza);
}

void Gestionale::addOrdineBox(){
    auto q = new QGroupBox(this);
    q->setTitle("Ordinamento");
    QVBoxLayout* lq = new QVBoxLayout(q);
    ordine = new QComboBox(this);
    ordine->addItems({
         "Nome",
         "Cognome",
         "Codice fiscale",
         "Data di nascita",
         "Data assuzione",
         "Data fine contratto",
         "Stipendio base mensile",
         "Bonus stipendio",
         "Ore di lavoro settimanale",
         "Grado esperienza",
         "Produttività"
    });
    lq->addWidget(ordine);
    layoutFrameFiltri->addWidget(q);
}

void Gestionale::addEmployeesFilters(){
    QGroupBox* filtri = new QGroupBox(this);
    filtri->setTitle("Filtri");
    QVBoxLayout* lfiltri = new QVBoxLayout(filtri);
    name = new QLineEdit(filtri);
    name->setPlaceholderText("Nome Dipendente");
    name->setStyleSheet("width:100%; background-color:white; padding:5px; color:black;");
    Dipendenti = new QComboBox(this);
    Dipendenti->addItems({
        "Tutti",
        "Manutentore",
        "Hardware",
        "Software",
        "BackDeveloper",
        "FrontDeveloper",
        "FullStack",
        "DBDeveloper",
        "GUIDeveloper",
        "ITSecurityDev",
        "Tecnico"
    });
    QLabel* name_l = new QLabel("Per nome/cognome:", filtri);
    name_l->setStyleSheet("font-size:15px; color:white;");
    QLabel* type_l = new QLabel("Per tipo di dipendente:", filtri);
    type_l->setStyleSheet("font-size:15px; color:white;");
    lfiltri->addWidget(name_l);
    lfiltri->addWidget(name);
    lfiltri->addWidget(type_l);
    lfiltri->addWidget(Dipendenti);
    layoutFrameFiltri->addWidget(filtri);
}

void Gestionale::addFirstBox(){
    Visualizzare = new QGroupBox(this);
	Visualizzare->setTitle("Cosa Visualizzare");
    LayoutVisualizzare = new QVBoxLayout(Visualizzare);
    layoutFrameFiltri->addWidget(Visualizzare);
	addBoxPersona();
    addBoxLavoro();
    addBoxSpecifico();
}

void Gestionale::addBoxPersona(){
    QGroupBox* DatiPersona = new QGroupBox(this);
    DatiPersona->setObjectName("dati-persona-left");
	DatiPersona->setTitle("Dati della persona");
    QVBoxLayout* layoutDatiPersona = new QVBoxLayout(DatiPersona);
    c_cognome = new QCheckBox("Cognome",this);
    layoutDatiPersona->addWidget(c_cognome);
    c_nome = new QCheckBox("Nome",this);
    layoutDatiPersona->addWidget(c_nome);
    c_cf = new QCheckBox("Codice Fiscale",this);
    layoutDatiPersona->addWidget(c_cf);
    c_dataNascita = new QCheckBox("Data di nascita",this);
    layoutDatiPersona->addWidget(c_dataNascita);
    c_nome->setCheckState(Qt::CheckState::Checked);
    c_cognome->setCheckState(Qt::CheckState::Checked);
    c_cf->setCheckState(Qt::CheckState::Checked);
    c_dataNascita->setCheckState(Qt::CheckState::Checked);
	LayoutVisualizzare->addWidget(DatiPersona);
}

void Gestionale::addBoxLavoro(){
	QGroupBox* DatiDip = new QGroupBox(this);
	DatiDip->setTitle("Dati relativi al lavoro");
	QVBoxLayout* layoutDatiDip = new QVBoxLayout(DatiDip);
    DataA = new QCheckBox("Data assunzione",this);
	layoutDatiDip->addWidget(DataA);
    DataFineContratto = new QCheckBox("Data fine contratto",this);
	layoutDatiDip->addWidget(DataFineContratto);
    StipendioBase = new QCheckBox("Stipendio Base \nMensile",this);
	layoutDatiDip->addWidget(StipendioBase);
    OreLavoro= new QCheckBox("Ore di lavoro \nsettimanale",this);
    layoutDatiDip->addWidget(OreLavoro);

    bonus_stipendio= new QCheckBox("Bonus stipendio",this);
    grado_esperienza= new QCheckBox("Grado esperienza",this);
    layoutDatiDip->addWidget(bonus_stipendio);
    layoutDatiDip->addWidget(grado_esperienza);
    bonus_stipendio->setCheckState(Qt::CheckState::Checked);
    grado_esperienza->setCheckState(Qt::CheckState::Checked);

    DataA->setCheckState(Qt::CheckState::Checked);
    DataFineContratto->setCheckState(Qt::CheckState::Checked);
    StipendioBase->setCheckState(Qt::CheckState::Checked);
    OreLavoro->setCheckState(Qt::CheckState::Checked);
	LayoutVisualizzare->addWidget(DatiDip);
}

void Gestionale::addBoxSpecifico(){
    QGroupBox* DatiSpecifici = new QGroupBox(this);
    DatiSpecifici->setTitle("Dati specifici");
    QVBoxLayout* layoutDatiSpecifici = new QVBoxLayout(DatiSpecifici);
    produttivo = new QCheckBox("Produttivo",this);
    produttivo->show();
    produttivo->setCheckState(Qt::CheckState::Checked);
    layoutDatiSpecifici->addWidget(produttivo);

    numero_righe_totali= new QCheckBox("Numero righe \ndi codice totali",this);
    linguaggio= new QCheckBox("Linguaggio preferito",this);
    percentuale_ripristino= new QCheckBox("Percentuale ripristino",this);
    numero_criticita_risolte= new QCheckBox("Numero criticità \n risolte",this);
    ore_straordinari= new QCheckBox("Ore straordinari",this);

    layoutDatiSpecifici->addWidget(numero_righe_totali);
    layoutDatiSpecifici->addWidget(linguaggio);
    layoutDatiSpecifici->addWidget(percentuale_ripristino);
    layoutDatiSpecifici->addWidget(numero_criticita_risolte);
    layoutDatiSpecifici->addWidget(ore_straordinari);

    numero_righe_totali->hide();
    linguaggio->hide();
    percentuale_ripristino->hide();
    numero_criticita_risolte->hide();
    ore_straordinari->hide();

    numero_righe_totali->setCheckState(Qt::CheckState::Unchecked);
    linguaggio->setCheckState(Qt::CheckState::Unchecked);
    percentuale_ripristino->setCheckState(Qt::CheckState::Unchecked);
    numero_criticita_risolte->setCheckState(Qt::CheckState::Unchecked);
    ore_straordinari->setCheckState(Qt::CheckState::Unchecked);

    LayoutVisualizzare->addWidget(DatiSpecifici);
}

void Gestionale::addAzioni(){
	QGroupBox* Azioni = new QGroupBox(this);
	Azioni->setTitle("Azioni sui dipendenti");
    Azioni->setObjectName("azioni-left");
	QVBoxLayout* layoutAzioni = new QVBoxLayout(Azioni);
    inserisci = new QPushButton("Inserisci",Azioni);
    layoutAzioni->addWidget(inserisci);
    modifica = new QPushButton("Modifica",Azioni);
    layoutAzioni->addWidget(modifica);
    elimina = new QPushButton("Elimina",Azioni);
    layoutAzioni->addWidget(elimina);
    layoutFrameFiltri->addWidget(Azioni);
}

void Gestionale::addBoxDestro(){
    auto scroll = new QScrollArea();
    scroll->setContentsMargins(0,0,0,0);
    scroll->setWidgetResizable(true);
    scroll->setObjectName("scroll-right");
    scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    employeesList = new EmployeesList(this);
    scroll->setWidget(employeesList);
    mainLayout->addWidget(scroll);
}

void Gestionale::addMenu(){
    QMenuBar* menuBar = new QMenuBar();
    menuBar->setStyleSheet("color:white; background-color:#424242;");
    QMenu * menu = new QMenu("File");
    menuBar->addMenu(menu);
    a_open = new QAction("Apri...", menuBar);
    a_open->setShortcut(Qt::Key_O | Qt::CTRL);
    a_import = new QAction("Importa da...", menuBar);
    a_import->setIcon(QIcon(":/resources/import_icon.png"));
    a_import->setShortcut(Qt::Key_I | Qt::CTRL);
    a_export = new QAction("Esporta a...", menuBar);
    a_export->setIcon(QIcon(":/resources/export_icon.png"));
    a_export->setShortcut(Qt::Key_E | Qt::CTRL);
    a_import->setDisabled(true);
    a_export->setDisabled(true);
    a_exit = new QAction("Esci", menuBar);
    a_exit->setIcon(QIcon(":/resources/exit_icon.png"));
    a_exit->setShortcut(Qt::Key_Q | Qt::CTRL);
    menu->addAction(a_open);
    menu->addAction(a_import);
    menu->addAction(a_export);
    menu->addSeparator();
    menu->addAction(a_exit);
    menu->setMinimumWidth(200);
    aboutUs = new QMenu("Help");
    a_aboutUs = new QAction("Informazioni su MyGestionale", aboutUs);
    aboutUs->addAction(a_aboutUs);
    menuBar->addMenu(aboutUs);
    aboutUs->setMinimumWidth(200);
    mainLayout->setMenuBar(menuBar);
}

void Gestionale::setStyle(){
	QFile file(":/resources/style.css");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	setStyleSheet(styleSheet);
}


void Gestionale::showLiquidation(QString nome, float quota_liquidazione){
    QString testo= QString("Per liquidare ")+ nome + QString(" l'azienda deve lui una retribuzione di: ")+ QString::number(quota_liquidazione)+"€";
    QMessageBox(QMessageBox::Information, "Liquidazione", testo, QMessageBox::Ok).exec();
}

void Gestionale::deleteButtonClicked(){
    auto e = employeesList->getCurrent();
    if(e){
        QMessageBox msgBox(this);
        msgBox.setStyleSheet("QLabel{min-width: 300px;}");
        msgBox.setText(QString("Stai per eliminare ") + QString(e->getNome().c_str()) + QString(" ") + QString(e->getCognome().c_str()));
        msgBox.setInformativeText("Sicuro di voler procedere?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int resp = msgBox.exec();
        if(resp == QMessageBox::Yes)
            emit deleteEmployeeEvent(employeesList->getCurrent());
    } else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Nessun dipendente selezionato", "Nessun dipendente selezionato, vuoi crearne uno?",QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes) this->insertButtonClicked() ;
    }
}

void Gestionale::insertButtonClicked(){
    emit insertEmployeeEvent();
}

void Gestionale::modifyButtonClicked(){
    emit modifyEmployeeEvent(employeesList->getCurrent());
}

void Gestionale::employeeListElementDoubleClicked(EmployeeListElement* e){
    emit employeeListElementDoubleClickedEvent(e->getEmployee());
}

void Gestionale::setModel(std::shared_ptr<EmployeesManagement> model_){
    model = model_;
}

void Gestionale::updateList() const{
    if(model){
        this->employeesList->setEmployees(*model->getEmployees());
        this->ordine->setCurrentText("Nome");
        this->employeesList->orderBy(EmployeeListElement::Name);
        name->setText({});
    }
}

bool Gestionale::disableSaveEnableImport(){
    bool to_r = a_open->isEnabled();
    a_open->setDisabled(true);
    a_import->setDisabled(false);
    a_export->setDisabled(false);
    return to_r;
}

void Gestionale::importFile(){
    emit importFileRequestEvent();
}

void Gestionale::exportToFile(){
    emit exportToFileRequestEvent();
}
void Gestionale::exitApplication(){
    emit exitApplicationEvent();
}

void Gestionale::changeSelectedElementComboBox(const QString& selected){
    name->setText({});
    Dipendenti->setCurrentText(selected);
    numero_righe_totali->setCheckState(Qt::CheckState::Unchecked);
    linguaggio->setCheckState(Qt::CheckState::Unchecked);
    percentuale_ripristino->setCheckState(Qt::CheckState::Unchecked);
    numero_criticita_risolte->setCheckState(Qt::CheckState::Unchecked);
    ore_straordinari->setCheckState(Qt::CheckState::Unchecked);
    numero_righe_totali->hide();
    linguaggio->hide();
    percentuale_ripristino->hide();
    numero_criticita_risolte->hide();
    ore_straordinari->hide();

    employeesList->changeListAttributeVisibility(
             EmployeeListElement::NumeroRigheTotali |
             EmployeeListElement::Linguaggio |
             EmployeeListElement::PercentualeRipristino |
             EmployeeListElement::NumeroCriticitaRisolte |
             EmployeeListElement::OreStraordinari ,
             static_cast<int>(false)
     );
    if(selected=="Manutentore"){
        percentuale_ripristino->show();
        percentuale_ripristino->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<Manutenzione>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::PercentualeRipristino, true
        );
    }
    else if(selected=="FrontDeveloper"){
        linguaggio->show();
        numero_righe_totali->show();
        linguaggio->setCheckState(Qt::CheckState::Checked);
        numero_righe_totali->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<FrontDev>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::NumeroRigheTotali | EmployeeListElement::Linguaggio, true
        );
    }
    else if(selected=="FullStack"){
        linguaggio->show();
        numero_righe_totali->show();
        linguaggio->setCheckState(Qt::CheckState::Checked);
        numero_righe_totali->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<FullStack>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::NumeroRigheTotali | EmployeeListElement::Linguaggio, true
        );
    }
    else if(selected=="GUIDeveloper"){
        linguaggio->show();
        numero_righe_totali->show();
        linguaggio->setCheckState(Qt::CheckState::Checked);
        numero_righe_totali->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<GUIDev>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::NumeroRigheTotali | EmployeeListElement::Linguaggio, true
        );
    }
    else if(selected=="Hardware"){
        employeesList->filter(employeesTypeFilter<Hardware>);
    }
    else if(selected=="Software"){
        linguaggio->show();
        numero_righe_totali->show();
        linguaggio->setCheckState(Qt::CheckState::Checked);
        numero_righe_totali->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<Software>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::NumeroRigheTotali | EmployeeListElement::Linguaggio, true
        );
    }
    else if(selected=="ITSecurityDev"){
        linguaggio->show();
        numero_righe_totali->show();
        percentuale_ripristino->show();
        numero_criticita_risolte->show();
        linguaggio->setCheckState(Qt::CheckState::Checked);
        numero_righe_totali->setCheckState(Qt::CheckState::Checked);
        percentuale_ripristino->setCheckState(Qt::CheckState::Checked);
        numero_criticita_risolte->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<ITSecurityDev>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::PercentualeRipristino | EmployeeListElement::NumeroCriticitaRisolte | EmployeeListElement::NumeroRigheTotali | EmployeeListElement::Linguaggio, true
        );
    }
    else if(selected=="Tecnico"){
        percentuale_ripristino->show();
        ore_straordinari->show();
        percentuale_ripristino->setCheckState(Qt::CheckState::Checked);
        ore_straordinari->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<Tecnico>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::OreStraordinari | EmployeeListElement::PercentualeRipristino, true
        );
    }
    else if(selected=="BackDeveloper"){
        linguaggio->show();
        numero_righe_totali->show();
        linguaggio->setCheckState(Qt::CheckState::Checked);
        numero_righe_totali->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<BackDev>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::NumeroRigheTotali | EmployeeListElement::Linguaggio, true
        );
    }
    else if(selected=="DBDeveloper"){
        linguaggio->show();
        numero_righe_totali->show();
        linguaggio->setCheckState(Qt::CheckState::Checked);
        numero_righe_totali->setCheckState(Qt::CheckState::Checked);
        employeesList->filter(employeesTypeFilter<DBDev>);
        employeesList->changeListAttributeVisibility(
            EmployeeListElement::NumeroRigheTotali | EmployeeListElement::Linguaggio, true
        );
    }
    else if(selected=="Tutti"){
        employeesList->filter(employeesTypeFilter<Employee>);
    }
}

void Gestionale::cambioOrdine(const QString& index){
    if("Nome" == index) employeesList->orderBy(EmployeeListElement::Name);
    if("Cognome" == index) employeesList->orderBy(EmployeeListElement::Surname);
    if("Codice fiscale" == index) employeesList->orderBy(EmployeeListElement::CF);
    if("Data di nascita" == index) employeesList->orderBy(EmployeeListElement::DateOfBirth);
    if("Data assuzione" == index) employeesList->orderBy(EmployeeListElement::DateOfEmployment);
    if("Data fine contratto" == index) employeesList->orderBy(EmployeeListElement::DateEndOfContract);
    if("Stipendio base mensile" == index) employeesList->orderBy(EmployeeListElement::Salary);
    if("Bonus stipendio" == index) employeesList->orderBy(EmployeeListElement::BonusStipendio);
    if("Ore di lavoro settimanale" == index) employeesList->orderBy(EmployeeListElement::WeeklyHours);
    if("Grado esperienza" == index) employeesList->orderBy(EmployeeListElement::GradoEsperienza);
    if("Produttività" == index) employeesList->orderBy(EmployeeListElement::Produttivo);
    emit name->textChanged(name->text());
}

void Gestionale::filterByKeyword(const QString &to_search){
    employeesList->filter([&](Employee* e) -> bool{
        if(to_search.isEmpty()) return true;
        QString search = to_search.simplified();
        search.replace(" ", "");
        QString source_name_surname = (QString(e->getDatiPersona().nome.c_str()) + " " + QString(e->getDatiPersona().cognome.c_str())).simplified().toLower();
        source_name_surname.replace(" ", "");
        QString source_surname_name = (QString(e->getDatiPersona().cognome.c_str()) + " " + QString(e->getDatiPersona().nome.c_str())).simplified().toLower();
        source_surname_name.replace(" ", "");
        return search.contains(source_name_surname) || source_name_surname.contains(search) ||
                search.contains(source_surname_name) || source_surname_name.contains(search) ;
    });
}
