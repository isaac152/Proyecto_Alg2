#include <iostream>
#include "doctor-sesion.h"
#include "menu.h"
using namespace std;


//Archivo principal de la app
int main()
{   

    if(inicioSesion()){
        interfazMenu();

    }
    return 0;
}