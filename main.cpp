#include <iostream>
#include <string>
#include "doctor-sesion.h"
#include "menus.h"
#include <stdio.h>
using namespace std;

//Archivo principal de la app
//Cuando el usuario logre comprobar su indetidad se van a cargar datos guardados del programa 
//Se lee el archivo de pacientes, se genera las fechas del anio, se lee el archivo de citas.
//Por ultimo se carga el menu para que pueda interactuar
int main(){
    bool a=true;
    if(inicioSesion()){
            leeArchivoPaciente(lista_pacientes);
            registro_doctor->anio_sesion;
            generarFecha(calendario_app);
            leerArchivoCita(lista_citas);
            limpiar();
            logicaMenu();
            limpiar();
            a=false;
    }
    
    return 0;
}