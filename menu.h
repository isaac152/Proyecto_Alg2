#include <iostream>
#include "contrasena.h"
#include "menuhistoria.h"
#include <stdlib.h>
using namespace std;

/*
void cambioContrasena(){
    string nueva_contrasena,seguridad;
    cout<<"Introduce la actual contrasena"<<endl;
    cin>>seguridad;
    if (validacion(registro_doctor->user,seguridad)){
        cout<<"Introduce la nueva contrasena"<<endl;
        cin>>nueva_contrasena;
        nueva_contrasena=base64_encode(nueva_contrasena,cadena);
        registro_doctor->pass=nueva_contrasena;
        cambiarContra(nueva_contrasena);
    }
}
*/

void interfazMenu(){
    cout<<"Bienvenido "<<registro_doctor->nombre<<endl;
    cout<<"*********************"<<endl;
    cout<<"******opciones*******"<<endl;
    cout<<"*********************"<<endl;
    cout<<"1-Historias"<<endl;
    cout<<"2-Citas"<<endl;
    cout<<"3-Salir"<<endl;
}

void logicaMenu(){
    int opcion=0;
    while (opcion!=3)
    {
    interfazMenu();
    opcion=repetirEntero();
        switch (opcion)
        {
        case 1:
            menuHistoria();
            break;
        case 2:
            //funcion citas
            break;
        case 3:
            break;
        
        default:
            cout<<"Valor invalido. Intente de nuevo"<<endl;
            cin.get();
            break;
        }
    system("CLS");
    }

}