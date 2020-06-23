#include <iostream>
#include <ctype.h>
#include <fechapac.h>
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
    bool confirmacion;
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
apun_pacientes crearPaciente(){
    apun_pacientes paciente;
    paciente=new(struct nodo_pacientes);
    cout<<"Registro nuevo paciente"<<endl;
    cout<<"Introduzca nombre y apellido: ";
    cin>>paciente->nombres;
    cout<<endl;
    paciente->cedula=cedulaPaciente();
    cout<<"Introduzca la direccion: ";
    cin>>paciente->direccion;
    cout<<endl;
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