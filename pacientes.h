#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string>
#include "fechapac.h"
#include "historias.h"
using namespace std;
//Libreria que se encarga de agrupar todas las funciones relacionadas con los pacientes. 
//Es una libreria padre de historia y fecha paciente.

//Estructura de nodo paciente
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
//Variable global con la lista de los pacientes
apun_pacientes lista_pacientes=NULL;

//Funcion que se encarga de evaluar si un entero recibido como parametro, se encuentra en el rango 
//establecido para las cedulas. Devuelve el booleano que sea equivalente a dicha comparacion
bool cedulaRango(int numero){
    if ((numero>=100000) && (numero<=99999999)){
        return true;
    }
    else{
        return false;
    }
}
//Funcion que se encarga de pedir un numero de cedula y hacer las comprobaciones necesarias con 
//funciones auxiliares para luego regresar dicho valor como entero
int cedulaPaciente(){
    string dato;
    bool confirmacion=false;
    while (!confirmacion){
        cout<<"Introduzca el numero de cedula: ";
        cin>>dato;
        if(verificacionEntero(dato) && cedulaRango(stoi(dato))){
            return stoi(dato);
        }
        else
        {
            cout<<"Dato invalido. No puede contener letras o valores fuera del rango"<<endl;
            confirmacion=false;
        }
        
    }
    return 0;
}
//Funcion que se encarga de pedir un caracter que indique si el paciente es masculino o femenino
//se realizan las comprobaciones necesarias y si todo funciona devuelve dicho caracter
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
    return ' ';
}

//Funcion que se encarga de crear un nodo de paciente. Recibe como parametro la cedula del paciente y retorna dicho nodo
apun_pacientes crearPaciente(int cedula){ 
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
    paciente->historia=NULL;
    paciente->sig=NULL;
    return paciente;
}
//Funcion que se encarga de crear la lista de los pacientes a partir de los datos leidos de un archivo
//Recibe como parametro la lista de pacientes (global y por referencia) y el paciente que fue creado a partir
//de la lectura del archivo
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
//Funcion auxiliar que se encarga de mostrar toda la lista de pacientes. No esta implementada en el codigo base
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
//Funcion que se encarga de imprimir el nodo paciente que fue recibido como parametro, indicando sus caracteristicas
void imprimirPaciente(apun_pacientes paciente)
{
    cout <<"Paciente "<<endl;
    cout <<"1.Nombres y apellidos: "<<paciente->nombres<<endl;
    cout <<"2.Cedula: "<<paciente->cedula<<endl;
    cout <<"3.Fecha de nacimiento: "<<paciente->fnacimiento<<endl;
    cout <<"4.Sexo: "<<paciente->sexo<<endl;
    cout <<"5.Direccion: "<<paciente->direccion<<endl;

}
//Funcion que se encarga de guardar los datos de la lista de pacientes en un archivo plano
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
//Funcion que se encarga de leer el contenido de un archivo plano y crear una lista pacientes a partir de esos datos
//Hace un llamado a la funcion crearListaPacientesArchivo tras cada paciente leido.
//Recibe como parametro por referencia a la lista de pacientes (global)
void leeArchivoPaciente(apun_pacientes &lista_pacientes){
    fstream archivo;
    string linea;
    historia_paciente historia;
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
                if(existeArchivoHistoria(paciente->cedula)){
                    historia=leerArchivoHistoria(paciente->cedula);
                    paciente->historia=historia;
                 }
                 else
                {
                      paciente->historia=NULL;
                }
                paciente->sig=NULL;
                crearListaPacientesArchivo(lista_pacientes,paciente);
                getline(archivo,linea);
            }
            
        }

}
//Funcion que se encarga de buscar y devolver un paciente en concreto a partir de su numero de cedula
//Recibe como parametro la lista de pacientes y la cedula como entero
apun_pacientes buscarPaciente(apun_pacientes lista, int cedula) {
    apun_pacientes recorrido = lista;
    while (recorrido != NULL) {
        if (recorrido->cedula == cedula) 
            break;
        recorrido = recorrido->sig;
    }
    return (recorrido);
}
//Funcion que recorre la lista de pacientes y se encarga de evaluar si existe algun paciente
//con el numero de cedula dado como parametro. Devuelve el booleano equivalente al resultado de la comparacion
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
//Funcion que se encarga de modificar el elemento indicado en un paciente en particular.
//Recibe como parametro dicho paciente y se repite hasta que el usuario decida salir del bucle
void campoModificarPaciente(apun_pacientes paciente){
    string linea;
    cout<<"Indique el numero de campo a modificar: ";
    bool validacion_cedula=true;
    int cedula=0;
    int opcion=repetirEntero();
    cin.ignore(); 
    while (opcion!=0)
    {
        switch (opcion)
        {
        case 0:
            break;
        case 1:
            cout<<"Introduzca nombre y apellido: ";
            linea=lineasTextoExtensas();
            paciente->nombres=linea ;
            break;
        case 2:
            while (validacion_cedula){
    
                cedula=cedulaPaciente();
                if(!existePaciente(lista_pacientes,cedula)){
                    paciente->cedula=cedula;
                    validacion_cedula=false;
                }
                else
                {
                    cout<<endl;
                    cout<<"ERROR. Ya existe un paciente con ese numero de cedula. Intete de nuevo "<<endl;
                    cout<<endl;
                    validacion_cedula=true;
                }
            }
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
//Funcion que se encarga de cambiar el archivo de historia de paciente si este cambia de cedula
//Se crea un nuevo archivo con la nueva cedula, se copia todos los elementos del viejo archivo y luego se borra el anterior
//Recibe como parametro la nueva cedula y la vieja cedula para realizar el cambio de archivo
void cambiarArchivoCedula(int cedula_vieja, int cedula_nueva){
    ofstream aux;
    fstream archivo;
    string linea,cedula_v,cedula_n;
    cedula_v="Pacientes/"+to_string(cedula_vieja)+".txt";
    cedula_n="Pacientes/"+to_string(cedula_nueva)+".txt";
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
//Funcion que se encarga de mostrar un paciente en concreto, llamar a las funciones respectivas para modificar sus datos
//y luego imprime de nuevo el paciente cambiado.
//Recibe como parametro un paciente en particular y su cedula como entero, para evaluar si esta cambio en la modificacion
void modificarPaciente(apun_pacientes paciente,int cedula){
    int cond;
    cond=0;
    imprimirPaciente(paciente);
    cout<<endl;
    campoModificarPaciente(paciente);
    if(cedula!=paciente->cedula){
        cambiarArchivoCedula(cedula,paciente->cedula);
    }
    cout<<"Los datos del paciente fueros modificados correctamente"<<endl;
    cout<<"**********************"<<endl;
    imprimirPaciente(paciente);
    cout<<"**********************"<<endl;
    crearArchivoPaciente(lista_pacientes);
}
//Funcion que se encarga de crear o agregar nuevos elementos a la lista de pacientes.
//Recibe como parametro por referencia la lista de pacientes y un entero que sera la cedula del nuevo paciente
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
    cout<<endl;
    cout<<"Paciente creado con exito"<<endl;
    cout<<"********************"<<endl;
    imprimirPaciente(aux1);
    cout<<endl;

    crearArchivoPaciente(lista_pacientes);

    
}
//Funcion que recibe como parametro un entero como numero de cedula, busca el paciente en la lista
//y devuelve el nombre de dicho paciente
string obtenerNombre(int cedula){
    apun_pacientes recorrido=lista_pacientes;
    while (recorrido!=NULL)
    {
        if (recorrido->cedula==cedula)
        {
            return recorrido->nombres;
        }
        recorrido=recorrido->sig;
    }
    return NULL; 
}
