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
bool validacion(string user,string pass)
{
    cout<<registro_doctor->user<<endl;
    cout<<user<<endl;
    cout<<registro_doctor->pass<<endl;
    cout<<base64_encode(pass,cadena)<<endl;
    cout<<pass;
    if ((user==registro_doctor->user) && (base64_encode(pass,cadena)==registro_doctor->pass))
        {
            return true;
        }
    else
        {  
            return false;
        }
}
//Funcion que verifica si el user o la contrasena, tiene mas de 6 cacteres sin espacio
bool verificacionCaracteres(string parametro){
    if (parametro.length()>=6)
    {
        for (int i = 0; i < parametro.length(); i++)
        {
            if (parametro[i] == ' ')
            {
                return false;
            }
            else
            {
                return true;
            }
            
        }
        
    }
    else
    {
        return false;
    }
    
}

//Funcion que hace un llamado a las dos validaciones anteriores y devuelve el valor booleano 
//de la operacion de las dos validaciones. Asi, como un mensaje de error.
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
//Si entrada devuelve un falso, se hace un llamado recursivo a datoSesion hasta que pueda entrar.
bool datoSesion(){
    string user,pass; 
    cout<<"Introduzca el username: ";
    cin>>user;
    cout<<" "<<endl;
    cout<<"Introduzca la contraseña: ";
    cin>>pass;
    cout<<" "<<endl;
    if (entrada(user,pass)){
        return true;
    }
    else
    {
        cout<<"Intente de nuevo."<<endl;
        cout<<"********************"<<endl;
        datoSesion(); // Recursividad, siempre debe dar positivo
    }
    }
//Funcion que verifica la existencia del archivo doctor y llena la estructura doctor con los datos
//dentro del archivo
bool crearDoctor(Doc &registro, semana &lista_semana){
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
                break;
            }
        return true;
    }
    else
    {
        return false;
    }
    archivo.close();
}

//Llamada principal de inicio de sesion.  
//Verifica que el archivo doctor funcionara correctamente 
//No finaliza hasta que datosSesion retorne verdadero.
bool inicioSesion(){
    cout<<"APP MEDICA"<<endl;
    crearDoctor(registro_doctor,lista_semana);
    cout<<registro_doctor->user<<endl;
    cout<<registro_doctor->pass<<endl;
    cout<<base64_decode(registro_doctor->pass,cadena)<<endl;;

    if (datoSesion() && registro_doctor!=NULL){
        return true;
    }
    else
    {
        cout<<"Error archivo doctor no disponible o corrupto"<<endl;
        return false;
    }
    
}
