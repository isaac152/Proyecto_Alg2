#include <iostream>
#include <fstream>

using namespace std;

//Funcion que verifica la exitencia del archivo
bool verificarArchivo(string nombreArchivo){
    fstream archivo;
    nombreArchivo=nombreArchivo+".txt";
    archivo.open(nombreArchivo, ios::in);
    if (!archivo.fail())
    {
        while(!archivo.eof())
            {
                return true;
            }
    }
    else
    {
        return false;
    }
}
