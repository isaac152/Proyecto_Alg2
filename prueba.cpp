#include <iostream>
#include <ctype.h>
#include "historias.h"

using namespace std;

int main(){
    int opcion;
    bool a=true;

    crearListaHistoriaOrdenada(lista_historia,25676145);
    while (a)
    {
        cout<<"Desea continuar ";
        cin>>opcion;
        if (opcion!=0)
        {
            crearListaHistoriaOrdenada(lista_historia,25676145);
        }
        else
        {
            a=false;
        }
        
        
    }
    mostrarLista(lista_historia);

    return 0;
}
