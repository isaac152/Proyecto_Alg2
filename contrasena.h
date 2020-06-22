#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace  std;
//Libreria encargada de encriptar y desencriptar la contrasena del doctor

void cambiarContra(string cambiar){
    ofstream aux;
    fstream archivo;
    string linea;
    archivo.open("doctor.txt",ios::in);
    if(!archivo.fail())
    {
        aux.open("aux.txt",ios::out);
        if(!aux.fail()){
            getline(archivo,linea);
            aux<<linea<<endl;
            getline(archivo,linea);
            aux<<cambiar<<endl;
            for (int i = 0; i < 3; i++)
            {
                getline(archivo,linea);
                aux<<linea<<endl;
            }
            getline(archivo,linea);
            aux<<linea;
            aux.close();
        }
       
    }
    archivo.close();
    remove("doctor.txt");
    rename("aux.txt","doctor.txt");
}