#include <iostream>
#include "doctor-sesion.h"
#include "menu.h"
#include "pacientes.h"
using namespace std;


//Archivo principal de la app
int main(){
    /*
    int b;
    int a=1;
    while (a==1)
        {
            cin.ignore();
            crearListaPacientes(lista_pacientes);
            cout<<"**********"<<endl;
            cout<<"Quieres introducir otro paciente?"<<endl;
            cin>>b;
            if (b==0){
                a=0;
            }
            else
            {
                a=1;
            }
            
        }
        */
    leeArchivoPaciente(lista_pacientes);
    mostrarLista(lista_pacientes);

/*
    if(inicioSesion()){
        interfazMenu();

    }*/
    return 0;
}