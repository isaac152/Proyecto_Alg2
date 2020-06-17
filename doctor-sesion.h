#include <iostream>
#include <fstream>
using namespace std;

struct doctor {
    string user;
    string pass;
    string nombre;
    string especializacion;
    string dias;
    string horas;
};
typedef struct doctor *Doc;

Doc registro_doctor=NULL;

bool validacion(string user,string pass)
{
    if ((user==registro_doctor->user) && (pass==registro_doctor->pass))
        {
            return true;
        }
    else
        {  
            return false;
        }
}
bool verificacionCaracteres(string parametro){
    if (parametro.length()>=6)
    {
        for (int i = 0; i < parametro.length(); i++)
        {
            if (parametro[i] == ' ')
            {
                return false;
            }
            else
            {
                return true;
            }
            
        }
        
    }
    else
    {
        return false;
    }
    
}

bool entrada(string user, string pass){
    bool val1,val2;
    val1=verificacionCaracteres(user);
    val2=verificacionCaracteres(pass);
    if (val1 && val2){
        if(validacion(user,pass)){
            return true;
        }
        else
        { 
            cout<<"El usuario o contrasena no coincide. Intente de nuevo"<<endl;
            return false;
        }
    }
    else
    {
        cout<<"El usuario/contrasena debe de ser mayor a 6 caracteres y no debe tener espacios"<<endl;
        return false;
    }
    
}

bool datoSesion(){
    string user,pass; 
    cout<<"Introduzca el username: ";
    cin>>user;
    cout<<" "<<endl;
    cout<<"Introduzca la contraseña: ";
    cin>>pass;
    cout<<" "<<endl;
    if (entrada(user,pass)){
        return true;
    }
    else
    {
        cout<<"Intente de nuevo."<<endl;
        cout<<"********************"<<endl;
        datoSesion(); //intento recursividad,, siempre debe dar positivo
    }}

Doc crearDoctor(Doc &registro){
    fstream archivo;
    string linea;
    registro=new(struct doctor);
    archivo.open("doctor.txt", ios::in);
    if (!archivo.fail())
    {
        while(!archivo.eof())
            {
                getline(archivo,registro->user);
                getline(archivo,registro->pass);
                getline(archivo,registro->nombre);
                getline(archivo,registro->especializacion);
                getline(archivo,registro->dias);
                getline(archivo,registro->horas);
            }
    }
    else
    {
        cout<<"Error archivo doctor"<<endl;
    }
}
bool inicioSesion(){
    cout<<"APP MEDICA"<<endl;
    crearDoctor(registro_doctor);
    if (datoSesion()){
        return true;
    }
}


