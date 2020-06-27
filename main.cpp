#include <iostream>
#include "doctor-sesion.h"
#include "menu.h"
using namespace std;


//Archivo principal de la app
int main(){
    bool a=true;
    if(inicioSesion()){
            leeArchivoPaciente(lista_pacientes);
            logicaMenu();
            a=false;
    }
    

    return 0;
}