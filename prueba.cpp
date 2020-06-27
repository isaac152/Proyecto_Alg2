#include <iostream>
#include <ctype.h>
#include <fstream>
#include "pacientes.h"

using namespace std;
void crearArchivo( ){
    fstream archivo;
    archivo.open("Pacientes/prueba.txt",ios::out);
    if(!archivo.fail())
        {
                archivo<<"prueba"<<endl;
                
        }
    archivo.close();
} 

int main(){
    int cedula;
    int b;
    int a=1;
    while (a==1)
        {
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
    mostrarLista(lista_pacientes);
    /*
    apun_pacientes paciente;

    leeArchivoPaciente(lista_pacientes);
    mostrarLista(lista_pacientes);
    modificarPaciente(lista_pacientes);
    /*
    cout<<"Introduzca cedula de paciente a cambiar: "<<endl;
    cin>>cedula;
    if(existePaciente(lista_pacientes,cedula)){
        paciente=buscarPaciente(lista_pacientes,cedula);
        crearListaHistoriaOrdenada(paciente->historia,paciente->cedula);
        mostrarListaHistoria(paciente->historia);
    }
    else
    {
        cout<<"No existe"<<endl;
    }*/
    
    return 0;
}
