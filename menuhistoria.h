#include <iostream>
#include <stdlib.h>
#include "pacientes.h"
#include "pruebacita.h"

using namespace std;


void interfazMenuHistoria(){
    int opcion;
    cout<<"******opciones*******"<<endl;
    cout<<"*********************"<<endl;
    cout<<"1-Nuevo paciente"<<endl;
    cout<<"2-Modificar informacion paciente"<<endl;
    cout<<"3-Nueva historia medica"<<endl;
    cout<<"4-Actualizar historia de un paciente"<<endl;
    cout<<"5-Modificar historia de un paciente"<<endl;
    cout<<"6-Mostrar historia de un paciente"<<endl;
    cout<<"7-Regresar"<<endl;
}

void menuHistoria(){ //flush por cada reintento
    int cedula;
    apun_pacientes paciente;
    int opcion=0;
    while (opcion!=7)
    {
        interfazMenuHistoria();
        opcion=repetirEntero();
        cin.ignore(); 
        switch (opcion)
        {
        case 1:
            cedula=cedulaPaciente();
            if(!existePaciente(lista_pacientes,cedula)){
                crearListaPacientes(lista_pacientes,cedula);
            }
            else
            {
                cout<<"Paciente ya se encuentra registrado. Intente modificando"<<endl;
            }
            break;
        case 2:
                modificarPaciente(lista_pacientes);        
            break;
        case 3:
            cedula=cedulaPaciente();
            if(existePaciente(lista_pacientes,cedula)){
                paciente=buscarPaciente(lista_pacientes,cedula);
                crearListaHistoriaOrdenada(paciente->historia,paciente->cedula); 
                
            }
            else
            {
                cout<<"Paciente no se encuentra registrado."<<endl;
            }
            break;
        case 4:
                cedula=cedulaPaciente();
                if(existePaciente(lista_pacientes,cedula)){
                    paciente=buscarPaciente(lista_pacientes,cedula);
                    if(paciente->historia!=NULL){
                        mostrarListaHistoria(paciente->historia);
                        cout<<"*************"<<endl;
                        crearListaHistoriaOrdenada(paciente->historia,paciente->cedula);
                    }
                    else
                    {
                        cout<<"Paciente no tiene historia, registrela primero"<<endl;
                    }
                    
                }
                else
                {
                    cout<<"Paciente no existe. Cree el paciente primero "<<endl;
                }
                
            break;
        case 5:
                cedula=cedulaPaciente();
                if(existePaciente(lista_pacientes,cedula)){
                    paciente=buscarPaciente(lista_pacientes,cedula);
                    modificarHistoria(paciente->historia);
                }
                else
                {
                    cout<<"Paciente no existe. Cree el paciente primero "<<endl;
                }
            break;
        case 6:
                cedula=cedulaPaciente();
            if(existePaciente(lista_pacientes,cedula)){
                paciente=buscarPaciente(lista_pacientes,cedula);
                cout<<"Paciente: "<<paciente->nombres<<endl;
                mostrarListaHistoria(paciente->historia);
            }
            else
            {
                cout<<"Paciente no existe. Cree el paciente primero"<<endl;
            }
            
            break;
        case 7:
            break;
        default:
            cout<<"Valor invalido. Intente de nuevo"<<endl;
            cin.get();
            break;
        }

    }

}
