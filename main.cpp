#include <iostream>
#include "menu.h"
#include "doctorsesion.h"

using namespace std;


//Archivo principal de la app
int main(){
    bool a=true;
    if(inicioSesion(registro_doctor)){
            cout<<"acaaa"<<endl;
            leeArchivoPaciente(lista_pacientes);
            cout<<"aca"<<endl;
            logicaMenu();
            a=false;
    }
    

    return 0;
}