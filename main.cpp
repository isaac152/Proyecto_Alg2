#include <iostream>
#include "doctor-sesion.h"

using namespace std;


int main()
{
    if(inicioSesion()){
        cout<<"LO HICIMOS, LO HICIMOS"<<endl;
    }

    return 0;

    /*
    cout<<"Introduzca contrasena "; //prueba
    cin>>nombreArchivo;
    n=nombreArchivo.size();
    copia="";
    for (int i = 1; i <=n; i++)
    {
        a=n*-1;
        nombreArchivo[i]=nombreArchivo[i]+a;
        copia=copia+nombreArchivo[i];
        if (i % 2 ==0){
            copia=copia+"@";
        }
        else
        {
            copia=copia+"$";
        }
        
    }
    n=n+5;  
    copia=copia+to_string(n);
    cout<<copia<<endl;
    */

}