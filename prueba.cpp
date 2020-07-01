#include <iostream>
#include "doctor-sesion.h"
#include "pacientes.h"
#include <stdlib.h>
using namespace std;


int main(){
    int cedula,opcion;
    bool a=true;
    cedula=cedulaPaciente();
    cout<<cedula<<endl;
    cedula=cedulaPaciente();
    cout<<cedula<<endl;
    cedula=cedulaPaciente();
    cout<<cedula<<endl;
    while (a)
    {
        cedula=cedulaPaciente();
        cout<<cedula<<endl;
        cout<<"Diga el valor "<<endl;
        cin>>opcion;
        if (opcion==0)
        {
            a=false;
        }
        
    }
    
    system("pause");
    return 0;
}
