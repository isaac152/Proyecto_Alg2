#include <iostream>
#include <fstream>
#include "base64.cpp"
#include "fechadoc.h"
using namespace std;
#pragma once

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
    semana dias=NULL;
    horas horas_lab=NULL;
    int anio_sesion;
};

bool cadena;
typedef struct doctor *Doc;
//Inicializacion de tipo de dato- Doctor- Como null y variable global
Doc registro_doctor=NULL;



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
bool verifiArchivoDoctor(){
    fstream archivo;
    archivo.open("doctor.txt",ios::in);
    if (!archivo.fail()){
        return true;
    }
    else
    {
        return false;
    }
    archivo.close();
    
}



Doc crearDoctor(){
    fstream archivo;
    string linea;
    semana lista_semana;
    horas lista_horas;
    Doc registro;
    registro=new(struct doctor);
    archivo.open("doctor.txt", ios::in);
    while(!archivo.eof())
            {
                getline(archivo,registro->user);
                getline(archivo,registro->pass);
                getline(archivo,registro->nombre);
                getline(archivo,registro->especializacion);
                getline(archivo,linea);
                //
                asignarSemana(linea,lista_semana);
                registro->dias=lista_semana;
                getline(archivo,linea);
                asingarHoras(lista_horas,linea);
                registro->horas_lab=lista_horas;
                getline(archivo,linea);
                registro->anio_sesion=atoi(linea.c_str());
                break;
            }
        return registro;
    archivo.close();
}

//Llamada principal de inicio de sesion.  
//Verifica que el archivo doctor funcionara correctamente 
//No finaliza hasta que datosSesion retorne verdadero.
bool inicioSesion(Doc &registro_doctor){
    Doc doctor;
    doctor=registro_doctor;
    cout<<"APP MEDICA"<<endl;
    if(verifiArchivoDoctor()){
     doctor=crearDoctor();
    }
    else
    {
        cout<<"Archivo invalido"<<endl;
    }
    cout<<doctor->user<<endl;
    cout<<doctor->pass<<endl;
    cout<<base64_decode(doctor->pass,cadena)<<endl;;

    if (datoSesion() && verifiArchivoDoctor()){
        return true;
    }
    else
    {
        cout<<"Error archivo doctor no disponible o corrupto"<<endl;
        return false;
    }
    
}
