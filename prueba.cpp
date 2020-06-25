#include <iostream>
#include <ctype.h>
#include "historias.h"

using namespace std;

int main(){
    historia_paciente paciente1,paciente2; 
    int opcion;
    bool a=true;
    crearListaHistoriaOrdenada(lista_historia,25676145);
    
    while (a)
    {
        cout<<"Desea continuar ";
        cin>>opcion;
        if (opcion!=0)
        {
            cin.ignore();
            crearListaHistoriaOrdenada(lista_historia,25676145);
        }
        else
        {
            a=false;
        }
        
        
    }
    paciente1=lista_historia;
    cout<<paciente1->sintomas<<endl;
    cout<<endl;
    mostrarLista(lista_historia);
    return 0;
}
