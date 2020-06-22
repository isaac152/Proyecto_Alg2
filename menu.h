#include <iostream>
#include "contrasena.h"
using namespace std;

//limpiar pantalla


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

void logicaMenu(int opcion){
    switch (opcion)
    {
    case 1:
        //Funcion historias
        break;
    case 2:
        //funcion citas
        break;

    case 3:
        cambioContrasena();
        break;

    case 4:
        break;
    
    default:
        cout<<"Valor invalido. Intente de nuevo"<<endl;
        cin.get();
        break;
    }

}

void interfazMenu(){
    int opcion;
    cout<<"Bienvenido "<<registro_doctor->nombre<<endl;
    cout<<"*********************"<<endl;
    cout<<"******opciones*******"<<endl;
    cout<<"*********************"<<endl;
    cout<<"1-Historias"<<endl;
    cout<<"2-Citas"<<endl;
    cout<<"3-Cambio contraseña"<<endl;
    cout<<"4-Salir"<<endl;
    cin>>opcion;
    logicaMenu(opcion);
}