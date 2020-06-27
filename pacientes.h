#include <iostream>
#include <ctype.h>
#include "fechapac.h"
#include <fstream>
#include "historias.h"

using namespace std;

struct nodo_pacientes
{
    string nombres;
    int cedula;
    string fnacimiento;
    char sexo;
    string direccion;
    historia_paciente historia=NULL;
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


apun_pacientes crearPaciente(int cedula){ ///llamado iniciar con un cin.ignore()
    apun_pacientes paciente;
    paciente=new(struct nodo_pacientes);
    cout<<"Registro nuevo paciente"<<endl;
    paciente->cedula=cedula;
    cin.ignore(256,'\n');
    cout<<"Introduzca nombre y apellido: ";
    paciente->nombres=lineasTextoExtensas();
    cout<<"Introduzca la direccion: ";
    paciente->direccion=lineasTextoExtensas();
    cout<<"Fecha nacimiento paciente "<<endl;
    paciente->fnacimiento=fechaPaciente();
    paciente->sexo=sexoPaciente();
    paciente->sig=NULL;
    return paciente;
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

void mostrarListaPaciente(apun_pacientes lista){
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
void imprimirPaciente(apun_pacientes paciente)
{
    cout <<"Paciente "<<endl;
    cout <<"1.Nombres y apellidos: "<<paciente->nombres<<endl;
    cout <<"2.Cedula: "<<paciente->cedula<<endl;
    cout <<"3.Fecha de nacimiento: "<<paciente->fnacimiento<<endl;
    cout <<"4.Sexo: "<<paciente->sexo<<endl;
    cout <<"5.Direccion: "<<paciente->direccion<<endl;

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

apun_pacientes buscarPaciente(apun_pacientes lista, int cedula) {
    apun_pacientes recorrido = lista;
    while (recorrido != NULL) {
        if (recorrido->cedula == cedula) 
            break;
        recorrido = recorrido->sig;
    }
    return (recorrido);
}
bool existePaciente(apun_pacientes lista_pacientes, int cedula) {
    apun_pacientes paciente;
    paciente = NULL;
    bool compro = false;
    if (lista_pacientes != NULL){
        paciente = lista_pacientes;
        while (paciente != NULL) {
            if (paciente->cedula == cedula) {
                compro = true;
                break;
            }
            paciente = paciente->sig;
        }
    }
    return (compro);
}
void campoModificarPaciente(apun_pacientes paciente){
    cout<<"Indique el numero de campo a modificar: "<<endl;
    int opcion=repetirEntero();
    while (opcion!=0)
    {
        switch (opcion)
        {
        case 0:
            break;
        case 1:
            cout<<"Introduzca nombre y apellido: ";
            paciente->nombres=lineasTextoExtensas();
            break;
        case 2:
            paciente->cedula=cedulaPaciente();
            break;
        case 3:
            paciente->fnacimiento=fechaPaciente();
            break;
        case 4:
            paciente->sexo=sexoPaciente();
            break;
        case 5:
            cout<<"Introduzca la direccion: ";
            paciente->direccion=lineasTextoExtensas();
            break;
        default:
            cout<<"Campo invalido"<<endl;
            break;
        }
        cout<<"Si desea modificar otro campo, coloque el numero, sino cooque 0: ";
        opcion=repetirEntero();
        cin.ignore(); 
    }
}
void cambiarArchivoCedula(int cedula_vieja, int cedula_nueva){
    ofstream aux;
    fstream archivo;
    string linea,cedula_v,cedula_n;
    cedula_v=to_string(cedula_vieja)+".txt";
    cedula_n=to_string(cedula_nueva)+".txt";
    archivo.open(cedula_v,ios::in);
    if(!archivo.fail())
    {
        aux.open(cedula_n,ios::out);
        if(!aux.fail()){
            while(!archivo.eof())
            {
                getline(archivo,linea);
                aux<<linea<<endl;
            }
            archivo.close();
        }
       
    }
    aux.close();
    remove(cedula_v.c_str());
}
void modificarPaciente(apun_pacientes lista_pacientes){
    int cedula,cond;
    cond=0;
    apun_pacientes paciente,aux;
    cedula=cedulaPaciente();
    if (existePaciente(lista_pacientes,cedula)){
        paciente=buscarPaciente(lista_pacientes,cedula);
        imprimirPaciente(paciente);
        cout<<endl;
        campoModificarPaciente(paciente);
        cout<<cedula<<endl;
        cout<<paciente->cedula<<endl;
        if(cedula!=paciente->cedula){
            cambiarArchivoCedula(cedula,paciente->cedula);
        }
        cout<<"Los datos del paciente fueros modificados correctamente"<<endl;
        cout<<"**********************"<<endl;
        imprimirPaciente(paciente);
        cout<<"**********************"<<endl;
        crearArchivoPaciente(lista_pacientes);
    }
    else
    {
        cout<<"No existen registros con esa cedula"<<endl;
    }
    
}
void crearListaPacientes(apun_pacientes &pacientes,int cedula)
{
    apun_pacientes aux1,aux2;

    aux1=crearPaciente(cedula);
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
    crearArchivoPaciente(lista_pacientes);

    
}

apun_pacientes ultimoPaciente(apun_pacientes lista){
    apun_pacientes aux=lista;
    while (aux->sig!=NULL)
    {
        aux=aux->sig;
    }
    return aux;
    
}
