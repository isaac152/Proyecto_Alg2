#include <iostream>
using namespace  std;
//Libreria encargada de encriptar y desencriptar la contrasena del doctor

//Funcion encargada de encriptar
string encriptado(string contrasena){
    int tamano,alterno;
    //Copia contrasena en una variable auxiliar y se crea un nuevo string vacio
    string copia=contrasena;
    string encrip="";

    tamano=contrasena.size()+5;
    alterno=tamano;
    
    for (int i=0; i<contrasena.size(); i++){
        //Por cada vuelta de ciclo, alterno cambia su signo segun el orden {-,+,-,+,-,+}
        alterno=alterno*-1;
        //Agarra el caracter i de la copia y le suma el tamano+5 en su valor de la tabla ASCII
        copia[i]=copia[i]+alterno;
        //Se copia el nuevo caracter dentro del string vacio
        encrip=encrip+copia[i];
        //Si el caracter se encuentra en una posicion par, se le anade un @ de lo contrario un $
        //Para hacer la contrasena mas larga y despistar.
        if (i % 2 ==0){
            encrip=encrip+"@";
        }
        else
        {
            encrip=encrip+"$";
        }
    }
    return encrip;
}  
//Funcion encargada de descriptar-
string descencriptado(string contrasena){
    int tamano,alterno;
    string copia="";
    //Ciclo que se encarga de eliminar todos los $ y @ presentes en el encriptado
    for (int i = 0; i <contrasena.size(); i++)
    {   
        if(i%2==0){
            copia=copia+contrasena[i];
        } 
    }
    tamano=copia.size()+5;
    alterno=-tamano;
    //Ciclo que busca sumar o restar caractereses segun su codigo ASCII para que regresen a su valor 
    for (int i = 0; i <copia.size(); i++)
    {
        //alterno va cambiando segun el orden {+,-,+,-,+} para eliminar el efecto del encriptado
        alterno=alterno*-1;
        //Cada caracter se suma o resta con el valor respectivo del encriptado
        copia[i]=copia[i]+alterno;   
    }
    return copia;
    
}