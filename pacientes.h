#include <iostream>
#include <ctype.h>
#include "fechapac.h"
#include <fstream>

using namespace std;

struct nodo_pacientes
{
    string nombres;
    int cedula;
    string fnacimiento;
    char sexo;
    string direccion;
    struct nodo_pacientes *sig;
};
typedef struct nodo_pacientes *apun_pacientes;
apun_pacientes lista_pacientes=NULL;

bool cedulaRango(int numero){
    if ((numero>=100000) && (numero<=99999999)){
        return true;
    }
    else{
        return false;
    }
}

int cedulaPaciente(){
    string dato;
    bool confirmacion;
    while (!confirmacion){
        cout<<"Introduzca el numero de cedula: ";
        cin>>dato;
        cout<<endl;
        if(verificacionEntero(dato) && cedulaRango(stoi(dato))){
            return stoi(dato);
        }
        else
        {
            cout<<"Dato invalido. No puede contener letras o valores fuera del rango"<<endl;
            confirmacion=false;
        }
        
    }
}
char sexoPaciente(){
    char dato;
    bool confirmacion=false;
    while (!confirmacion){
        cout<<"Introduzca sexo del paciente M/F ";
        cin>>dato;
        cout<<endl;
        dato=toupper(dato);
        if ((!isdigit(dato)) && ((dato=='M') ||(dato=='F')))
        {
            return dato;
        }
        else
        {
            cout<<"Dato invalido, intentalo de nuevo"<<endl;
            confirmacion=false;
        }
    }
}


string lineasTexto(){
    char linea[500];
    linea[0]=' ';
    cin.getline(linea,500);
    cin.ignore();
    return linea;
    
}


apun_pacientes crearPaciente(){ ///llamado iniciar con un cin.ignore()
    apun_pacientes paciente;
    paciente=new(struct nodo_pacientes);
    cout<<"Registro nuevo paciente"<<endl;
    cout<<"Introduzca nombre y apellido: ";
    paciente->nombres=lineasTexto();
    paciente->cedula=cedulaPaciente();
    cout<<"Introduzca la direccion: ";
    cin.ignore();
    paciente->direccion=lineasTexto();
    paciente->fnacimiento=fechaNacPaciente();
    paciente->sexo=sexoPaciente();
    paciente->sig=NULL;
    return paciente;
};


void crearListaPacientes(apun_pacientes &pacientes)
{
    apun_pacientes aux1,aux2;

    aux1=crearPaciente();
    if (pacientes==NULL){
        pacientes=aux1;
    }
    else
    {
        aux2=pacientes;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=aux1;
    }
    
}
void crearListaPacientesArchivo(apun_pacientes &lista_paciente, apun_pacientes paciente )
{
    apun_pacientes aux2;

    if (lista_paciente==NULL){
        lista_paciente=paciente;
    }
    else
    {
        aux2=lista_paciente;
        while(aux2->sig!=NULL){
            aux2=aux2->sig;
        }
        aux2->sig=paciente;
    }
}   

//Funcion prueba

void mostrarLista(apun_pacientes lista){
    apun_pacientes recorrido;
    recorrido=lista;
    while(recorrido != NULL){
        cout<<recorrido->nombres<<endl;
        cout<<recorrido->cedula<<endl;
        cout<<recorrido->fnacimiento<<endl;
        cout<<recorrido->sexo<<endl;
        cout<<recorrido->direccion<<endl;
        recorrido=recorrido->sig;

    }

}

void crearArchivoPaciente(apun_pacientes lista_pacientes){
    ofstream aux;
    fstream archivo;
    apun_pacientes recorrido=lista_pacientes;
    archivo.open("pacientes.txt",ios::out);
    if(!archivo.fail())
        {
            while(recorrido !=NULL){
                archivo<<recorrido->nombres<<endl;
                archivo<<recorrido->cedula<<endl;
                archivo<<recorrido->fnacimiento<<endl;
                archivo<<recorrido->sexo<<endl;
                archivo<<recorrido->direccion<<endl;
                if (recorrido->sig!=NULL){
                    archivo<<"***********"<<endl;
                }
                else
                {
                    archivo<<"***********";
                }
                
                recorrido=recorrido->sig;
                
            }
        }
    archivo.close();
}
void leeArchivoPaciente(apun_pacientes &lista_pacientes){
    fstream archivo;
    string linea;
    apun_pacientes paciente,aux2;
    archivo.open("pacientes.txt",ios::in);
    if(!archivo.fail())
        {
            while(!archivo.eof())
            {
                paciente=new(struct nodo_pacientes);
                getline(archivo,paciente->nombres);
                getline(archivo,linea);
                paciente->cedula=stoi(linea);
                getline(archivo,paciente->fnacimiento);
                getline(archivo,linea);
                paciente->sexo=linea[0];
                getline(archivo,paciente->direccion);
                paciente->sig=NULL;
                crearListaPacientesArchivo(lista_pacientes,paciente);
                getline(archivo,linea);
            }
            
        }

}