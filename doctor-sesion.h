#include <iostream>
#include <fstream>
#include "base64.cpp"
#include "fechadoc.h"
using namespace std;

//Libreria encargada de leer el archivo doctor y asignar sus valores a su respectivo nodo
//Encargarse del inicio de sesion del doctor

/*Arbol de llamado
    -inicioSesion
        -crearDoctor
        -datos sesion (recursiva)
            -entrada
                -validacion
                    -Encriptado(LIBRERIA CONTRASEÑA)
                -verificacionCaracteres
    Main()
*/

//Estructura que guardara los datos leidos del archivo del doctor. 
struct doctor {
    string user;
    string pass;
    string nombre;
    string especializacion;
    semana dias;
    horas horas_lab;
    int anio_sesion;
};
bool cadena;
typedef struct doctor *Doc;
//Inicializacion de tipo de dato- Doctor- Como null y variable global
Doc registro_doctor=NULL;
semana lista_semana=NULL;
horas lista_horas=NULL;



//Funcion que se encarga de verificar que el usuario y la contraseña coinciden con los datos 
//del nodo doctor.
//NOTA: Se hace un llamado a la funcion encriptado pues la contrasena esta encriptada en el archivo
//Recibe como parametro el usuario y la contrasena
bool validacion(string user,string pass)
{
    if ((user==registro_doctor->user) && (base64_encode(pass,cadena)==registro_doctor->pass))
        {
            return true;
        }
    else
        {  
            return false;
        }
}
//Funcion que verifica si el user o la contrasena, tiene mas de 6 cacteres sin espacio y devuelve un bool con eso
//Recibe como parametro el user o la contrasena
bool verificacionCaracteres(string parametro){
    bool a=true;
    if (parametro.length()>=6)
    {
        for (int i = 0; i < parametro.length(); i++)
        {
            if (parametro[i] == ' ')
            {  
                a=false;
                return false;
    
            }            
        }
        if(a){
            return true;
        }
    }
    else
    {
        return false;
    }
    return NULL;
}

//Funcion que hace un llamado a las dos validaciones anteriores y devuelve el valor booleano 
//de la operacion de las dos validaciones. Asi, como un mensaje de error. 
//Tambien recibe como parametro el user y el pass
bool entrada(string user, string pass){
    bool val1,val2;
    val1=verificacionCaracteres(user);
    val2=verificacionCaracteres(pass);
    if (val1 && val2){
        if(validacion(user,pass)){
            return true;
        }
        else
        { 
            cout<<"El usuario o contrasena no coincide. Intente de nuevo"<<endl;
            return false;
        }
    }
    else
    {
        cout<<"El usuario/contrasena debe de ser mayor a 6 caracteres y no debe tener espacios"<<endl;
        return false;
    }
    
}

//Funcion que se encarga de pedir los datos al usuario
//Luego hace llamado a la funcion entrada para que haga las validaciones necesarias

bool datoSesion(){
    string user,pass; 
    cout<<"***************APP MEDICA****************"<<endl;
    cout<<"Introduzca el username: ";
    cin>>user;
    cout<<" "<<endl;
    cout<<"Introduzca la contrasena: ";
    cin>>pass;
    cout<<" "<<endl;
    if (entrada(user,pass)){
        return true;
        }
    else
        {
        cout<<"Intente de nuevo."<<endl;
        cout<<"********************"<<endl;
        cin.get();
        cin.get();
        system("clear");
        return false;
        }
    }
//Funcion que se encarga de repetir datoSesion hasta que se introduzcan datos validos para iniciar sesion.
void nuevoIntento(){
    bool a=true;
    while (a)
    {
        cout<<" "<<endl;
        if (datoSesion())
        {
            a=false;
            break;
        }
        else
        {
            a=true;
        }
        
    }
    
}

//Funcion que verifica la existencia del archivo doctor y llena la estructura doctor con los datos
//dentro del archivo
//Recibe como parametro un nodo doctor y un nodo lista_semana. Ambos como variables globales
void crearDoctor(Doc &registro, semana &lista_semana){
    fstream archivo;
    string linea;
    registro=new(struct doctor);
    archivo.open("doctor.txt", ios::in);
    if (!archivo.fail())
    {
        while(!archivo.eof())
            {
                getline(archivo,registro->user);
                getline(archivo,registro->pass);
                getline(archivo,registro->nombre);
                getline(archivo,registro->especializacion);
                getline(archivo,linea);
                asignarSemana(linea,lista_semana);
                registro->dias=lista_semana;
                getline(archivo,linea);
                asingarHoras(lista_horas,linea);
                registro->horas_lab=lista_horas;
                registro->anio_sesion=2020;
                break;
            }
    }
    registro->dias->horas_dis=registro_doctor->horas_lab; 
    archivo.close();
}

//Llamada principal de inicio de sesion.  
//Verifica que el archivo doctor funcionara correctamente y llenara la estructura doctor, de lo contrario de vuelve un false

bool inicioSesion(){
    crearDoctor(registro_doctor,lista_semana);
    nuevoIntento();
    if (registro_doctor!=NULL){
        return true;
    }
    else
    {
        cout<<"Error archivo doctor no disponible o corrupto"<<endl;
        return false;
    }
    
}
