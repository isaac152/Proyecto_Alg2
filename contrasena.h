#include <iostream>
using namespace  std;

string encriptado(string contrasena){
    int tamano,alterno;
    string copia=contrasena;
    string encrip="";
    tamano=contrasena.size()+5;
    alterno=tamano;
    for (int i=0; i<contrasena.size(); i++){
        alterno=alterno*-1;
        copia[i]=copia[i]+alterno;
        encrip=encrip+copia[i];
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
string descencriptado(string contrasena){
    int tamano,alterno;
    string copia="";
    for (int i = 0; i <contrasena.size(); i++)
    {   
        if(i%2==0){
            copia=copia+contrasena[i];
        } 
    }
    tamano=copia.size()+5;
    alterno=-tamano;
    for (int i = 0; i <copia.size(); i++)
    {
        alterno=alterno*-1;
        copia[i]=copia[i]+alterno;   
    }
    return copia;
    
}