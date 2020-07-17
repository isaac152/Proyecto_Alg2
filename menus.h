#include <iostream>
#include <stdlib.h>
#include "pacientes.h"
#include "cita.h"

using namespace std;

//Libreria que se encarga de mostrar y llevar acabo la logica de todos los menus de la app

//Funcion que imprime las opciones del menu principal
void interfazMenu(){
    cout<<"Bienvenido Dr "<<registro_doctor->nombre<<"---"<<registro_doctor->especializacion<<endl;
    cout<<"*********************"<<endl;
    cout<<"******opciones*******"<<endl;
    cout<<"*********************"<<endl;
    cout<<"1-Historias"<<endl;
    cout<<"2-Citas"<<endl;
    cout<<"3-Salir"<<endl;
}
//Funcion que imprime las opciones del menu de historia
void interfazMenuHistoria(){
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
//Funcion que imprime las opciones del menu de citas
void interfazMenuCitas(){
    int opcion;
    cout<<"******opciones*******"<<endl;
    cout<<"*********************"<<endl;
    cout<<"1-Nueva cita"<<endl;
    cout<<"2-Modificar cita"<<endl;
    cout<<"3-Mostrar cita para un paciente"<<endl;
    cout<<"4-Mostrar citas para una fecha"<<endl;
    cout<<"5-Mostrar citas para un rango de fechas"<<endl;
    cout<<"6-Regresar"<<endl;
}
//Funcion que se encarga de limpiar la pantalla solo windows
void limpiar(){
    cout<<"Presione una tecla para continuar"<<endl;
    cin.get();
    cin.get();
    system("clear");
}
//Funcion que se encarga de la logica tras el menu de historias con cada opcion
void menuHistoria(){
    int cedula;
    apun_pacientes paciente;
    apun_citas cambio_cita;
    int opcion=0;
    while (opcion!=7)
    {
        limpiar();
        interfazMenuHistoria();
        cout<<"Introduzca una opcion: ";
        opcion=repetirEntero();
        cin.ignore(); 
            system("clear");
        switch (opcion)
        {
            //nuevo paciente
        case 1:
            cedula=cedulaPaciente();
            cout<<'\n';
            if(!existePaciente(lista_pacientes,cedula)){
                crearListaPacientes(lista_pacientes,cedula);
            }
            else
            {
                cout<<"Paciente ya se encuentra registrado. Intente modificando"<<endl;
            }
            break;
            //modificar paciente
        case 2:
                cedula=cedulaPaciente();
                cout<<'\n';
                if (existePaciente(lista_pacientes,cedula)){
                    paciente=buscarPaciente(lista_pacientes,cedula);
                    modificarPaciente(paciente,cedula);

                    if ((paciente->cedula!=cedula)&&(citaCedula(lista_citas,cedula)))
                    {
                        cambiarCedulaCita(lista_citas,cedula,paciente->cedula);
                        crearArchivoCita(lista_citas);
                    }
                     
                }
                else
                {
                    cout<<"No existen registros con esa cedula"<<endl;
                }

            break;
            //nueva historia
        case 3:
            cedula=cedulaPaciente();
            cout<<'\n';
            if(existePaciente(lista_pacientes,cedula)){
                paciente=buscarPaciente(lista_pacientes,cedula);
                if(paciente->historia==NULL){
                    crearListaHistoriaOrdenada(paciente->historia,paciente->cedula); 
                    if (citaCedula(lista_citas,cedula))
                    {
                        eliminarCita(lista_citas,cedula);
                        crearArchivoCita(lista_citas);
                    }
                }
                else
                {
                    cout<<"Paciente ya tiene una historia. Intente actualizarla"<<endl;
                }
            }
            else
            {
                cout<<"Paciente no se encuentra registrado."<<endl;
            }
            break;
            //actualizar historia
        case 4:
                cedula=cedulaPaciente();
                cout<<'\n';
                if(existePaciente(lista_pacientes,cedula)){
                    paciente=buscarPaciente(lista_pacientes,cedula);
                    if(paciente->historia!=NULL){
                        mostrarListaHistoria(paciente->historia);
                        cout<<"*************"<<endl;
                        crearListaHistoriaOrdenada(paciente->historia,paciente->cedula);
                        if (citaCedula(lista_citas,cedula))
                            {
                                eliminarCita(lista_citas,cedula);
                                crearArchivoCita(lista_citas);
                            }
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
            //Modificar ultima historia
        case 5:
                cedula=cedulaPaciente();
                cout<<'\n';
                if(existePaciente(lista_pacientes,cedula)){
                    paciente=buscarPaciente(lista_pacientes,cedula);
                    modificarHistoria(paciente->historia);
                }
                else
                {
                    cout<<"Paciente no existe. Cree el paciente primero "<<endl;
                }
            break;
            //Mostrar la lista de historias de un paciente
        case 6:
            cedula=cedulaPaciente();
            cout<<'\n';
            if(existePaciente(lista_pacientes,cedula)){
                paciente=buscarPaciente(lista_pacientes,cedula);
                cout<<"Paciente: "<<paciente->nombres<<endl;
                mostrarListaHistoria(paciente->historia);
            }
            else
            {
                cout<<"No existe un paciente registrado con ese número de cédula"<<endl;
            }
            
            break;
            //Salir
        case 7:
            break;
        default:
            cout<<"Valor invalido. Intente de nuevo"<<endl;
            cin.get();
            break;
        }

    }

}
//Funcion que se encarga de llevar a cabo toda la logica tras el menu de citas
void menuCitas(){ 
    int cedula;
    int opcion=0;
    apun_pacientes paciente_cita;
    apun_citas cita_paciente;
    string consulta;
    while (opcion!=6)
    {
        limpiar();
        interfazMenuCitas();
        cout<<"Introduzca una opcion: ";
        opcion=repetirEntero();
        cin.ignore(); 
        system("clear");
        switch (opcion)
        {
            //Nueva cita
        case 1:
            cedula=cedulaPaciente();
            cout<<'\n';
            if(!citaCedula(lista_citas,cedula)){
                if(existePaciente(lista_pacientes,cedula)){
                    paciente_cita=buscarPaciente(lista_pacientes,cedula);
                    cout<<'\n';
                    cout<<"****************"<<endl;
                    imprimirPaciente(paciente_cita);
                    cout<<"****************"<<endl;
                    crearListaCitas(lista_citas,cedula);
                }
                else
                {
                    cout<<"Primera vez en el consultorio."<<endl;
                    crearListaCitas(lista_citas,cedula);

                }
            }
            else
            {
                cout<<"Ya existe una cita con esta cedula. Intente modificarla"<<endl;
            }
                      
            break;
            //Modificar cita
        case 2:
            cedula=cedulaPaciente();
            cout<<'\n';
            if(citaCedula(lista_citas,cedula)){
                
                cita_paciente=buscarCitaCedula(lista_citas,cedula);
                modificarCita(cita_paciente);
                crearArchivoCita(lista_citas);
            }
            else
            {
                cout<<"Cita no existe"<<endl;
            }
            break;
            //Mostrar cita para un paciente
        case 3:
            cedula=cedulaPaciente();
            cout<<'\n';
            if(citaCedula(lista_citas,cedula)){
                cita_paciente=buscarCitaCedula(lista_citas,cedula);
                mostrarCita(cita_paciente);   
            }
            else
            {
                cout<<"No existe cita registrada con ese numero de cedula"<<endl;
            }       
            break;
            //Mostrar cita para una fecha
        case 4:
            cout<<"Indique la fecha de las citas: "<<endl;
            consulta=fechaCita();
            cout<<'\n';
            if(existeFechaCita(lista_citas,consulta)){
                cita_paciente=buscarCitaFecha(lista_citas,consulta);
                mostrarVariasFechasCitas(lista_citas,cita_paciente);
            }
            else
            {
                cout<<"No existen consultas para esta fecha."<<endl;
            }
            break;
            //Mostrar cita para un rango de fechas
        case 5:
            mostrarRangoFechasCitas(lista_citas);
            break;
            //salir
        case 6:
            break;
        default:
            cout<<"Valor invalido. Intente de nuevo"<<endl;
            cin.get();
            break;
        }
    }

}

//Funcion que lleva la logica del menu principal de la app y hace un llamado a los otros menus
void logicaMenu(){
    int opcion=0;
    while (opcion!=3)
    {
    interfazMenu();
    opcion=repetirEntero();
        switch (opcion)
        {
        case 1:
            system("clear");
            menuHistoria();
            break;
        case 2:
            system("clear");
            menuCitas();
            break;
        case 3:
            break;
        
        default:
            cout<<"Valor invalido. Intente de nuevo"<<endl;
            cin.get();
            break;
        }
    limpiar();
    }

}

