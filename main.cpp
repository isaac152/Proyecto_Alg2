#include <iostream>
#include "Archivo.h"
#include <string>

using namespace std;

string nombreArchivo,copia;
int n,a;
int main()
{
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
    

    return 0;
}