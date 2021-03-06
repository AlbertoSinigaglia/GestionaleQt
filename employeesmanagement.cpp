#include "employeesmanagement.h"

std::shared_ptr<EmployeesManagement> EmployeesManagement::instance = nullptr;

EmployeesManagement::EmployeesManagement():
    employees(std::make_shared<DynamicArray<Employee*>>()),
    source(){}

std::shared_ptr<EmployeesManagement> EmployeesManagement::getInstance(){
    if(!EmployeesManagement::instance)
        EmployeesManagement::instance = std::shared_ptr<EmployeesManagement>(new EmployeesManagement);
    return EmployeesManagement::instance;
}

bool EmployeesManagement::import(const QString& path){
    try {
        auto empls = CSVReader::parse(path);
        employees->insert(employees->end(), empls.begin(), empls.end());
        if(source.isEmpty())
            source = path;
        return true;
    } catch (std::exception& e) {
        return false;
    }
}

void EmployeesManagement::save(const QString& source_){
    CSVWriter::write(source_.endsWith("qcsv") ? source_ : source_ + ".qcsv", *employees);
}

 std::shared_ptr<DynamicArray<Employee*>> EmployeesManagement::getEmployees() const{
    return employees;
}

QString EmployeesManagement::getOriginalSource() const{
    return source;
}

DynamicArray<AbstDataSection*> EmployeesManagement::serializeEmployee(Employee* e){
    DynamicArray<AbstDataSection*> vett;
    vett.push_back(new DatiPersona(e->getDatiPersona()));
    vett.push_back(new DatiLavoratore(e->getDatiLavoratore()));
    Software* p = dynamic_cast<Software*>(e);
    if(p){
        vett.push_back(new DatiDeveloping(p->getDatiDeveloping()));
        if(typeid(*e)==typeid(GUIDev)){
            GUIDev* p = dynamic_cast<GUIDev*>(e);
            vett.push_back(new DatiLatoClient(p->getDatiLatoClient()));
            vett.push_back(new DatiInterfacceUtente(p->getDatiInterfacceUtente()));
        }else if(typeid(*e)==typeid(DBDev)){
            DBDev* p = dynamic_cast<DBDev*>(e);
            vett.push_back(new DatiLatoServer(p->getDatiLatoServer()));
            vett.push_back(new DatiDatabase(p->getDatiDatabase()));
        }else if(typeid(*e)==typeid(FullStack)){
            FullStack* p = dynamic_cast<FullStack*>(e);
            vett.push_back(new DatiLatoServer(p->getDatiLatoServer()));
            vett.push_back(new DatiLatoClient(p->getDatiLatoClient()));
            vett.push_back(new DatiFullStack(p->getDatiFullStack()));
        }else if(typeid(*e)==typeid(ITSecurityDev)){
            ITSecurityDev* p = dynamic_cast<ITSecurityDev*>(e);
            vett.push_back(new DatiManutenzione(p->getDatiManutenzione()));
            vett.push_back(new DatiRipristinoSicurezza(p->getDatiRipristinoSicurezza()));}
    }else if(typeid(*e)==typeid(Tecnico)){
        Tecnico* p = dynamic_cast<Tecnico*>(e);
        vett.push_back(new DatiManutenzione(p->getDatiManutenzione()));
        vett.push_back(new DatiSistemi(p->getDatiSistemi()));
        vett.push_back(new DatiRiparazioneSistemi(p->getDatiRiparazioneSistemi()));
    }
    return vett;
}

void EmployeesManagement::addEmployee(Employee* e){
    employees->push_back(e);
}

void EmployeesManagement::deleteEmployee(Employee* e){
    for(auto it = employees->begin(); it != employees->end(); ++it){
        if(*it == e){
            employees->erase(it);
            break;
        }
    }
}

void EmployeesManagement::updateMonthAll(){
    for(auto e: *employees)
        e->aggiornaMese();
}


std::string EmployeesManagement::StdTypeEmployee(Employee* e){
    if(typeid(*e)==typeid(GUIDev)){
        return "GUIDev";
    }else if(typeid(*e)==typeid(DBDev)){
        return "DBDev";
    }else if(typeid(*e)==typeid(FullStack)){
        return "FullStack";
    }else if(typeid(*e)==typeid(ITSecurityDev)){
        return "ITSecurityDev";
    }else if(typeid(*e)==typeid(Tecnico)){
        return "Tecnico";
    }
    return "";
}
